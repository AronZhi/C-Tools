#ifndef PRINT_HPP
#define PRINT_HPP

#include <sstream>
// #include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

template <class cls>
void _wprintOne(char splite, std::wstringstream& ws, cls& param)
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
		ws << param << splite;
}

template <>
inline void _wprintOne<std::string>(char splite, std::wstringstream& ws, std::string& param)
{
	ws << param.c_str() << splite;
}

template <class... Args>
void wprint(Args... args)
{
	std::wstringstream ws(L"");
	if (sizeof...(args) > 0)
		(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(' ', ws, args), 0)...};
	wprintf(L"%s\n", ws.str().c_str());
}

template<class T, class... Args>
void wprint(const std::list<T>& lst, Args... args)
{
	std::wstringstream ws(L"");
	ws << '[';
	if (lst.size() > 0)
	{
		for (auto item : lst)
			_wprintOne<decltype(item)>(',', ws, item);
	}
	ws << ']';
	if (sizeof...(args) > 0)
	{
		ws << ' ';
		(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(' ', ws, args), 0)...};
	}
	wprintf(L"%s\n", ws.str().c_str());
}

template<class T, class... Args>
void wprint(const std::vector<T>& vec, Args... args)
{
	std::wstringstream ws(L"");
	ws << '[';
	if (vec.size() > 0)
	{
		for (auto item : vec)
			_wprintOne<decltype(item)>(',', ws, item);
	}
	ws << ']';
	if (sizeof...(args) > 0)
	{
		ws << ' ';
		(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(' ', ws, args), 0)...};
	}
	wprintf(L"%s\n", ws.str().c_str());
}

template<class K, class V, class... Args>
void wprint(const std::map<K, V>& map, Args... args)
{
	std::wstringstream ws(L"");
	ws << '{';
	if (map.size() > 0)
	{
		for (auto item : map)
		{
			_wprintOne<decltype(item.first)>(':', ws, item.first);
			_wprintOne<decltype(item.second)>(',', ws, item.second);
		}
	}
	ws << '}';
	if (sizeof...(args) > 0)
	{
		ws << ' ';
		(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(' ', ws, args), 0)...};
	}
	wprintf(L"%s\n", ws.str().c_str());
}

#endif // PRINT_HPP