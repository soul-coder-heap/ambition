#ifndef ASYNC_SIGNAL_H
#define ASYNC_SIGNAL_H
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <future>
#include <iostream>


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
            std::vector<std::future<void>> futures;
            for (auto& slot : local) {
                futures.emplace_back(std::async(std::launch::async, &Slot<Args...>::operator(), slot, args...));
            }
            for (auto& future : futures) {
                future.get();  // 等待所有异步任务完成
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




// 槽1，打印收到的数值
void Slot1(int value) {
    //std::cout << "Slot 1: " << value << std::endl;
    printf("Slot 1: %d\n", value);
}

// 槽2，打印收到的数值，并延迟一段时间
void Slot2(int value) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    //std::cout << "Slot 2: " << value << std::endl;
    printf("Slot 2: %d\n", value);

}

// 槽3，打印收到的数值的平方
void Slot3(int value) {
    //std::cout << "Slot 3: " << value * value << std::endl;
    printf("Slot 3: %d\n", value);
}

int async_run_signal() {
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

#endif // ASYNC_SIGNAL_H
