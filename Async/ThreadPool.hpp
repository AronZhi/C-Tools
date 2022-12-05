#ifndef THREAD_POOL
#define THREAD_POOL

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t thread_count);
    
    ~ThreadPool();

    template<class F, class... Args>
    auto add_task(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;

    void stop();

protected:
    std::vector<std::thread> _thread_pool;
    std::queue<std::function<void()> > _task_queue;
    std::mutex _task_queue_mutex;
    std::condition_variable _weak_thread_signal;
    std::atomic_bool _run;
};

/*创建一定数量的线程*/
ThreadPool::ThreadPool(size_t thread_count)
: _run(true)
{
    for(size_t i = 0; i < thread_count; i++)
    {
        _thread_pool.emplace_back(
            [this]
            {
                /* 线程将循环从任务队列中取任务做任务 */
                for (;;)
                {
                    std::function<void()> task;
                    {
                        /* 进入临界区获取任务 */
                        std::unique_lock<std::mutex> lock(this->_task_queue_mutex);
                        while (this->_run.load() && this->_task_queue.empty())
                            this->_weak_thread_signal.wait(lock);
                        if (!this->_run.load())
                            return;
                        else
                        {
                            task = std::move(this->_task_queue.front());
                            this->_task_queue.pop();
                        }                        
                    }
                    /* 退出临界区执行任务 */
                    task();
                }
            }
        );
    }
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::stop()
{
    if (_run.load())
    {
        bool running = true;
        while (!_run.compare_exchange_strong(running, false));
        _weak_thread_signal.notify_all();
        for (std::thread& thread : _thread_pool)
            thread.join();
    }
}

template<class F, class... Args>
auto ThreadPool::add_task(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>
{
    /*
    * return 一个future, 可以用future::get()函数获得执行结果
    */
    using ret_type = typename std::result_of<F(Ars...)>::type;
    auto task = std::make_shared<std::packaged_task<ret_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    /*
    * 通过std::bind生成一个新的可调用对象，可以让task延迟调用
    * std::packaged_task允许传入一个函数或其他可调用对象，并将函数计算的结果作为异步结果传递给std::future，包括函数运行时产生的异常
    */
    std::future<ret_type> res = task->get_future();
    if (_run.load())
    {
        /* 进入临界区，将任务添加到任务队列 */
        std::unique_lock<std::mutex> lock(_task_queue_mutex);
        _task_queue.emplace([task]() {*task(); });
    }
    /* 唤醒一个线程取执行任务 */
    _weak_thread_signal.notify_one();
    return res;
}

#endif // THREAD_POOL