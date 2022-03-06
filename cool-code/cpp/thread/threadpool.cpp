#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include "threadpool.h"


class ThreadPoolInternal {
public:
    ThreadPoolInternal(int nthreads) : 
        //q_(32 * moodycamel::BlockingConcurrentQueue<TaskBase *>::BLOCK_SIZE, 10, 10),
        nthreads_(nthreads)
    {}

    ThreadPoolInternal(const ThreadPoolInternal &) = delete;

    void Start() {
        threads_.reserve(nthreads_);
        for (int i = 0; i < nthreads_; ++i) {
            threads_.emplace_back(std::thread(&ThreadPoolInternal::ThreadFunc, this, i));
        }
    }

    void ThreadFunc(int i) {
        std::string thread_name = "ml-parallel-pool-" + std::to_string(i);
        pthread_setname_np(pthread_self(), thread_name.c_str());
        for (;;) {
            if (auto r = stopped_.load(std::memory_order_relaxed); r != 0) {
                // TODO: task memory leak
                return;
            }

            TaskBase * task;
            // wait for 10ms
            if (auto success = q_.wait_dequeue_timed(task, 10 * 1000); success) {
                auto _ = std::unique_ptr<TaskBase>(task);
                (*task)();
            }
        }
    }

    void Stop() {
        stopped_.store(1, std::memory_order_relaxed);
        for (int i = 0; i < nthreads_; ++i) {
            threads_[i].join();
        }
    }

    std::queue<TaskBase*> q_;
    std::vector<std::thread> threads_;
	std::condition_variable cond_;
    int nthreads_;
    std::atomic<int> stopped_{0};
};

ThreadPool::ThreadPool(int nthreads) {
    internal_.reset(new ThreadPoolInternal(nthreads));
    internal_->Start();
}

ThreadPool::~ThreadPool() {
    internal_->Stop();
}

void ThreadPool::Submit(TaskBase * task) {
    internal_->q_.enqueue(task);
}

void ThreadPool::SubmitBulk(ThreadPool::TaskIteratorWrapper wrapper, size_t count) {
    internal_->q_.enqueue_bulk(std::move(wrapper), count);
}

int ThreadPool::GetThreadCount() const {
    return internal_->nthreads_;
}