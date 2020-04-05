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

void tyr::ContentManager::Destroy()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

tyr::Texture* tyr::ContentManager::LoadTexture(const std::wstring& path)
{
	auto found = std::find(m_pTextures.begin(), m_pTextures.end(), path);

	if(found != m_pTextures.end())
	{
		return *found;
	}
	
	auto pTemp = new Texture(m_DataFolder, path);
	m_pTextures.emplace_back(pTemp);
	return pTemp;
}
tyr::Font* tyr::ContentManager::LoadFont(const std::wstring& path)
{
	auto found = std::find(m_pFonts.begin(), m_pFonts.end(), path);

	if (found != m_pFonts.end())
	{
		return *found;
	}

	auto pTemp = new Font(m_DataFolder, path);
	m_pFonts.emplace_back(pTemp);
	return pTemp;
}


