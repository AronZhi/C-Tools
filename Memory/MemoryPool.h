#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <memory>
#include <queue>

template<class T>
class MemoryPool
{
public:
	MemoryPool() : _mem(nullptr) {}
	~MemoryPool()
	{
		if (_mem)
			delete[] _mem;
	}

	bool Malloc(int32_t obj_count)
	{
		_mem = new T[obj_count];
		if (_mem)
		{
			for (int i = 0; i < obj_count; i++)
			{
				T* ptr = _mem + i;
				_avaliable_ptrs.push(ptr);
			}
			return true;
		}
		return false;
	}

	T* Fetch()
	{
		T* ret = NULL;
		if (!_avaliable_ptrs.empty())
		{
			ret = _avaliable_ptrs.front();
			_avaliable_ptrs.pop();
		}
		return ret;
	}

	void GiveBack(T* ptr, void (*clear_func)(void)=nullptr)
	{
		if (clear_func)
			clear_func();
		_avaliable_ptrs.push(ptr);
	}

private:
	std::queue<T*> _avaliable_ptrs;
	T* _mem;
};

#endif // MEMORY_POOL