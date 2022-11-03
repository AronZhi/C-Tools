#ifndef SPLIT_HPP
#define SPLIT_HPP

#include <vector>
#include <string>
#include <regex>

void split(const std::string& src, const std::string& delimiter, std::vector<std::string>& ret)
{
	std::regex re(delimiter);
	/*
	std::vector<std::string> temp{
				std::sregex_token_iterator(src.begin(), src.end(), re, -1),
				std::sregex_token_iterator() };
	*/
	ret.clear();
	ret = { std::sregex_token_iterator(src.begin(), src.end(), re, -1),std::sregex_token_iterator() };
}

#endif // SPLIT_HPP
