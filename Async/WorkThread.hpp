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

	virtual ~WorkThread() { stop(); }

	inline bool isRunning() { return _thread_run.load(); }

    inline void quitWithinThread() { _thread_run.store(false); }

	void stop(bool force_stop = false)
	{
		if (force_stop)
			_thread_run.store(false);

		if (_thread_exist.load())
		{
			_thread->join();
			_thread.reset(nullptr);
			_thread_exist.store(false);
		}
	}

	virtual void run() = 0;
	/*
    void run() 
	{
		bool existed = false;
		if (_thread_exist.compare_exchange_strong(existed, true))
		{
			try
			{
				_thread.reset(new std::thread([&]() {
					_thread_run.store(true);
					while (_thread_run.load())
					{
						// TODO
					}
				}));
			}
			catch (std::exception& e)
			{
				if (_thread.get())
				{
					_thread.reset(nullptr);
					_thread_exist.store(false);
				}
			}
		}
	}
	*/
};

#endif // WORK_THREAD