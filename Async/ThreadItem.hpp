#ifndef THREAD_ITEM
#define THREAD_ITEM

#include <thread>
#include <atomic>
#include <memory>
#include "ThreadWork.hpp"

class ThreadItem
{
protected:
	std::unique_ptr<ThreadWork> _work;
	std::atomic_bool _thread_run;
	std::atomic_bool _thread_exist;
	std::unique_ptr<std::thread> _thread;

public:
	ThreadItem(ThreadWork* pWork) : _work(pWork), _thread_run(false), _thread_exist(false) {}
	virtual ~ThreadItem() 
	{
		stop();
		_work.reset(nullptr);
	}

	void run()
	{
		if (nullptr == _work.get())
			return;

		bool exist = false;
		if (_thread_exist.compare_exchange_strong(exist, true))
		{
			_thread.reset(new std::thread([&]() {
				_thread_run.store(true);
				while (_thread_run.load())
				{
					if (_work->isQuit())
					{
						break;
					}
					else
					{
						_work->work();
					}
				}
				_thread_run.store(false);
			}));
		}
	}

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

		_work->clean();
	}

	bool isRunning() { return _thread_run.load(); }

};

#endif // THREAD_ITEM