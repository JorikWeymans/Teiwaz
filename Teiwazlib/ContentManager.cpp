#include "tyrpch.h"
#include "ContentManager.h"
#include <algorithm>
#include "Font.h"
#include "Texture.h"
#include "Animation.h"
#include <functional>
#include <sstream>
#include "BinaryReader.h"
#include <filesystem>
#include <direct.h>
#include "StringManipulation.h"
#include "./Editor/ETabItem.h"

#define ANIMATION_SUFFIX ".tyrAnimation"
tyr::ContentManager* tyr::ContentManager::pInstance = nullptr;


tyr::ContentManager::ContentManager()
	: m_IsInitialized(false)
	, m_DataFolder("")
	, m_pTextures(std::vector<Texture*>())
	, m_pFonts(std::vector<Font*>())
{
}

tyr::ContentManager::~ContentManager()
{
	std::for_each(m_pTextures.begin(), m_pTextures.end(),		[](auto* p) {SAFE_DELETE(p)});
	std::for_each(m_pFonts.begin(), m_pFonts.end(),			[](auto* p) {SAFE_DELETE(p)});
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(),	[](auto* p) {SAFE_DELETE(p) });
}

tyr::ContentManager* tyr::ContentManager::GetInstance()
{
	if(!pInstance)
	{
		pInstance = new ContentManager();
	}
	return pInstance;
}

void tyr::ContentManager::Initialize(const std::string& dataFolder, const std::string& sceneFolder, const std::string& animationFolder)
{
	UNREFERENCED_PARAMETER(sceneFolder);
	UNREFERENCED_PARAMETER(animationFolder);
	if(!m_IsInitialized)
	{
		m_DataFolder = dataFolder;
		m_SceneFolder = sceneFolder;
		m_AnimationFolder = animationFolder;
		
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
	delete pInstance;
	pInstance = nullptr;
}

TextureID tyr::ContentManager::LoadTexture(const std::string& path)
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
FontID tyr::ContentManager::LoadFont(const std::string& path)
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
AnimationID tyr::ContentManager::LoadAnimation(const std::string& fileName)
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), fileName);

	if (found != m_pAnimations.end())
	{
		return static_cast<AnimationID>(std::distance(m_pAnimations.begin(), found));
	}


	//Loading animation if it does not already exist
	std::stringstream ss;
	ss << m_DataFolder << m_AnimationFolder << fileName << ANIMATION_SUFFIX;

	BinaryReader reader{ ss.str() };

	ULONG64 header = reader.Read<ULONG64>();
	if (header != 0x78b109c3)
	{
#ifdef USE_IM_GUI
		SDXL_ImGui_ConsoleLogError("This is not an tyrAnimation");
#else
		THROW_ERROR(L"This is not an animation");
#endif
	}

	const std::string animationName = reader.Read<std::string>();
	const float tpf = reader.Read<float>();
	const UINT elements = reader.Read<UINT>();

	SpritePositions positions;

	for (UINT i{ 0 }; i < elements; ++i)
	{
		positions.insert({ i, Rect(reader.Read<Rect_POD>()) });
	}
	m_pAnimations.emplace_back(new Animation(animationName, tpf, std::move(positions)));




	return static_cast<AnimationID>(m_pAnimations.size() - 1);
}


tyr::Texture* tyr::ContentManager::GetTexture(TextureID id)
{
	if (id >= m_pTextures.size()) return nullptr;
	
	return m_pTextures[id];
}
tyr::Font const* tyr::ContentManager::GetFont(FontID id)
{
	if (id >= m_pFonts.size()) return nullptr;

	return m_pFonts[id];
}
tyr::Animation* tyr::ContentManager::GetAnimation(AnimationID id)
{
	if (id >= m_pAnimations.size()) return nullptr;

	return m_pAnimations[id];
}

tyr::Animation* tyr::ContentManager::GetAnimation(std::string& name)
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), name);
	if (found != m_pAnimations.end())
		return *found;

	return nullptr;
	
}

std::vector<tyr::TabItem> tyr::ContentManager::GetAnimationsInFolder() const
{
	std::vector<tyr::TabItem> files;

	std::string folder = m_DataFolder + m_AnimationFolder;
#pragma warning (suppress : 6031)
	_mkdir(folder.c_str()); //making dir if dir does not exist
	for (auto& entry : std::filesystem::directory_iterator(folder))
	{

		std::string filename{ GetFileFromPath(entry.path().string()) };

		if (DoesExtensionMatch(filename, ANIMATION_SUFFIX, false))
		{
			RemoveExtension(filename);
			files.emplace_back(TabItem(entry.path().string(), filename));
		}
	}

	return files;
	
}

