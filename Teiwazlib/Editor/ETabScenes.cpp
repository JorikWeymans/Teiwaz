#include "../tyrpch.h"
#include <direct.h>

#ifdef EDITOR_MODE
#include <filesystem>
#include "../StringManipulation.h"
#include "../ContentManager.h"
#include "../Color.h"
#include "../Texture.h"
#include "../SceneManager.h"
#include "../GameContext.h"
#include "../Scene.h"
#include "ETabScenes.h"
#include "../CMScenes.h"
tyr::ETabScenes::ETabScenes(GameContext* pContext)
	: tyr::ETabItem("Scenes", pContext)
	, m_Texture(0)
{
	CreateTabItems();
	
}

void tyr::ETabScenes::PreRender()
{
	
}

void tyr::ETabScenes::InternalRenderEditor()
{
	SDXL::SDXLImage* theImage = CONTENT_MANAGER->GetTexture(m_Texture)->SDXL();
	for (auto& s : m_TabItems)
	{

		SDXL_ImGui_BeginGroup();
		SDXL_ImGui_Image(theImage, { 50.f, 50.f }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f },
			static_cast<SDXL::Float4>(s.isHovered ? ColorGray : ColorWhite));
		SDXL_ImGui_PushTextWrapPos(SDXL_ImGui_GetCursorPos().x + 50.f);
		SDXL_ImGui_TextWrapped(s.name.c_str());
		SDXL_ImGui_PopTextWrapPos();
		SDXL_ImGui_EndGroup();

		s.isHovered = SDXL_ImGui_IsItemHovered();
		if (SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left) && s.isHovered)
		{
			if(!m_pContext->pSceneManager->DoesSceneExist(s.name))
				m_pContext->pSceneManager->AddScene(new Scene(s.name, s.path));

			m_pContext->pSceneManager->SetCurrentScene(s.name);
			
			SDXL_ImGui_ConsoleLog(FormatString("Scene %s is loaded", s.name.c_str()).c_str());
			
		}

		SDXL_ImGui_SameLine();
	}
}

void tyr::ETabScenes::CreateTabItems()
{
	
	m_TabItems.clear();
	CMScenes* t = ContentManager::GetInstance()->GetScenes();
	std::string path = ContentManager::GetInstance()->GetAbsoluteSceneFolder();
	std::for_each(t->Begin(), t->End(), [&](Scene* s)
		{
			m_TabItems.emplace_back(TabItem(path, s->GetName()));
		});
}

#endif
