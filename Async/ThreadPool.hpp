#ifndef THREAD_POOL
#define THREAD_POOL

#include <thread>
#include <memory>
#include <list>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool
{
public:
	ThreadPool() : _run(false), _thread_pool_exist(false) {}
	
	~ThreadPool()
	{
		stop();
		join();
	}

	void run(int thread_count)
	{
		bool already_exist = false;
		if (_thread_pool_exist.compare_exchange_strong(already_exist, true))
		{
			_run.store(true);
			for (int i = 0; i < thread_count; ++i)
			{
				_thread_pool.emplace_back(new std::thread([&]() {
					while (_run.load())
					{
						std::shared_ptr<std::function<void()>> ptask;

						do
						{
							std::unique_lock<std::mutex> lock(_task_queue_mtx);

							while (_run.load() && _task_queue.empty())
								_weak_signal.wait(lock);

							if (!_run.load())
							{
								return;
							}
							else
							{
								ptask = _task_queue.front();
								_task_queue.pop();
							}
						} while (false);

						(*ptask)();
					}
				}));
			}
		}
	}

	void stop()
	{
		bool is_running = true;
		if (_run.compare_exchange_strong(is_running, false))
			_weak_signal.notify_all();
	}

	void join()
	{
		if (_thread_pool_exist.load())
		{
			for (auto& pthread : _thread_pool)
			{
				pthread->join();
				pthread.reset(nullptr);
			}
			_thread_pool.clear();
			_thread_pool_exist.store(false);
		}
	}

	void add(std::function<void()>&& task)
	{
		if (!_run.load())
			return;

		std::shared_ptr<std::function<void()>> ptask = std::make_shared<std::function<void()>>(task);
		do
		{
			std::unique_lock<std::mutex> lock(_task_queue_mtx);
			_task_queue.push(ptask);
		} while (false);
		_weak_signal.notify_one();
		return;
	}

private:
	std::atomic_bool _run;
	std::atomic_bool _thread_pool_exist;
	std::mutex _task_queue_mtx;
	std::condition_variable _weak_signal;
	std::queue<std::shared_ptr<std::function<void()>>> _task_queue;
	std::list<std::unique_ptr<std::thread>> _thread_pool;
};

#endif // THREAD_POOL