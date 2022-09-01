#ifndef BLOCK_QUEUE
#define BLOCK_QUEUE

#include <mutex>
#include <queue>
#include <assert.h>

template<class T>
class BlockQueue
{
public:
	void push(T data)
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		_queue.push(data);
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		assert(!_queue.empty());
		T data = _queue.front();
		_queue.pop();
		return data;
	}

	bool empty()
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		return _queue.empty();
	}

	T front()
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		assert(!_queue.empty());
		return _queue.front();
	}

private:
	std::queue<T> _queue;
	std::mutex __queue_mutex;
};

#endif // BLOCK_QUEUE
