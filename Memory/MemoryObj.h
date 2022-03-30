#ifndef MEMORY_OBJ
#define MEMORY_OBJ

template<class T>
class MemoryObj
{
public:
	void RemoveData()
	{
		/*remove data in member*/
		return;
	}

	T& GetData() { return _member; }

private:
	T _member;
};

#endif // MEMORY_OBJ
