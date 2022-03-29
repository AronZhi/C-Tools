#ifndef CONVERT_H
#define CONVERT_H

#include <string>
#include <locale>
#include <codecvt>

void WsToS(const std::wstring& src, std::string& ret)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
	ret = wcv.to_bytes(src);
}

bool SToWs(const std::string& src, std::wstring& ret)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
	ret = wcv.from_bytes(src);
}

#endif // CONVERT_H
