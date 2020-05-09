#include "tyrpch.h"
#include "Texture.h"
#include "TyrException.h"
#include "StringManipulation.h"
#include <sys/types.h>
#include <sys/stat.h>
tyr::Texture::Texture(const std::string& dataFolder, const std::string& name)
	: m_pImage(nullptr)
	, m_Hash(std::hash<std::string>{}(name))
	, m_Name(name)
	, m_Dimension(0.f,0.f)
{
	const std::string completePath = dataFolder + name;

	//https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
	struct stat info{};
	if (stat(completePath.c_str(), &info) != 0)
	{
		THROW_ERROR(L"Image does not exist");
	}
	else
	{
		if(!DoesExtensionMatch(completePath, "png"))
		{
			THROW_ERROR(L"Can only load png");
		}
		
		
#ifdef USE_IM_GUI
		const std::string what = "[LOADED]   " + m_Name;
		SDXL_ImGui_ConsoleLog(what.c_str());
#endif
	}
	
	SDXL_CreateImage(&m_pImage, std::wstring(completePath.begin(), completePath.end()));
	
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

const std::string& tyr::Texture::GetName() const
{
	return m_Name;
}

bool tyr::operator==(Texture* lhs, const std::string& rhs)
{
	if (!lhs) return false;
	
	const size_t rhsHash = std::hash<std::string>{}(rhs);
	return (lhs->m_Hash == rhsHash);
}
