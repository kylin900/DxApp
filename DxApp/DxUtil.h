#pragma once

#include <windows.h>
#include <string>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

class DxException
{
public:
	DxException() = default;
	DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

	std::wstring ToString()const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;
};

#ifndef ThrowIfFailed
#define GFX_THROW_INFO(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}
#endif

inline std::wstring AnsiToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

template<typename T>
T wrap_angle(T theta)
{
	const T modded = fmod(theta, ( T )2.0 * (T)PI_D);
	return ( modded > (T)PI_D ) ?
		( modded - ( T )2.0 * (T)PI_D ) :
		modded;
}