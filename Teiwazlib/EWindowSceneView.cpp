#include "tyrpch.h"

#ifdef USE_IM_GUI
#include "EWindowSceneView.h"
#include "TeiwazEngine.h"
#include "GameContext.h"
#include "Vectors.h"
#include "SceneManager.h"
tyr::EWindowSceneView::EWindowSceneView(GameContext* pContext)
	: tyr::EWindow("Inspector", pContext)
{
}

void tyr::EWindowSceneView::PreRender()
{
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ 0.f,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ ENGINE_SPACING_LEFT,m_pContext->pGameSpace->height + ENGINE_SPACING_BOT });
	m_Name = m_pContext->pSceneManager->GetCurrentSceneName().c_str();
}

void tyr::EWindowSceneView::InternalRenderEditor()
{
	if (SDXL_ImGui_BeginPopupContextWindow("SceneOptions"))
	{
		static char sceneName[25];

		SDXL_ImGui_InputText("##SceneName", sceneName, 25, nullptr);
		SDXL_ImGui_SameLine();
		if (SDXL_ImGui_Button("Save SceneName"))
		{
			m_pContext->pSceneManager->SetCurrentSceneName(std::string(sceneName));

		}

		SDXL_ImGui_EndPopup();
	}
}
#endif
