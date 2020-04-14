#include "tyrpch.h"
#include "ESceneHolder.h"
#include "direct.h"
#include <filesystem>
#include "StringManipulation.h"
#include "ContentManager.h"
#include "Texture.h"
#include "Color.h"

tyr::ESceneHolder::ESceneHolder(const std::string& dataFolder)
	: m_SceneFolder(dataFolder + "Scenes/")
{

	for(auto& entry : std::filesystem::directory_iterator(m_SceneFolder))
	{
		
		std::string filename{ GetFileFromPath(entry.path().string()) };
		
		if(DoesExtensionMatch(filename, "tyrScene"))
		{
			RemoveExtension(filename);
			m_Files.emplace_back(SceneItem(entry.path().string(), filename));
		}
		
	}
	m_pTexture = CONTENT_MANAGER->LoadTexture(L"Editor/TyrIcon.png");
	//Vector2
}

void tyr::ESceneHolder::RenderEditor()
{
#ifdef USE_IM_GUI
	for( auto& s : m_Files)
	{

		SDXL_ImGui_BeginGroup();
		SDXL_ImGui_Image(m_pTexture->SDXL(), { 50.f, 50.f }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f },
			static_cast<SDXL::Float4>(s.isHovered ? ColorGray : ColorWhite));

		SDXL_ImGui_Text(s.name.c_str());
		SDXL_ImGui_EndGroup();

		s.isHovered = SDXL_ImGui_IsItemHovered();
		if (SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left) && s.isHovered)
		{
			SDXL_ImGui_ConsoleLog("count or something");
		}

		SDXL_ImGui_SameLine();
	}

#endif
}
