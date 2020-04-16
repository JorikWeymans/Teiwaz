#include "../tyrpch.h"

#ifdef USE_IM_GUI
#include "ETabItem.h"

tyr::ETabItem::ETabItem(const char* name, GameContext* pContext)
	: m_Name(name)
	, m_pContext(pContext)
{
}

void tyr::ETabItem::RenderEditor()
{
	PreRender();

	if(	SDXL_ImGui_BeginTabItem(m_Name))
	{
		InternalRenderEditor();

		SDXL_ImGui_EndTabItem();
	}
	
	
}
#endif
