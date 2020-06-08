#include "../tyrpch.h"
#include "ETabAnimators.h"

#ifdef EDITOR_MODE
#include "../CMAnimators.h"
#include "../ContentManager.h"
#include "../Animator.h"
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
	UNREFERENCED_PARAMETER(clickedItem);
}
#endif
