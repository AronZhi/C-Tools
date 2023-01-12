#ifndef MESSAGE_QUEUE
#define MESSAGE_QUEUE

/*
* Apply to multi thread push message and one thread pop message
*/

#include <queue>
#include <mutex>
#include <memory>

template <class T>
class MessageQueue
{
protected:
	bool _run;
	std::queue<std::shared_ptr<T>> _queue;
	std::mutex _mtx;
	std::condition_variable _signal;

public:
	MessageQueue() : _run(true) {}

	void stop()
	{
		do
		{
			std::unique_lock<std::mutex> lock(_mtx);
			_run = false;
		} while (false);
		_signal.notify_all();
	}

	bool push(T* pMsg)
	{
		T* p = new T();
		if (p)
		{
			memset(p, 0, sizeof(T));
			memcpy(p, pMsg, sizeof(T));
			std::shared_ptr<T> queue_msg(p);
			do
			{
				std::unique_lock<std::mutex> lock(_mtx);
				if (_run)
					_queue.push(std::move(queue_msg));
				else
					return false;
			} while (false);
			_signal.notify_all();
			return true;
		}
		return false;
	}

	std::shared_ptr<T> pop()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		while (_run && _queue.empty())
			_signal.wait(lock);

		if (_queue.empty())
		{
			std::shared_ptr<T> ret(nullptr);
			return ret;
		}
		else
		{
			std::shared_ptr<T> ret(std::move(_queue.front()));
			_queue.pop();
			return ret;
		}
	}
};

#endif // MESSAGE_QUEUE