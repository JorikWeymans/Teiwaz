#include "tyrpch.h"
#include "Texture.h"

tyr::Texture::Texture(const std::wstring& dataFolder, const std::wstring& path)
	: m_pImage(nullptr)
	, m_Hash(std::hash<std::wstring>{}(path))
	, m_Dimension(0.f,0.f)
{
	const std::wstring completePath = dataFolder + path;

	SDXL_CreateImage(&m_pImage, completePath);
	
	const auto di = SDXL_GetImageDimensions(m_pImage);

	m_Dimension.x = di.x;
	m_Dimension.y = di.y;
}

tyr::Texture::~Texture()
{
	SDXL_DestroyImage(&m_pImage);
}

SDXL::SDXLImage* tyr::Texture::SDXL() const
{
	return m_pImage;
}

const tyr::Vector2& tyr::Texture::GetDimension() const
{
	return m_Dimension;
}

bool tyr::operator==(Texture* lhs, const std::wstring& rhs)
{
	const size_t rhsHash = std::hash<std::wstring>{}(rhs);
	return (lhs->m_Hash == rhsHash);
}
