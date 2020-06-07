#include "../tyrpch.h"
#include "ETabAnimators.h"
#ifdef EDITOR_MODE


tyr::ETabAnimators::ETabAnimators(GameContext* pContext)
	: ETabItem("Animators", pContext, 2)
{
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
