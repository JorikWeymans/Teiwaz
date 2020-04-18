#include "../tyrpch.h"
#include <direct.h>

#ifdef USE_IM_GUI
#include <filesystem>
#include "../StringManipulation.h"
#include "../ContentManager.h"
#include "../Color.h"
#include "../Texture.h"
#include "../SceneManager.h"
#include "../GameContext.h"

#include "ETabScenes.h"

tyr::ETabScenes::ETabScenes(GameContext* pContext)
	: tyr::ETabItem("Scenes", pContext)
	, m_SceneFolder(ContentManager::GetInstance()->GetDataFolder() + "Scenes/")
{
	
#pragma warning (suppress : 6031)
	_mkdir(m_SceneFolder.c_str()); //making dir if dir does not exist
	for (auto& entry : std::filesystem::directory_iterator(m_SceneFolder))
	{

		std::string filename{ GetFileFromPath(entry.path().string()) };

		if (DoesExtensionMatch(filename, "tyrScene"))
		{
			RemoveExtension(filename);
			m_Files.emplace_back(TabItem(entry.path().string(), filename));
		}
	}
	m_Texture = CONTENT_MANAGER->LoadTexture("Editor/TyrIcon.png");
}

void tyr::ETabScenes::PreRender()
{
}

void tyr::ETabScenes::InternalRenderEditor()
{
	for (auto& s : m_Files)
	{

		SDXL_ImGui_BeginGroup();
		SDXL_ImGui_Image(CONTENT_MANAGER->GetTexture(m_Texture)->SDXL(), { 50.f, 50.f }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f },
			static_cast<SDXL::Float4>(s.isHovered ? ColorGray : ColorWhite));
		SDXL_ImGui_PushTextWrapPos(SDXL_ImGui_GetCursorPos().x + 50.f);
		SDXL_ImGui_TextWrapped(s.name.c_str());
		SDXL_ImGui_PopTextWrapPos();
		SDXL_ImGui_EndGroup();

		s.isHovered = SDXL_ImGui_IsItemHovered();
		if (SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left) && s.isHovered)
		{
			SDXL_ImGui_ConsoleLog("count or something");
			m_pContext->pSceneManager->Flush();
		}

		SDXL_ImGui_SameLine();
	}
}

#endif
