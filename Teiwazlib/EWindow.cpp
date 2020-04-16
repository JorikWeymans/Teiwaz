#include "tyrpch.h"

#ifdef USE_IM_GUI
#include "EWindow.h"

tyr::EWindow::EWindow(const char* name, GameContext* pContext)
	: m_Name(name)
	, m_pContext(pContext)
	, m_Flags(SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove)
{
}

void tyr::EWindow::RenderEditor()
{
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	PreRender();
	
	SDXL_ImGui_Begin(m_Name, nullptr, m_Flags);
	InternalRenderEditor();
	SDXL_ImGui_End();
}
#endif
