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
#include "TyrException.h"
#include <filesystem>
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include "BinStructureHelpers.h"

#define CONTENT_PATH "./TyrBin/Content.tyr"
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

void tyr::ContentManager::Initialize(const std::string& dataFolder, const std::string& sceneFolder,
																	const std::string& textureFolder,
																	const std::string& fontFolder,
																	const std::string& animationFolder)
{
	UNREFERENCED_PARAMETER(sceneFolder);
	UNREFERENCED_PARAMETER(animationFolder);
	if(!m_IsInitialized)
	{
		m_DataFolder = dataFolder;
		m_SceneFolder = sceneFolder;
		m_TextureFolder = textureFolder;
		m_FontFolder = fontFolder;
		m_AnimationFolder = animationFolder;

		m_IsInitialized = true;
	}
}

void tyr::ContentManager::InitializeFromFile()
{
	BinaryReader reader(CONTENT_PATH);

	if (!reader.IsOpen())
		THROW_ERROR(L"Could not open file");
	
	ULONG64 header = reader.Read<ULONG64>();
	if (header != 0x30140623)
	{
		THROW_ERROR(L"This is not the contentFile");
	}

	m_DataFolder = reader.Read<std::string>();
	
	m_SceneFolder = reader.Read<std::string>();
	m_TextureFolder = reader.Read<std::string>();
	m_FontFolder = reader.Read<std::string>();

	m_AnimationFolder = reader.Read<std::string>();

	ContentType type = reader.Read<ContentType>();
	while(type != ContentType::End)
	{
		//all types (except end) have a size and a size
		UINT size = reader.Read<UINT>();

		switch (type)
		{
		case ContentType::Texture:
			m_pTextures.resize(size, nullptr);
			
			for(UINT i {0}; i < size; i++)
			{
				std::string name = reader.Read<std::string>();
				m_pTextures[i] = new Texture(m_DataFolder + m_TextureFolder, name);
			}

			break;
		case ContentType::Font:
			if(size > 0)
				THROW_ERROR(L"Font is not implemented yet");

			break;
		case ContentType::Animation: 
			m_pAnimations.resize(size, nullptr);
			
			for (UINT i{ 0 }; i < size; i++)
			{
				std::string name = reader.Read<std::string>();
				LoadAnimation(name, i);
			}
				
			
			break;
		case ContentType::End:
			THROW_ERROR(L"Type end should not be read");
		default:
			THROW_ERROR(L"This Type is invalid");
			;
		}

		type = reader.Read<ContentType>();
	}
	
	
}

std::string tyr::ContentManager::GetDataFolder() const
{
#pragma warning (suppress : 4244)
	return std::string(m_DataFolder.begin(), m_DataFolder.end());
}

#ifdef USE_IM_GUI
void tyr::ContentManager::RenderEditor()
{


	
	static bool openContentManager = false;
	
	if (SDXL_ImGui_Selectable("ContenManager",false , SDXL_ImGuiSelectableFlags_DontClosePopups, SDXL::Float2(90,20)))
	{
		openContentManager = !openContentManager;
		if(openContentManager)
		{
			SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ 100.f,100.f });
			SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ 500.f, 300.f });
		}
	}

	static bool openFilePathSettings = false;

	if(openContentManager)
	{
		
		static int selected = -1;

		if (SDXL_ImGui_Begin("ContentManager##ContentManager", &openContentManager, SDXL_ImGuiWindowFlags_NoSavedSettings | SDXL_ImGuiWindowFlags_MenuBar ))
		{
			if(SDXL_ImGui_BeginMenuBar())
			{
				if(SDXL_ImGui_BeginMenu("MenuItem##ContentManger"))
				{
					if(SDXL_ImGui_MenuItem("File paths"))
					{

						openFilePathSettings = true;


						strcpy_s(m_CharDataPath, m_DataFolder.c_str());
						strcpy_s(m_CharSceneFolder, m_SceneFolder.c_str());
						strcpy_s(m_CharAnimationFolder, m_AnimationFolder.c_str());
						strcpy_s(m_CharTextureFolder, m_TextureFolder.c_str());
						
					}
					SDXL_ImGui_EndMenu();
				}
				SDXL_ImGui_EndMenuBar();
			}
			if(SDXL_ImGui_BeginChild("child#ContentManager", SDXL::Float2(100,0), true))
			{
				
				
				if (SDXL_ImGui_Selectable("Textures", selected == 1, SDXL_ImGuiSelectableFlags_AllowDoubleClick | SDXL_ImGuiSelectableFlags_DontClosePopups))
				{
					selected = 1;

				}
				if (SDXL_ImGui_Selectable("Scenes", selected == 2, SDXL_ImGuiSelectableFlags_AllowDoubleClick | SDXL_ImGuiSelectableFlags_DontClosePopups))
				{
					selected = 2;

				}
				SDXL_ImGui_EndChild();
			}
			SDXL_ImGui_SameLine();


		}




		if (selected == 1)
		{
			if (SDXL_ImGui_BeginChild("TextureWindow##ContentManager", SDXL::Float2(0,0), false, SDXL_ImGuiWindowFlags_AlwaysAutoResize))
			{
				TextureWindow();
				SDXL_ImGui_EndChild();
			}
		}
		
		SDXL_ImGui_End();
	}

	static bool areContentSettingsOpen = true;
	if(openFilePathSettings)
	{
		SDXL_ImGui_OpenPopup("ContentManager Settings");
		openFilePathSettings = false;
		areContentSettingsOpen = true;

		//SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ 100.f,100.f });
		SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ 500.f, 300.f });
	}

	static bool pathHasChanged = false;
	SDXL_ImGuiWindowFlags flags = SDXL_ImGuiWindowFlags_NoMove | SDXL_ImGuiWindowFlags_NoResize;
	if (pathHasChanged) flags |= SDXL_ImGuiWindowFlags_UnsavedDocument;
	
	if (SDXL_ImGui_BeginPopupModal("ContentManager Settings", &areContentSettingsOpen, flags))
	{
		//Data Path
		if(SDXL_ImGui_InputText("Data Path##ContentManager", m_CharDataPath, ARRAY_SIZE(m_CharDataPath)))
			pathHasChanged = true;

		std::filesystem::path path = m_CharDataPath;
		SDXL_ImGui_TextDisabled("[EPath]%s" , std::filesystem::absolute(path).string().c_str());

		//Scene Folder
		if(SDXL_ImGui_InputText("Scene Folder##ContentManager", m_CharSceneFolder, ARRAY_SIZE(m_CharSceneFolder)))
			pathHasChanged = true;
		
		path = std::string(m_CharDataPath) + std::string(m_CharSceneFolder);
		SDXL_ImGui_TextDisabled("[EPath]%s", std::filesystem::absolute(path).string().c_str());

		//Animation Folder
		if(SDXL_ImGui_InputText("Animation folder##ContentManager", m_CharAnimationFolder, ARRAY_SIZE(m_CharAnimationFolder)))
			pathHasChanged = true;
		
		path = std::string(m_CharDataPath) + std::string(m_CharAnimationFolder);
		SDXL_ImGui_TextDisabled("[EPath]%s", std::filesystem::absolute(path).string().c_str());
		
		//Texture Folder
		if (SDXL_ImGui_InputText("Texture folder##ContentManager", m_CharTextureFolder, ARRAY_SIZE(m_CharTextureFolder)))
			pathHasChanged = true;

		path = std::string(m_CharDataPath) + std::string(m_CharTextureFolder);
		SDXL_ImGui_TextDisabled("[EPath]%s", std::filesystem::absolute(path).string().c_str());
		

		SDXL_ImGui_Separator();
		
		if(SDXL_ImGui_Button("Cancel##SettingsContentManager"))
		{
			pathHasChanged = false;
			SDXL_ImGui_CloseCurrentPopup();

		}
		SDXL_ImGui_SameLine();
		if(SDXL_ImGui_Button("Save"))
		{
			m_DataFolder = std::string(m_CharDataPath);
			m_SceneFolder = std::string(m_CharSceneFolder);
			m_AnimationFolder = std::string(m_CharAnimationFolder);

			pathHasChanged = false;
			Save();
			SDXL_ImGui_CloseCurrentPopup();
		}
		
		SDXL_ImGui_EndPopup();
	}


}

void tyr::ContentManager::EditorTextureSelector(const char* imGuiID, TextureID& textureID)
{
	const char* item_current = m_pTextures[textureID]->GetName().c_str();

	SDXL_ImGui_SetNextItemWidth(219.f);
	if (SDXL_ImGui_BeginCombo(imGuiID, item_current, SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < static_cast<UINT>(m_pTextures.size()); n++)
		{
			bool is_selected = (item_current == m_pTextures[n]->GetName().c_str());

			if (SDXL_ImGui_Selectable(m_pTextures[n]->GetName().c_str(), is_selected))
				textureID = n;
			if (is_selected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}
	
}

void tyr::ContentManager::Save()
{
	BinaryWriter writer(CONTENT_PATH);

	//Binsctructure
	// Long double -> Header (JorikWeymansTyr hashed via Adler32 to this value)
	// String -> DataFolder;
	// String -> SceneFolder;
	// String -> AnimationFolder;
	// String -> TextureFolder
	//
	// ContentType::Texture
	// amount of textures
	// foreach(texture.Name)
	//
	// ContentType::Animation
	// amount of animations
	// foreach(animation.Name)
	//
	// ContentType::End (Marking EOF)

	ULONG64 header = 0x30140623;
	writer.Write(header); //Header
	
	writer.WriteString(m_DataFolder);
	
	writer.Write(m_SceneFolder);
	writer.Write(m_TextureFolder);
	writer.Write(m_FontFolder);
	writer.Write(m_AnimationFolder);

	
	writer.Write(ContentType::Texture);
	writer.Write(static_cast<UINT>(m_pTextures.size()));
	std::for_each(m_pTextures.begin(), m_pTextures.end(), [&writer](Texture* t) { writer.Write(t->GetName());});

	writer.Write(ContentType::Font);
	writer.Write(static_cast<UINT>(0 /*m_pFonts.size()*/));
	//std::for_each(m_pFonts.begin(), m_pFonts.end(), [&writer](Font* f) { writer.Write(f->GetName()); });
	
	writer.Write(ContentType::Animation);
	writer.Write(static_cast<UINT>(m_pAnimations.size()));
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [&writer](Animation* a) { writer.Write(a->GetName()); });

	
	writer.Write(ContentType::End);
	
}

void tyr::ContentManager::TextureWindow()
{
	SDXL_ImGui_Text("ID\tName");
	static int selected = -1;
	for (int i{ 0 }; i < static_cast<int>(m_pTextures.size()); ++i)
	{
		std::string tag = FormatString(" %i\t%s", i, m_pTextures[i]->GetName().c_str());
		
		if (SDXL_ImGui_Selectable(tag.c_str(), selected == i,  SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			selected = i;
		}
	}
	
	if (selected != -1)
	{
		if(SDXL_ImGui_Begin("Texture##", nullptr, SDXL_ImGuiWindowFlags_AlwaysAutoResize))
		{
			auto di = m_pTextures[selected]->GetDimension();
			
			SDXL_ImGui_Image(m_pTextures[selected]->SDXL(), { di.x, di.y}, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f });
			
			
		}
		SDXL_ImGui_End();
	}
	SDXL_ImGui_Separator();
	static char newTexture[40];
	
	SDXL_ImGui_InputText("##ContentManagerTextureName", newTexture, ARRAY_SIZE(newTexture));
	SDXL_ImGui_SameLine();
	if(SDXL_ImGui_Button("LoadTexture"))
	{
		LoadTexture(std::string(newTexture));
	}

	
}
#endif
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
	
	try
	{
		auto pTemp = new Texture(m_DataFolder + m_TextureFolder, path);
		m_pTextures.emplace_back(pTemp);
		return static_cast<TextureID>(m_pTextures.size() - 1);
	}
	catch (TyrException & e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
		return 0;
	}

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

	Animation::Create(ss.str());
	m_pAnimations.emplace_back(Animation::Create(ss.str()));



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

tyr::Animation* tyr::ContentManager::GetAnimation(const std::string& fileName)
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), fileName);
	if (found != m_pAnimations.end())
	{
		return *found;
	}

	return nullptr;
}

AnimationID tyr::ContentManager::GetAnimationID(const std::string& fileName)
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), fileName);

	if (found != m_pAnimations.end())
	{
		return static_cast<AnimationID>(std::distance(m_pAnimations.begin(), found));
	}

	return 0; //
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

void tyr::ContentManager::LoadAnimation(const std::string& fileName, AnimationID arrayIndex)
{
	std::stringstream ss;
	ss << m_DataFolder << m_AnimationFolder << fileName << ANIMATION_SUFFIX;
	
	m_pAnimations.at(arrayIndex) = Animation::Create(ss.str());
}
