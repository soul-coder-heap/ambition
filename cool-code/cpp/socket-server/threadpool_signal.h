#ifndef THREADPOOL_SIGNAL_H
#define THREADPOOL_SIGNAL_H
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <iostream>
// 槽1，打印收到的数值
void Slot1(int value) {
    std::cout << "Slot 1: " << value << std::endl;
    //printf("Slot 1: %d\n", value);
}

// 槽2，打印收到的数值，并延迟一段时间
void Slot2(int value) {
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //std::cout << "Slot 2: " << value << std::endl;
    printf("Slot 2: %d\n", value);

}

// 槽3，打印收到的数值的平方
void Slot3(int value) {
    //int *p = &value;
    //*p = 5;
    //std::cout << "Slot 3: " << value * value << "; *p "<<*p<<std::endl;
    printf("Slot 3: %d\n", value);
}
namespace apollo {
namespace cyber {
namespace base {

class ThreadPool {
public:
    using Task = std::function<void()>;

    explicit ThreadPool(std::size_t numThreads)
        : stop_(false) {
        for (std::size_t i = 0; i < numThreads / 2; ++i) {
            std::cout <<"no."<<i<<", thread start"<< std::endl;
            threads_.emplace_back([this, i] {
                while (true) {
                    Task task;
                    //std::cout <<"no."<<i<<", running"<< std::endl;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        condition_.wait(lock, [this] { return !tasks_.empty(); });

                        if (stop_ && tasks_.empty()) {
                            return;
                        }
                        //std::cout <<"no."<<i<<", running...."<< std::endl;

                        task = tasks_.front();
                        tasks_.pop();
                        //std::cout <<"no."<<i<<", running....xxxx"<< std::endl;

                    }
                    //std::cout <<"no."<<i<<", running....yyyy"<< std::endl;

                    task();
                    std::cout <<"exec...."<< std::endl;
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }

        condition_.notify_all();

        for (std::thread& thread : threads_) {
            thread.join();
        }
    }

    template <typename Function, typename... Args>
    void Enqueue(Function&& func, Args&&... args) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.emplace([func, args...] { func(args...); });
        }

        condition_.notify_all();
    }

private:
    std::vector<std::thread> threads_;
    std::queue<Task> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};

template <typename... Args>
class Slot;

template <typename... Args>
class Connection;

template <typename... Args>
class Signal {
public:
    using Callback = std::function<void(Args...)>;
    using SlotPtr = std::shared_ptr<Slot<Args...>>;
    using SlotList = std::list<SlotPtr>;
    using ConnectionType = Connection<Args...>;

    Signal(std::size_t numThreads = std::thread::hardware_concurrency())
        : threadPool_(numThreads) {
        std::cout <<"nuthreads : "<<numThreads<< std::endl;
    }

    virtual ~Signal() { DisconnectAllSlots(); }

    void operator()(Args... args) {
        SlotList local;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& slot : slots_) {
                local.emplace_back(slot);
            }
        }

        if (!local.empty()) {
            for (auto& slot : local) {
                std::cout <<"enqueue..."<< std::endl;
                threadPool_.Enqueue([slot, args...](){
                    //slot(args...);
                    std::cout <<"thread id : "<<std::this_thread::get_id()<< std::endl;
                    (*slot)(args...);
                });

            }
        }

        ClearDisconnectedSlots();
    }

    ConnectionType Connect(const Callback& cb) {
        auto slot = std::make_shared<Slot<Args...>>(cb);
        {
            std::lock_guard<std::mutex> lock(mutex_);
            slots_.emplace_back(slot);
        }

        return ConnectionType(slot, this);
    }

    bool Disconnect(const ConnectionType& conn) {
        bool find = false;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& slot : slots_) {
                if (conn.HasSlot(slot)) {
                    find = true;
                    slot->Disconnect();
                }
            }
        }

        if (find) {
            ClearDisconnectedSlots();
        }
        return find;
    }

    void DisconnectAllSlots() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& slot : slots_) {
            slot->Disconnect();
        }
        slots_.clear();
    }

private:
    Signal(const Signal&) = delete;
    Signal& operator=(const Signal&) = delete;

    void ClearDisconnectedSlots() {
        std::lock_guard<std::mutex> lock(mutex_);
        slots_.erase(
            std::remove_if(slots_.begin(), slots_.end(),
                           [](const SlotPtr& slot) { return !slot->connected(); }),
            slots_.end());
    }

    SlotList slots_;
    std::mutex mutex_;
    ThreadPool threadPool_;
};

template <typename... Args>
class Connection {
public:
    using SlotPtr = std::shared_ptr<Slot<Args...>>;
    using SignalPtr = Signal<Args...>*;

    Connection() : slot_(nullptr), signal_(nullptr) {}
    Connection(const SlotPtr& slot, const SignalPtr& signal)
        : slot_(slot), signal_(signal) {}
    virtual ~Connection() {
        slot_ = nullptr;
        signal_ = nullptr;
    }

    Connection& operator=(const Connection& another) {
        if (this != &another) {
            this->slot_ = another.slot_;
            this->signal_ = another.signal_;
        }
        return *this;
    }

    bool HasSlot(const SlotPtr& slot) const {
        if (slot != nullptr && slot_ != nullptr) {
            return slot_.get() == slot.get();
        }
        return false;
    }

    bool IsConnected() const {
        if (slot_) {
            return slot_->connected();
        }
        return false;
    }

    bool Disconnect() {
        if (signal_ && slot_) {
            return signal_->Disconnect(*this);
        }
        return false;
    }

private:
    SlotPtr slot_;
    SignalPtr signal_;
};

template <typename... Args>
class Slot {
public:
    using Callback = std::function<void(Args...)>;

    Slot(const Slot& another)
        : cb_(another.cb_), connected_(another.connected_) {}
    explicit Slot(const Callback& cb, bool connected = true)
        : cb_(cb), connected_(connected) {}
    virtual ~Slot() {}

    void operator()(Args... args) {
        if (connected_ && cb_) {
            cb_(args...);
        }
    }

    void Disconnect() { connected_ = false; }
    bool connected() const { return connected_; }

private:
    Callback cb_;
    bool connected_ = true;
};




int threadpool_run_signal() {
    Signal<int> mySignal;

    // 连接槽
    mySignal.Connect(Slot1);
    mySignal.Connect(Slot2);
    mySignal.Connect(Slot3);
    //mySignal.Connect(Slot1, 1);
    //mySignal.Connect(Slot2, 2);
    //mySignal.Connect(Slot3, 0, [](int value) { return value % 2 == 0; });

    // 触发信号
    mySignal(5);

    return 0;
}

}  // namespace base
}  // namespace cyber
}  // namespace apollo

#endif // THREADPOOL_SIGNAL_H
