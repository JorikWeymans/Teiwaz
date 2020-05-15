#include "../tyrpch.h"

#ifdef EDITOR_MODE
#include "EWindow.h"

tyr::EWindow::EWindow(const char* name, GameContext* pContext)
	: m_Name(name)
	, m_pContext(pContext)
	, m_Flags(SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove | SDXL_ImGuiWindowFlags_NoBringToFrontOnFocus)
{
}

void tyr::EWindow::RenderEditor()
{
	//SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	PreRender();
	
	if(SDXL_ImGui_Begin(m_Name, nullptr, m_Flags))
	{
		InternalRenderEditor();
		SDXL_ImGui_End();
	}

	
}
#endif
