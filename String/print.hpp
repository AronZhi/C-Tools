#pragma once
#include <iostream>
#include <string>

template <class cls>
void print_one(std::wofstream& stream, cls param)
{
	stream << param << ' ';
}

template <>
void print_one<std::string>(std::wofstream& stream,std::string param)
{
	stream << param.c_str() << ' ';
}

template <class... Args>
int print(Args... args)
{
	int ret = sizeof...(args);
	(void)std::initializer_list<int> {(std::wcout << ' ' << args << ' ', 0)...};
	std::wcout << std::endl;
	return ret;
}