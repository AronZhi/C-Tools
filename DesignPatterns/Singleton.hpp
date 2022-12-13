#ifndef SINGLE_INST
#define SINGLE_INST

/*使用once_flag和call_oncel来保证线程安全*/
#include <mutex>
#include <memory>

template <typename T>
class Singleton
{
public:
	static T& getInstance()
	{
		static std::once_flag flag;
		std::call_once(flag, [&]() { __inst.reset(new T); });
		return *__inst;
	}

protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;

protected:
	static std::unique_ptr<T> __inst; 
};

template <typename T>
std::unique_ptr<T> Singleton<T>::__inst(nullptr); // 非模板的情况下需要在cpp文件进行初始化 std::unique_ptr<T> T::_inst(nullptr) 否则链接错误. 

/*
C++11之后静态变量初始化是线程安全的
使用静态局部变量能延迟构造实现懒汉式单例

template <typename T> 
class Singleton
{
public:
	static T& getInstance()
	{		
		static T t;
		return t;
	}

	~Singleton() = default;

protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
};
*/
#endif // SINGLE_INST