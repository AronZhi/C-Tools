#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <memory>
#include <queue>

template<class T>
class MemoryPool
{
public:
	MemoryPool() : _mem(NULL) {}
	~MemoryPool()
	{
		if (_mem)
			free(_mem)
		_mem = NULL;

	}

	bool Malloc(int32_t obj_count)
	{
		if (NULL == _mem)
		{
			_mem = (char*)malloc(obj_count * sizeof(T));
			if (_mem)
			{
				char* p = _mem;
				while (p)
				{
					_avaliable_ptrs.push(p);
					p += obj_size;
				}
				return true;
			}

		}
		return false;
	}

	T* Fetch()
	{
		T* ret = NULL;
		if (!_avaliable_ptrs.empty())
		{
			char* p = _avaliable_ptrs.front();
			_avaliable_ptrs.pop();
			ret = static_cast<T*>(p);
			ret->T::T();
		}
		return ret;
	}

	void GiveBack(T* ptr)
	{
		ptr->T::~T();
		char* p = ptr;
		memset(p, 0, sizeof(T))
		_avaliable_ptrs.push(p);
	}

private:
	std::queue<char*> _avaliable_ptrs;
	char* _mem;
};

#endif // MEMORY_POOL