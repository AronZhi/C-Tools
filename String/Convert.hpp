#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>
#include <locale>
#include <codecvt>

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

#endif // CONVERT_HPP
