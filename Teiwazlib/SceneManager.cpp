#include "tyrpch.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Vectors.h"
#include <sstream>
#include "TeiwazEngine.h"
#include "GameContext.h"
#include "Color.h"
tyr::SceneManager::SceneManager(GameContext* pContext)
	: m_pContext(pContext)
	, m_pScenes(std::vector<Scene*>())
{
}

tyr::SceneManager::~SceneManager()
{
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [](Scene* s) {SAFE_DELETE(s)});
}

void tyr::SceneManager::AddScene(Scene* pScene)
{
	pScene->m_pContext = m_pContext;
	pScene->Initialize();

	m_pScenes.emplace_back(pScene);
	
}

void tyr::SceneManager::Update()
{
	m_pScenes[0]->Update();
}

void tyr::SceneManager::FixedUpdate()
{
	m_pScenes[0]->FixedUpdate();
}
#ifdef USE_IM_GUI
void tyr::SceneManager::Debug() const
{
	DebugGameOutline();
	if(SDXL_ImGui_BeginMainMenuBar())
	{
		if(SDXL_ImGui_BeginMenu("File"))
		{
			if (SDXL_ImGui_MenuItem("Quit", "esc"))
			{
				TeiwazEngine::WantQuit = true;
				
			}
			SDXL_ImGui_EndMenu();
		}
		SDXL_ImGui_EndMainMenuBar();
	}
	

	
	m_pScenes[0]->Debug();
}

void tyr::SceneManager::DebugGameOutline() const
{

	const auto width = m_pContext->pGameSpace->GetWidth();
	const auto height = m_pContext->pGameSpace->GetHeight();

	//LEFT LINE
	SDXL_RenderDebugLine(SDXL::SDXLVec2{ ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP },
		SDXL::SDXLVec2{ ENGINE_SPACING_LEFT, height + ENGINE_SPACING_TOP }, static_cast<SDXL::SDXLVec4>(ColorBlue));

	//RIGHT LINE
	SDXL_RenderDebugLine(SDXL::SDXLVec2{ width + ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP },
		SDXL::SDXLVec2{ width + ENGINE_SPACING_LEFT, height + ENGINE_SPACING_TOP }, static_cast<SDXL::SDXLVec4>(ColorBlue));


	//TOP LINE
	SDXL_RenderDebugLine(SDXL::SDXLVec2{ ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP },
		SDXL::SDXLVec2{ width + ENGINE_SPACING_LEFT, ENGINE_SPACING_TOP }, static_cast<SDXL::SDXLVec4>(ColorBlue));


}
#endif
void tyr::SceneManager::Render() const
{
	SDXL_Clear();

	m_pScenes[0]->Render();
	
	SDXL_RenderAll();
#ifdef USE_IM_GUI
	Debug();
#endif

	
	SDXL_Present();

	
}
