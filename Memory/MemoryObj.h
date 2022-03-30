#ifndef MEMORY_OBJ
#define MEMORY_OBJ

template<class T>
class MemoryObj
{
public:
	MemoryObj() {}
	MemoryObj(const MemoryObj& src): _member(src._member) {}
	~MemoryObj() {}

	void RemoveData()
	{
		/*remove data in member*/
		return;
	}

	T& GetDataRef() { return _member; }
	T* GetDataPtr() { return &_member; }
	T GetData() { return _member; }

private:
	T _member;
};

#endif // MEMORY_OBJ
