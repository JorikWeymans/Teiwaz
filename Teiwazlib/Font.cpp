#include "tyrpch.h"
#include "Font.h"

tyr::Font::Font(const std::wstring& dataFolder, const std::wstring& path)
	: m_pFont(nullptr)
	, m_Hash(std::hash<std::wstring>{}(path))
{
	const std::wstring completePath = dataFolder + path;
	SDXL_CreateFont(&m_pFont, completePath);

}

tyr::Font::~Font()
{
	SDXL_DestroyFont(&m_pFont);
}

SDXL::SDXLFont* tyr::Font::SDXL() const
{
	return m_pFont;
}

bool tyr::operator==(Font* lhs, const std::wstring& rhs)
{
	const size_t rhsHash = std::hash<std::wstring>{}(rhs);
	return (lhs->m_Hash == rhsHash);
}
