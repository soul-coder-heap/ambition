#ifndef SIGNAL_H
#define SIGNAL_H
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <iostream>
#include <thread>

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

// 设置信号优先级
/*
template <typename... Args>
class Slot {
 public:
  using Callback = std::function<void(Args...)>;
  using Condition = std::function<bool(Args...)>;

  Slot(const Slot& another)
      : cb_(another.cb_), connected_(another.connected_), priority_(another.priority_), condition_(another.condition_) {}

  explicit Slot(const Callback& cb, int priority = 0, const Condition& condition = nullptr, bool connected = true)
      : cb_(cb), connected_(connected), priority_(priority), condition_(condition) {}

  virtual ~Slot() {}

  void operator()(Args... args) {
    if (connected_ && cb_ && (!condition_ || condition_(args...))) {
      cb_(args...);
    }
  }

  void Disconnect() { connected_ = false; }
  bool connected() const { return connected_; }

  int priority() const { return priority_; }
  void setPriority(int priority) { priority_ = priority; }

  Condition condition() const { return condition_; }
  void setCondition(const Condition& condition) { condition_ = condition; }

 private:
  Callback cb_;
  bool connected_ = true;
  int priority_ = 0;
  Condition condition_;
};

*/


/*

template <typename... Args>
class Signal {
  // ...

 public:
  // ...

  ConnectionType Connect(const Callback& cb, int priority = 0, const Condition& condition = nullptr) {
    auto slot = std::make_shared<Slot<Args...>>(cb, priority, condition);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = std::lower_bound(slots_.begin(), slots_.end(), slot,
                                 [](const SlotPtr& a, const SlotPtr& b) {
                                   return a->priority() > b->priority();
                                 });
      slots_.insert(it, slot);
    }

    return ConnectionType(slot, this);
  }

  // ...

 private:
  // ...

  void operator()(Args... args) {
    SlotList local;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      local = slots_; // Create a local copy to avoid modifying the original list while iterating
    }

    for (auto& slot : local) {
      (*slot)(args...);
    }

    ClearDisconnectedSlots();
  }

  // ...
};
*/



// 槽1，打印收到的数值
void Slot1(int value) {
    std::cout << "Slot 1: " << value << std::endl;
}

// 槽2，打印收到的数值，并延迟一段时间
void Slot2(int value) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Slot 2: " << value << std::endl;
}

// 槽3，打印收到的数值的平方
void Slot3(int value) {
    std::cout << "Slot 3: " << value * value << std::endl;
}

int run_signal() {
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
#endif // SIGNAL_H
