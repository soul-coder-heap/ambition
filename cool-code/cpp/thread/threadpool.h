#pragma once
#include <atomic>
#include <functional>
#include <iostream>
#include <mempry>
#include <type_traits>
namespace detail{
    template<typename L,typename R>
    struct has_operator_minus_impl{
        template<typename T = L,typename U = R>
        static auto test(T && t,U && u) -> decltype(t - u,void(),std::true_type{});        
        static auto test(...) -> std::false_type;
        using type = decltype(test(std::declval<L>(),std::declval<R>()));
    };
    template<typename L,typename R = L>
    struct has_operator_minus : detail::has_operator_minus_impl<L,R>::type{};
    
    template<typename L,typename R = L>
    inline constexpr bool has_operator_minus_v = detail::has_operator_minus<L,R>::type::value;

    template<typename L>
    struct has_operator_plus_prefix_impl{
        template<typename T = L>
        static auto test(T && t) -> decltype(++t,void(),std::true_type{});
        static auto test(...) -> std::false_type;
        using type = decltype(test(std::declval<L>()));
    };

    template<typename L>
    struct has_operator_plus_prefix : detail::has_operator_plus_prefix_impl<L>::type{};
    
    template<typename L>
    inline constexpr bool has_operator_plus_prefix_v = detail::has_operator_plus_prefix<L>::type:value;
} // namespace detail

class ThreadPoolInternal;

class TaskBase{
public:
    virtual ~TaskBase() {};
    virtual void operator()() = 0;
};

template<typename TaskFn,typename ResultFn>
class Task : public TaskBase{
public:
    Task(TaskFn && tf,ResultFn && rf) : taskFn(std::move(tf)),resultFn(std::move(rf)){}

    virtual void operator()() override{
        using Ret = std::invoke_result_t<TaskFn>;
        if(constexpr(std::is_same_v<Ret,void>)){
            std::exception_ptr ex;
			try{
				taskFn();
			}catch(...){
				ex = std::current_exception();
			}
			try{
				resultFn(ex);
			}catch(const std::exception &e){
				std::cerr <<"Uncaught exception in threadpool callback : "<<e.what()<<std::endl;
			}catch(...){
				std::cerr <<"Uncaught unknow exceptio\n in threadpool callback"<< std::endl;
			}
        }else{
			std::exception_ptr ex;
			Ret r;
			try{
				r = taskFn();
			}catch(...){
				ex = std::current_exception();
			}
			try{
				resultFn(std::move(r),ex);
			}catch(const std::exception &e){
				std::cerr <<"Uncaught exception in threadpool callback : "<<e.what()<< std::endl;
			}catch(...){
				std::cerr <<"Uncaught unknow exception in threadpool callback"<< std::endl;
			}
		}
    }
private:
    TaskFn taskFn;
    ResultFn resultFn;
};
class ThreadPool{
public:
	ThreadPool(int nthreads);
	~ThreadPool();
	ThreadPool(const ThreadPool &other) = delete;
	ThreadPool &operator = (const ThreadPool &other) = delete;
	
	template<typename TaskFunc,typename ResultFunc>
	static Taskbase * MakeTask(TaskFunc && tf,ResultFunc && rf) {
		return new Task<TaskFunc,ResultFunc>(std::move(tf),std::move(rf));
	}
	template<typename TaskFunc,typename ResultFunc>
	void Submit(TaskBase && tf,ResultFunc && rf){
		auto task = MakeTask(std::forward<TaskFunc>(tf),std::forward<ResultFunc>(rf));
		Submit(task);
	}
	void Submit(TaskBase *);
	
	struct TaskIteratorBase : public std::enable_shared_from_this<TaskIteratorBase>{
		virtual Task * operator *() = 0;
	};
	template<typename It,typename Func,typename ResultFunc>
	struct TasIterator : public TaskIteratorBase{
		It it;
		Func func;
		ResultFunc resultfn;
		size_t total;
		std::atomic_int32_t count{0};
		TasIterator(It && iter,Func && func, ResultFunc && resultfn,size_t toatl)
			: iter(std::forward<It>(iter)),
			: func(std::forward<Func>(func)),
			: resultfn(std::forward<ResultFunc(resultfn)>),
			: total(total)
		{}
		TaskBase * opoerator * () override{
			using TaskIteratorPtr = std::shared_ptr<TaskIterator>;
			TaskIteratorPtr self = std::static_pointer_cast<TaskIterator>(shared_from_this());
			auto tf = [iter = iter,self]{
				self->func(iter);
			};
			auto rf = [self](std::exception_ptr p) mutable{
				if(self->count < self->total){
					if(p){
						seif->resultfn(p);
					}else if(++self->count == self->total){
						self->resultfn(p);
					}
				}
			};
			++iter;
			return MakeTask(std::move(tf),std::move(rf));
		}
	};
	
	struct TaskIteratorWrapper{
		std::shared_ptr<TaskIteratorBase> iter;
		TaskIteratorWrapper & operator ++(){
			return *this;
		}
		TaskIteratorWrapper operator ++(int){
			TaskIteratorWrapper tmp = *this;
			return tmp;
		}
		TaskBase * operator *() const {
			return *(*iter);
		}
	};
	
	void SubmitBulk(TaskIteratorWrapper wrapper,size_t count);
	// what wanyi
	template<typename It,typename Func,typename ResultFunc,
			 typename = std::enable_if_t<detail::has_operator_minus_v<It>>,
			 typename = std::enable_if_t<std::is_copy_constructible_v<It>>>
	void ForEachRange(It begin,It end,Func && func,ResultFunc && resultfn){
		size_t count = end - begin;
		ForEachN<It,Func>(begin,std::forward<Func>(func),std::move(resultfn),count);
	}
	
	template<typename It,typename Func,typename ResultFunc,
			 typename = std::enable_if_t<detail::has_operator_plus_prefix_v<It>>,
			 typename = std::enable_if_t<std::is_copy_constructible_v<It>>>
	void ForEachN(It begin,Func && func, ResultFunc && rf,size_t count){
		std::shared_ptr<TaskIteratorBase> iter(new TaskIterator<It,Func,ResultFunc>{
			std::move(begin),std::move(func),std::move(resultfn),count});
		SubmitBulk(TaskIteratorWrapper{std::move(iter)},count);
	}
	
	int GetThreadCount() const;
private:
	std::unique_ptr<ThreadPoolInternal> internal_;
};