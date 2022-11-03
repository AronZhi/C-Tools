#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class cls>
void _wprintOne(cls param)
{
	const char* type_name = typeid(param).name();
	char* p = const_cast<char*>(type_name);
	bool invalid = true;
	static char invalid_print_type[5] = { 'c', 'l', 'a', 's', 's' };
	for (int i = 0; i < 5; ++i)
	{
		if (*p != invalid_print_type[i])
		{
			invalid = false;
			break;
		}
	}
	if (invalid)
		return;
	else
		std::wcout << param << ' ';
}

template <>
void _wprintOne<std::string>(std::string param)
{
	std::wcout << param.c_str() << ' ';
}

template<class T, class Allocator>
void _wprintContainer(const std::vector<T, Allocator>& vec)
{
	if (vec.empty())
		return;

	for (auto item : vec)
		_wprintOne<decltype(item)>(item);
}

template<class T, class Allocator>
void _wprintContainer(const std::list<T, Allocator>& lst)
{
	if (lst.empty())
		return;

	for (auto item : lst)
		_wprintOne<decltype(item)>(item);
}

template <class... Args>
int wprint(Args... args)
{
	int ret = sizeof...(args);
	(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(args), 0)...};
	std::wcout << std::endl;
	return ret;
}

#endif // PRINT_HPP