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
	std::queue<std::shared_ptr<T>> _queue;
	std::mutex _mtx;
	std::condition_variable _signal;

public:
	bool empty()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		return _queue.empty();
	}

	bool push(T* pMsg)
	{
		T* p = new T();
		if (p)
		{
			memset(p, 0, sizeof(T));
			memcpy(p, pMsg, size);
			std::shared_ptr<T> queue_msg(p);
			do
			{
				std::unique_lock<std::mutex> lock(_mtx);
				_queue.push(std::move(queue_msg));
			} while (false);
			_signal.notify_all();
			return true;
		}
		return false;
	}

	std::shared_ptr<T> pop()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		while (_queue.empty())
			_signal.wait(lock);
		std::shared_ptr ret(std::move(_queue.front()));
		_queue.pop();
		return ret;
	}
};

#endif // MESSAGE_QUEUE