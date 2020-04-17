#include "tyrpch.h"
#include "ContentManager.h"
#include <algorithm>
#include "Font.h"
#include "Texture.h"
#include <functional>
tyr::ContentManager* tyr::ContentManager::m_pInstance = nullptr;


tyr::ContentManager::ContentManager()
	: m_IsInitialized(false)
	, m_DataFolder(L"")
	, m_pTextures(std::vector<Texture*>())
	, m_pFonts(std::vector<Font*>())
{
}

tyr::ContentManager::~ContentManager()
{
	std::for_each(m_pTextures.begin(), m_pTextures.end(), [](auto* p) {delete p; p = nullptr; });
	std::for_each(m_pFonts.begin(), m_pFonts.end(), [](auto* p) {delete p; p = nullptr; });

}

tyr::ContentManager* tyr::ContentManager::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new ContentManager();
	}
	return m_pInstance;
}

void tyr::ContentManager::Initialize(const std::wstring& dataFolder)
{
	if(!m_IsInitialized)
	{
		m_DataFolder = dataFolder;
		m_IsInitialized = true;
	}
}
std::string tyr::ContentManager::GetDataFolder() const
{
#pragma warning (suppress : 4244)
	return std::string(m_DataFolder.begin(), m_DataFolder.end());
}

void tyr::ContentManager::Destroy()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

TextureID tyr::ContentManager::LoadTexture(const std::wstring& path)
{
	auto found = std::find(m_pTextures.begin(), m_pTextures.end(), path);

	if(found != m_pTextures.end())
	{
		return static_cast<TextureID>(std::distance(m_pTextures.begin(), found));
	}
	
	auto pTemp = new Texture(m_DataFolder, path);
	m_pTextures.emplace_back(pTemp);
	return static_cast<TextureID>(m_pTextures.size() - 1);
}
FontID tyr::ContentManager::LoadFont(const std::wstring& path)
{
	auto found = std::find(m_pFonts.begin(), m_pFonts.end(), path);

	if (found != m_pFonts.end())
	{
		//return 0;
		return static_cast<FontID>(std::distance(m_pFonts.begin(), found));
		
	}

	auto pTemp = new Font(m_DataFolder, path);
	m_pFonts.emplace_back(pTemp);
	return static_cast<FontID>(m_pFonts.size() - 1);
}

tyr::Font const* tyr::ContentManager::GetFont(FontID id)
{
	return m_pFonts[id];
}

tyr::Texture* tyr::ContentManager::GetTexture(TextureID id)
{
	return m_pTextures[id];
}


