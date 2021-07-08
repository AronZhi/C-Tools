#ifndef THREAD_POOL
#define THREAD_POOL

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t thread_count);
    template<class F, class... Args>
    auto AddTask(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    std::vector<std::thread> __work_threads;
    std::queue<std::function<void()> > __tasks;

    std::mutex __queue_mutex;
    std::condition_variable __weak_thread_signal;
    bool __stop;
};

/*创建一定数量的线程*/
ThreadPool::ThreadPool(size_t thread_count)
: __stop(false)
{
    for(size_t i = 0; i < thread_count; i++)
    {
        __work_threads.emplace_back(
            [this]
            {
                /* 线程将循环从任务队列中取任务做任务 */
                for (;;)
                {
                    std::function<void()> task;
                    {
                        /* 进入临界区获取任务 */
                        std::unique_lock<std::mutex> lock(this->__queue_mutex);
                        this->__weak_thread_signal.wait(lock, [this]{return this->__stop || !this->__tasks.empty();});
                        if (this->__stop && this->__tasks.empty())
                            return;
                        task = std::move(this->__tasks.front());
                        this->__tasks.pop();
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
    {
        std::unique_lock<std::mutex> lock(__queue_mutex);
        __stop = true;
    }
    __weak_thread_signal.notify_all();
    /* 等待所有线程执行完 */
    for (std::thread& thread : __work_threads)
        thread.join();
}

template<class F, class... Args>
auto ThreadPool::AddTask(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>
{
    using ret_type = typename std::result_of<F(Ars...)>::type;
    auto task = std::make_shared<std::packaged_task<ret_type()> >(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    std::future<ret_type> res = task->get_future()
    {
        /* 进入临界区，将任务添加到任务队列 */
        std::unique_lock<std::mutex> lock(__queue_mutex);
        if (__stop)
            throw std::runtie_error("add task on stopped thread pool");
        __tasks.emplace([task](){*task();});
    }
    /* 唤醒一个线程取执行任务 */
    __weak_thread_signal.notify_one();
    return res;
}

#endif // THREAD_POOL