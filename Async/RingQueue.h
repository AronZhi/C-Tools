#ifndef RING_QUEUE
#define RING_QUEUE

#include <array>

template <class T, int len>
class RingQueue
{
protected:
	std::array<T*, len> _ring_arr;
	unsigned int _size;
	int _head;
	int _tail;

public:
	RingQueue() : _size(_ring_arr.size()), _head(0), _tail(0) 
	{
		_ring_arr.fill(nullptr);
	}

	virtual ~RingQueue()
	{
	}

	bool empty()
	{
		return _head == _tail;
	}

	bool full()
	{
		return ((_tial + 1) % _size) == _head;
	}

	T* pop()
	{
		if (!empty())
		{
			T* ret = _ring_arr[_head];
			_head = (_head + 1) % _size;
			return ret;
		}
		return nullptr;
	}

	T* front()
	{
		if (!empty())
			return _ring_arr[_head];
		else
			return nullptr;
	}

	bool push(T* data)
	{
		if (!full())
		{
			_tail = (_tail + 1) % _size;
			_ring_arr[_tail] = data;
			return true;
		}
		return false;
	}
};

#endif // RING_QUEUE
