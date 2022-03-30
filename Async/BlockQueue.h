#ifndef BLOCK_QUEUE
#define BLOCK_QUEUE

#include <mutex>
#include <queue>

template<class T>
class BlockQueue
{
public:
	void Push(T data)
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		_queue.push(data);
	}

	T Pop()
	{
		std::unique_lock<std::mutex> lock(__queue_mutex);
		T data = _queue.front();
		_queue.pop();
		return data;
	}

private:
	std::queue<T> _queue;
	std::mutex __queue_mutex;
};

#endif // BLOCK_QUEUE
