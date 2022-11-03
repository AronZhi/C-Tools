#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <regex>

void ws2s(const std::wstring& src, std::string& ret)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
	ret = wcv.to_bytes(src);
}

void s2ws(const std::string& src, std::wstring& ret)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
	ret = wcv.from_bytes(src);
}

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

#endif // DATA_HPP