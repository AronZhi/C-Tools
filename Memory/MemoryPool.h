#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <memory>
#include <deque>
#include "MemoryObj.h"

template<class T>
class MemoryPool
{
public:
	typedef MemoryObj<T>* MemoryObj_Ptr;

	MemoryPool(int32_t obj_count) : _count(obj_count), _mem(nullptr) {}
	~MemoryPool()
	{
		if (_mem)
			delete[] _mem;
	}

	bool Create()
	{
		_mem = new MemoryObj<T>[_count];
		if (_mem)
		{
			for (int i = 0; i < _count; i++)
			{
				MemoryObj_Ptr ptr = _mem + i;
				_avaliable_ptrs.push_back(ptr);
			}
			return true;
		}
		return false;
	}

	MemoryObj_Ptr Fetch()
	{
		MemoryObj_Ptr ret = NULL;
		if (!_avaliable_ptrs.empty())
		{
			ret = _avaliable_ptrs.front();
			_avaliable_ptrs.pop_front();
		}
		return ret;
	}

	void GiveBack(MemoryObj_Ptr ptr)
	{
		ptr->RemoveData();
		_avaliable_ptrs.push_back(ptr);
	}

private:
	int32_t _count;
	std::deque<MemoryObj_Ptr> _avaliable_ptrs;
	MemoryObj_Ptr _mem;
};

#endif // MEMORY_POOL