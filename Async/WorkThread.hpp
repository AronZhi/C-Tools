#ifndef WORK_THREAD
#define WORK_THREAD

#include <thread>
#include <atomic>
#include <memory>

class WorkThread
{
protected:
	std::atomic_bool _thread_run;
	std::atomic_bool _thread_exist;
	std::unique_ptr<std::thread> _thread;

public:
	WorkThread() : _thread_run(false), _thread_exist(false), _thread(nullptr) {}

	virtual ~WorkThread()
	{ 
		stop();
		join();
	}

	inline bool isRunning() { return _thread_run.load(); }

	void stop() 
	{
		bool run = true;
		_thread_run.compare_exchange_strong(run, false);
	}

	void join()
	{
		if (_thread_exist.load())
		{
			if (_thread)
			{
				_thread->join();
				_thread.reset(nullptr);
			}
			_thread_exist.store(false);
		}
	}

	void run()
	{
		bool existed = false;
		if (_thread_exist.compare_exchange_strong(existed, true))
		{
			try
			{
				_thread.reset(new std::thread([&]() {
					_thread_run.store(true);
					work();
				}));
			}
			catch (...)
			{
				onException();
			}
		}
	}

	void reRun()
	{
		stop();
		join();
		run();
	}

protected:
	virtual void work() = 0;
	/* 
	void work()
	{
		while (_thread_run.load())
		{
			// TODO
		}
	}
	*/

	virtual void onException()
	{
		_thread_run.store(false);
		_thread_exist.store(false);
		_thread.reset(nullptr);
	}
};

#endif // WORK_THREAD