#include "tyrpch.h"
#include "Texture.h"

tyr::Texture::Texture(const std::wstring& dataFolder, const std::wstring& path)
	: m_pImage(nullptr)
	, m_Hash(std::hash<std::wstring>{}(path))
{
	const std::wstring completePath = dataFolder + path;

	SDXL_CreateImage(&m_pImage, completePath);
	
}

tyr::Texture::~Texture()
{
	SDXL_DestroyImage(&m_pImage);
}

SDXL::SDXLImage* tyr::Texture::SDXL() const
{
	return m_pImage;
}

bool tyr::operator==(Texture* lhs, const std::wstring& rhs)
{
	const size_t rhsHash = std::hash<std::wstring>{}(rhs);
	return (lhs->m_Hash == rhsHash);
}
