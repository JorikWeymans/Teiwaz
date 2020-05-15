#include "../tyrpch.h"

#ifdef EDITOR_MODE
#include "EWindowSceneView.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../Vectors.h"
#include "../SceneManager.h"
tyr::EWindowSceneView::EWindowSceneView(GameContext* pContext)
	: tyr::EWindow("Inspector", pContext)
	, m_Pos(0.f, ENGINE_SPACING_TOP)
	, m_Size(ENGINE_SPACING_LEFT, m_pContext->pGameSpace->height + ENGINE_SPACING_BOT)
{
}

void tyr::EWindowSceneView::PreRender()
{
	SDXL_ImGui_SetNextWindowPos(m_Pos);
	SDXL_ImGui_SetNextWindowSize(m_Size);
	m_Name = m_pContext->pSceneManager->GetCurrentSceneName().c_str();
}

void tyr::EWindowSceneView::InternalRenderEditor()
{

	//SDXL_ImGui_AddRect2(m_Pos, SDXL::Float2{ m_Pos.x + m_Size.x, m_Pos.y + 20.f });
	if (SDXL_ImGui_IsMouseHoveringRectSize(m_Pos, SDXL::Float2{ m_Size.x,20.f }, false))
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
	
}
#endif
