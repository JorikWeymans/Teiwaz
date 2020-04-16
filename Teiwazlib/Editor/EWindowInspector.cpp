#include "../tyrpch.h"

#ifdef USE_IM_GUI
#include "EWindowInspector.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../Vectors.h"
#include "../SceneManager.h"
tyr::EWindowInspector::EWindowInspector(GameContext* pContext)
	: tyr::EWindow("Inspector", pContext)
{
}

void tyr::EWindowInspector::PreRender()
{
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ ENGINE_SPACING_LEFT + m_pContext->pGameSpace->width,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ ENGINE_SPACING_RIGHT,m_pContext->pGameSpace->height + ENGINE_SPACING_BOT });
}

void tyr::EWindowInspector::InternalRenderEditor()
{
	//Nothing needs to be done here for now (Sceneobjects render in this part)
}
#endif
