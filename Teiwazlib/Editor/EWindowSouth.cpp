#include "../tyrpch.h"
#include <algorithm>

#ifdef EDITOR_MODE
#include "EWindowSouth.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../Vectors.h"
#include "ETabItem.h"
#include "ETabScenes.h"
#include "ETabAnimations.h"
tyr::EWindowSouth::EWindowSouth(GameContext* pContext)
	: tyr::EWindow("SouthWindow", pContext)
{
	m_Flags |= SDXL_ImGuiWindowFlags_NoDecoration;
	m_pTabItems.emplace_back(new ETabScenes(pContext));
	m_pTabItems.emplace_back(new ETabAnimations(pContext));
}

tyr::EWindowSouth::~EWindowSouth()
{
	std::for_each(m_pTabItems.begin(), m_pTabItems.end(), [](ETabItem* t) { SAFE_DELETE(t); });
}


void tyr::EWindowSouth::PreRender()
{
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ m_pContext->pGameSpace->pos.x,m_pContext->pGameSpace->height });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ m_pContext->pGameSpace->width, ENGINE_SPACING_BOT + ENGINE_SPACING_TOP });

}

void tyr::EWindowSouth::InternalRenderEditor()
{
	if (SDXL_ImGui_BeginTabBar("SouthTabBar"))
	{
		if (SDXL_ImGui_ConsoleBegin("Console", SDXL_ImGuiTabBarFlags_None))
		{
			SDXL_ImGui_ConsoleDraw();
			SDXL_ImGui_ConsoleEnd();
		}

		std::for_each(m_pTabItems.begin(), m_pTabItems.end(), [](ETabItem* t) { t->RenderEditor(); });



		SDXL_ImGui_EndTabBar();
	}
}
#endif