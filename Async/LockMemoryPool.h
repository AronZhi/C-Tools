#ifndef LOCK_MEMORY_POOL
#define LOCK_MEMORY_POOL

#include <mutex>
#include <queue>
#include <assert.h>

class LockMemoryPool
{
protected:
	char* _memory_pool;
	std::queue<char*> _queue;
	std::mutex _pool_mutex;
	int _obj_size;

protected:
	LockMemoryPool(int obj_size, int count = 1):
		_obj_size(obj_size)
	{
		obj_size += 1;
		for (int i = 0; i < 3; i++)
		{
			_memory_pool = (char*)malloc(count * obj_size);
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

	template<class  T, class ... Targs>
	T* pop_directly(Targs&... args)
	{
		/*
		* ����
		* �˴��ο�replacement_new, �Ӷ�����ȡ���ڴ棬����ʼ����T����Ҫ��Ĭ�Ϲ��캯����
		*/
		assert(sizeof(T) < _obj_size);
		char* buf = nullptr;
		if (!_queue.empty())
		{
			buf = _queue.front();
			_queue.pop();
		}
		T* ret = new(buf) T(args);
		return ret;
	}

	template <class T>
	void push_directly(T* mem, bool has_destruct_func = true)
	{
		/*
		* ����
		*/
		assert(sizeof(T) < _obj_size);
		if (has_destruct_func)
			mem->T::~T();
		else
			memset(mem, 0, sizeof(T));
		_queue.push(static_case<void*> mem);
		return true;
	}

	template<class  T, class ... Targs>
	T* pop_in_queue(Targs&... args)
	{
		/*
		* ����
		*/
		std::unique_lock<std::mutex> lock(_pool_mutex);
		return pop_directly(args);
	}

	template <class T>
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
