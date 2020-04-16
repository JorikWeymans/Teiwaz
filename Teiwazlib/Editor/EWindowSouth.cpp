#include "../tyrpch.h"

#ifdef USE_IM_GUI
#include "EWindowSouth.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../Vectors.h"

tyr::EWindowSouth::EWindowSouth(GameContext* pContext)
	: tyr::EWindow("SoutWindow", pContext)
{
	m_Flags |= SDXL_ImGuiWindowFlags_NoDecoration;
	
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




		SDXL_ImGui_EndTabBar();
	}
}
#endif