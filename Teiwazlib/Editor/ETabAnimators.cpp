#include "../tyrpch.h"
#include "ETabAnimators.h"


#ifdef EDITOR_MODE
#include "../CMAnimators.h"
#include "../ContentManager.h"
#include "../Animator.h"
#include "../GameContext.h"
#include "EUI.h"
#include "EAnimator.h"

tyr::ETabAnimators::ETabAnimators(GameContext* pContext)
	: ETabItem("Animators", pContext, 2)
{
	CreateTabItems();
}

void tyr::ETabAnimators::CreateTabItems()
{
	m_TabItems.clear();
	CMAnimators* pA = CONTENT_MANAGER->GetCMAnimators();

	std::string path = CONTENT_MANAGER->GetAbsoluteAnimatorFolder();
	std::for_each(pA->Begin(), pA->End(), [&](Animator* a)
		{
			m_TabItems.emplace_back(TabItem(path, a->GetName()));
		});

}

void tyr::ETabAnimators::PreTabRender()
{
}

void tyr::ETabAnimators::PostTabRender()
{
}

void tyr::ETabAnimators::OnItemDoubleClick(TabItem& clickedItem)
{
	E_UI->GetAnimatorEditor()->OpenAnimatorEditorWindow(
		CONTENT_MANAGER->GetAnimator(clickedItem.name));
	
}
#endif
