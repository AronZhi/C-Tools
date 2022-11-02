#pragma once
#include <iostream>
#include <string>
#include "Convert.h"

template <class cls>
void _wprintOne(cls param)
{
	std::wcout << param << ' ';
}

template <>
void _wprintOne<std::string>(std::string param)
{
	std::wcout << param.c_str() << ' ';
}

template <class... Args>
int wprint(Args... args)
{
	int ret = sizeof...(args);
	(void)std::initializer_list<int> {(_wprintOne<decltype(args)>(args), 0)...};
	std::wcout << std::endl;
	return ret;
}