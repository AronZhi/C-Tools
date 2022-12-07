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

void replace(std::string& str, char target_char, char replace_char)
{
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if (*it == target_char)
		{
			*it = replace_char;
		}
	}
}

void replace(std::string& src, const std::string& target_str, const std::string& replace_str)
{
	std::string::size_type pos = 0;
	std::string::size_type target_size = target_str.length();
	std::string::size_type replace_size = replace_str.length();
	while((pos = src.find(target_str, pos)) != std::string::npos)
	{
		src.replace(pos, target_size, replace_str);
		pos += replace_size;
	}
}

#endif // DATA_HPP