#ifndef LOCK_MEMORY_POOL
#define LOCK_MEMORY_POOL

#include <mutex>
#include <queue>
#include <assert.h>

template <class T>
class LockMemoryPool
{
protected:
	char* _memory_pool;
	std::queue<char*> _queue;
	std::mutex _pool_mutex;

protected:
	LockMemoryPool(int count = 1)
	{
		int obj_size = sizeof(T) + 1;
		for (int i = 0; i < 3; i++)
		{
			_memory_pool = malloc(count * obj_size);
			if (_memory_pool)
				break;
		}
		assert(_memory_pool);
		memset(_memory_pool, 0, count * obj_size);
		for (int j = 0; j < count; j++)
		{
			char* p = static_cast<char*> (_memory_pool + j * obj_size);
			_queue.push(p);
		}
	}

	~LockMemoryPool()
	{
		if (_memory_pool)
		{
			free(_memory_pool);
			_memory_pool = nullptr;
		}
	}

	T* pop_directly()
	{
		/*
		* ����
		* �˴��ο�replacement_new, �Ӷ�����ȡ���ڴ棬����ʼ����T����Ҫ��Ĭ�Ϲ��캯����
		*/
		char* buf = nullptr;
		if (!_queue.empty())
		{
			buf = _queue.front();
			_queue.pop();
		}
		T* ret = new(buf) T;
		return ret;
	}

	void push_directly(T* mem, bool has_destruct_func = true)
	{
		/*
		* ����
		*/
		if (has_destruct_func)
			mem->T::~T();
		else
			memset(mem, 0, sizeof(T));
		_queue.push(static_case<void*> mem);
		return true;
	}

	T* pop_in_queue()
	{
		/*
		* ����
		*/
		std::unique_lock<std::mutex> lock(_pool_mutex);
		return pop_directly();
	}

	void push_in_queue(T* mem, bool has_destruct_func = true)
	{
		/*
		* ����
		*/
		std::unique_lock<std::mutex> lock(_pool_mutex);
		push_directly(mem, has_destruct_func);
		
	}
};

#endif // LOCK_MEMORY_POOL
