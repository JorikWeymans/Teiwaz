#include "tyrpch.h"
#include "TyrException.h"
#include <comdef.h>
#include <sstream>
tyr::TyrException::TyrException(HRESULT hr, const std::wstring& msg, const std::string& file,
	const std::string& function, int line)
{
	const _com_error error(hr);
	std::wstringstream ss;
	ss << L"Msg:\t" << msg << std::endl;
	ss << L"  \t" << error.ErrorMessage() << std::endl;
	const auto fileShort = file.substr(file.find_last_of('\\') + 1);
	ss << L"File:\t" <<  std::wstring(fileShort.begin(), fileShort.end()) << std::endl;

	ss << L"Func:\t" << std::wstring(function.begin(), function.end()) << std::endl;
	ss << L"Line:\t" << line << std::endl;

	m_Message = ss.str();
}

tyr::TyrException::TyrException(const std::wstring& msg, const std::string& file, const std::string& function, int line)
{
	std::wstringstream ss;
	ss << L"Msg:\t" << msg << std::endl;
	const auto fileShort = file.substr(file.find_last_of('\\') + 1);
	ss << L"File:\t" << std::wstring(fileShort.begin(), fileShort.end()) << std::endl;

	ss << L"Func:\t" << std::wstring(function.begin(), function.end()) << std::endl;
	ss << L"Line:\t" << line << std::endl;

	m_Message = ss.str();
}

const wchar_t* tyr::TyrException::what() const
{
	return m_Message.c_str();
}
