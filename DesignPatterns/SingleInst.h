#ifndef SINGLE_INST
#define SINGLE_INST

/*使用once_flag和call_oncel来保证线程安全*/
#include <mutex>
#include <memory>

template <typename T>
class SingleInst
{
public:
	static T& get_instance()
	{
		static std::once_flag flg;
		std::call_once(flag, [&]() { __inst.reset(new T); });
		return *__inst;
	}

private:
	SingleInst() = default;
	SingleInst(const SingleInst&) = delete;
	SingleInst& operate = (const SingleInst&) = delete;

private:
	static std::unique_ptr<T> __inst;
};

/*
C++11之后静态变量初始化是线程安全的
使用静态局部变量能延迟构造实现懒汉式单例

template <typename T> 
class SingleInst
{
public:
	static T& GetInstance()
	{		
		static T t;
		return t;
	}

	~SingleInst() = default;

private:
	SingleInst() = default;
	SingleInst(const SingleInst&) = delete;
	SingleInst& operate = (const SingleInst&) = delete;
};
*/
#endif // SINGLE_INST