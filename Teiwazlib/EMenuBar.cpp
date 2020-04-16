#include "tyrpch.h"

#ifdef USE_IM_GUI
#include "EMenuBar.h"
#include "TeiwazEngine.h"
#include "GameContext.h"
#include "SceneManager.h"
tyr::EMenuBar::EMenuBar(GameContext* pContext)
	: m_pContext(pContext)
{

}

void tyr::EMenuBar::RenderEditor()
{
	if (SDXL_ImGui_BeginMainMenuBar())
	{
		if (SDXL_ImGui_BeginMenu("File"))
		{
			if (SDXL_ImGui_MenuItem("Quit", "esc"))
			{
				TeiwazEngine::WantQuit = true;

			}
			if (SDXL_ImGui_MenuItem("SaveScene", "s"))
			{
				m_pContext->pSceneManager->SaveCurrentScene();
			}
			SDXL_ImGui_EndMenu();
		}
		SDXL_ImGui_EndMainMenuBar();
	}
}
#endif