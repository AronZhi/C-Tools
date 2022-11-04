#ifndef PRINT_HPP
#define PRINT_HPP

#include <sstream>
// #include <iostream>
#include <string>
#include <vector>
#include <list>

template <class cls>
void _wprintOne(std::wstringstream& ws, cls param)
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
		ws << param << ' ';
}

template <>
void _wprintOne<std::string>(std::wstringstream& ws, std::string param)
{
	ws << param.c_str() << L' ';
}

template<class T, class Allocator>
void _wprintContainer(std::wstringstream& ws, const std::vector<T, Allocator>& vec)
{
	if (vec.empty())
		return;

	for (auto item : vec)
		_wprintOne<decltype(item)>(ws, item);
}

template<class T, class Allocator>
void _wprintContainer(std::wstringstream& ws, const std::list<T, Allocator>& lst)
{
	if (lst.empty())
		return;

	for (auto item : lst)
		_wprintOne<decltype(item)>(ws, item);
}

template <class... Args>
int wprint(Args... args)
{
	std::wstringstream ws(L"");
	int ret = sizeof...(args);
	(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(ws, args), 0)...};
	wprintf(L"%s\n", ws.str().c_str());
	return ret;
}

#endif // PRINT_HPP