#pragma once
#include <iostream>

template <class... Args>
int print(Args... args)
{
	int ret = sizeof...(args);
	(void)std::initializer_list<int> {(std::wcout << ' ' << args << ' ', 0)...};
	std::wcout << std::endl;
	return ret;
}