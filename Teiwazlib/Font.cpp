#include "tyrpch.h"
#include "Font.h"

tyr::Font::Font(const std::string& dataFolder, const std::string& path)
	: m_pFont(nullptr)
	, m_Hash(std::hash<std::string>{}(path))
{
	const std::string completePath = dataFolder + path;
	SDXL_CreateFont(&m_pFont, std::wstring(completePath.begin(), completePath.end()));

}

tyr::Font::~Font()
{
	SDXL_DestroyFont(&m_pFont);
}

SDXL::SDXLFont* tyr::Font::SDXL() const
{
	return m_pFont;
}

bool tyr::operator==(Font* lhs, const std::string& rhs)
{
	const size_t rhsHash = std::hash<std::string>{}(rhs);
	return (lhs->m_Hash == rhsHash);
}
