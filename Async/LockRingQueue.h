#ifndef LOCK_RING_QUEUE
#define LOCK_RING_QUEUE

#include <assert.h>
#include <vector>
#include <mutex>
#include <atomic>


template <class T>
class LockRingQueue
{
protected:
	std::vector<T*> _ring_arr;
	std::mutex _queue_mutex;
	unsigned int _capacity;
	int _head;
	int _tail;
	std::atomic_int _size;

protected:
	inline int _next_position(int current)
	{
		return (current + 1) % _capacity;
	}

public:
	LockRingQueue(unsigned int capacity = 1024) :
		_capacity(capacity),
		_head(0),
		_tail(0),
		_size(0)
	{
		_ring_arr.resize(_capacity);
	}

	~LockRingQueue()
	{

	}

	inline bool empty()
	{
		return _size.load() == 0;
	}

	inline bool full()
	{
		return _size.load() == _capacity;
	}

	bool push(T* pData)
	{
		assert(pData);
		if (full())
		{
			return false;
		}
		else
		{
			_size.fetch_add(1);
			std::unique_lock<std::mutex> lock(_queue_mutex);
			_ring_arr[_tail] = pData;
			_tail = _next_position(_tail);
			return true;
		}
	}

	T* pop()
	{
		if (empty())
		{
			return nullptr;
		}
		else
		{
			_size.fetch_sub(1);
			std::unique_lock<std::mutex> lock(_queue_mutex);
			T* ret = _ring_arr[_head];
			_head = _next_position(_head);
			return ret;
		}
	}
};


#endif // LOCK_RING_QUEUE
