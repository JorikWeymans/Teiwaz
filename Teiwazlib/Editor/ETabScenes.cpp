#include "../tyrpch.h"
#include "../CMScenes.h"
#include "../Scene.h"
#ifdef EDITOR_MODE
#include <filesystem>
#include "../StringManipulation.h"
#include "../ContentManager.h"
#include "../SceneManager.h"
#include "../GameContext.h"


#include "ETabScenes.h"
tyr::ETabScenes::ETabScenes(GameContext* pContext)
	: tyr::ETabItem("Scenes", pContext, 0)
{
	CreateTabItems();
}

void tyr::ETabScenes::PreTabRender()
{	
}

void tyr::ETabScenes::PostTabRender()
{
}

void tyr::ETabScenes::OnItemDoubleClick(TabItem& clickedItem)
{
	if (!m_pContext->pSceneManager->DoesSceneExist(clickedItem.name))
	{
		m_pContext->pSceneManager->AddScene(new Scene(clickedItem.name, clickedItem.path));
		m_pContext->pSceneManager->SetCurrentScene(clickedItem.name);
		SDXL_ImGui_ConsoleLog(FormatString("Scene %s is loaded", clickedItem.name.c_str()).c_str());
	}
	
}

void tyr::ETabScenes::CreateTabItems()
{
	
	m_TabItems.clear();
	CMScenes* t = CONTENT_MANAGER->GetCMScenes();
	std::string path = CONTENT_MANAGER->GetAbsoluteSceneFolder();
	std::for_each(t->Begin(), t->End(), [&](Scene* s)
		{
			m_TabItems.emplace_back(TabItem(path, s->GetName()));
		});
}

#endif
