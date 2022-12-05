#pragma once

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
		T* p = (T*)malloc(sizeof(T));
		if (p)
		{
			memcpy(p, pMsg, sizeof(T));
			std::shared_ptr<T> queue_msg(p);
			do
			{
				std::unique_lock<std::mutex> lock(_mtx);
				_queue.push(queue_msg);
			} while (false);
			_signal.notify_all();
			return true;
		}
		return false;
	}

	std::shared_ptr<T> pop()
	{
		std::shared_ptr<T> ret(nullptr);
		do
		{
			std::unique_lock<std::mutex> lock(_mtx);
			while (_queue.empty())
				_signal.wait(lock);
			ret = _queue.front();
			_queue.pop();
		} while (false);
		return ret;
	}
};