#pragma once
#define THROW_ERROR_IF_FAILED(hr, msg) if(FAILED(hr) throw tyr::TyrException(hr, msg, __FILE__, __FUNCTION__, __LINE__)
#define THROW_ERROR(msg) throw tyr::TyrException(msg, __FILE__, __FUNCTION__, __LINE__)
namespace tyr
{
	class TyrException final
	{
	public:
		TyrException(HRESULT hr, const std::wstring& msg, const std::string& file, const std::string& function, int line);
		TyrException(const std::wstring& msg, const std::string& file, const std::string& function, int line);
		const wchar_t* what() const;
	private:
		std::wstring m_Message;
	};


}
