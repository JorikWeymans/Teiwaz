#include "../tyrpch.h"

#ifdef USE_IM_GUI
#include "../ContentManager.h"
#include "../Texture.h"
#include "EMenuBar.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../SceneManager.h"
#include "EAnimation.h"
#include <sstream>
tyr::EMenuBar::EMenuBar(GameContext* pContext)
	: m_pContext(pContext)
	, m_pTexture(nullptr)
{
	m_pEditorAni = new EAnimation(pContext);
}

tyr::EMenuBar::~EMenuBar()
{
	SAFE_DELETE(m_pEditorAni);
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

		if(SDXL_ImGui_BeginMenu("Animation##MainMenu"))
		{
			
			if(SDXL_ImGui_Button("Open Ani Editor"))
			{
				SDXL_ImGui_OpenPopup("AniEditor");
			}

			m_pEditorAni->RenderEditor();

			SDXL_ImGui_EndMenu();
		}
		SDXL_ImGui_EndMainMenuBar();
	}
}
#endif