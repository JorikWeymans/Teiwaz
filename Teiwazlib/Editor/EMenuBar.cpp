#include "../tyrpch.h"

#ifdef USE_IM_GUI
#include "../ContentManager.h"
#include "../Texture.h"
#include "EMenuBar.h"
#include "../TeiwazEngine.h"
#include "../GameContext.h"
#include "../SceneManager.h"
#include "../ContentManager.h"
#include "EAnimation.h"
#include <sstream>
tyr::EMenuBar::EMenuBar(GameContext* pContext)
	: m_pContext(pContext)
	, m_pTexture(nullptr)
{
	m_pContext->paused = true;
}

tyr::EMenuBar::~EMenuBar()
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

		CONTENT_MANAGER->RenderEditor();
	

		
		if(m_pContext->paused)
		{
			if (SDXL_ImGui_Selectable("PLAY", false, 0, SDXL::Float2(40, 20)))
			{
				m_pContext->paused = !m_pContext->paused;
			}
		}
		else
		{
			if (SDXL_ImGui_Selectable("PAUSE", false, 0, SDXL::Float2(40, 20)))
			{
				m_pContext->paused = !m_pContext->paused;
			}
		}

		
		


		//if(SDXL_ImGui_IsItemClicked())
		
		
		SDXL_ImGui_EndMainMenuBar();
	}
}
#endif