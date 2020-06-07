#include "../tyrpch.h"
#include "ETabAnimations.h"

#ifdef EDITOR_MODE
#include "../StringManipulation.h"
#include "../ContentManager.h"

#include "../CMAnimations.h"
#include "../Animation.h"
#include "../GameContext.h"
#include "EAnimation.h"



tyr::ETabAnimations::ETabAnimations(GameContext* pContext)
	: tyr::ETabItem("Animations", pContext, 1)
	, m_SceneFolder(ContentManager::GetInstance()->GetDataFolder() + "Animations/")
{
	
	m_pEditorAni = new EAnimation(pContext);
	CreateTabItems();
}

tyr::ETabAnimations::~ETabAnimations()
{
	SAFE_DELETE(m_pEditorAni);
}

void tyr::ETabAnimations::CreateTabItems()
{
	m_TabItems.clear();
	CMAnimations* a = CONTENT_MANAGER->GetCMAnimations();

	std::string path = CONTENT_MANAGER->GetAbsoluteAnimationFolder();
	std::for_each(a->Begin(), a->End(), [&](Animation* a)
		{
			m_TabItems.emplace_back(TabItem(path, a->GetName()));
		});
	
	
}

void tyr::ETabAnimations::PreTabRender()
{}

void tyr::ETabAnimations::PostTabRender()
{	
	m_pEditorAni->RenderEditor();
}

void tyr::ETabAnimations::OnItemDoubleClick(TabItem& clickedItem)
{
	m_pEditorAni->SetCurrentAnimation(CONTENT_MANAGER->GetAnimation(clickedItem.name));

	SDXL_ImGui_OpenPopup("AniEditor");
}

#endif
