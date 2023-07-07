#ifndef MUTI_THREAD_SIGNAL_H
#define MUTI_THREAD_SIGNAL_H
#include <iostream>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace apollo {
namespace cyber {
namespace base {

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

    Signal() {}
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
                (*slot)(args...);
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

class ThreadPool {
public:
    ThreadPool() : stop_(false) {
        unsigned int threadCount = std::thread::hardware_concurrency();
        for (unsigned int i = 0; i < threadCount; ++i) {
            threads_.emplace_back(std::thread(&ThreadPool::WorkerThread, this));
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop_ = true;
            condition_.notify_all();
        }

        for (std::thread& thread : threads_) {
            thread.join();
        }
    }

    void Enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            tasks_.emplace_back(std::move(task));
        }
        condition_.notify_one();
    }

private:
    void WorkerThread() {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(mutex_);
                condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

                if (stop_ && tasks_.empty()) {
                    break;
                }

                task = std::move(tasks_.front());
                tasks_.pop_front();
            }

            task();
        }
    }

    std::vector<std::thread> threads_;
    std::list<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};


int muti_signal_run() {
    Signal<int> mySignal;
    ThreadPool threadPool;

    // Slot1，打印收到的数值
    auto Slot1 = [](int value) {
        std::cout << "Slot 1: " << value << std::endl;
    };

    // Slot2，打印收到的数值，并延迟一段时间
    auto Slot2 = [](int value) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Slot 2: " << value << std::endl;
    };

    // Slot3，打印收到的数值的平方
    auto Slot3 = [](int value) {
        std::cout << "Slot 3: " << value * value << std::endl;
    };

    // 连接槽
    mySignal.Connect(Slot1);
    mySignal.Connect(Slot2);
    mySignal.Connect(Slot3);

    // 触发信号（异步执行）
    threadPool.Enqueue([&mySignal]() {
        mySignal(5);
    });

    // 延迟一段时间，确保异步执行有足够的时间
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
}  // namespace base
}  // namespace cyber
}  // namespace apollo

#endif // MUTI_THREAD_SIGNAL_H
