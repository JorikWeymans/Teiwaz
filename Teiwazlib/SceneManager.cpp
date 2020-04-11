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
	SDXL_RenderDebugRect(SDXL::SDXLVec2{ ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP }, m_pContext->pGameSpace->width, m_pContext->pGameSpace->height, static_cast<SDXL::SDXLVec4>(ColorBlue));


	//Main Menu
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

	//LEFT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ 0.f,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ ENGINE_SPACING_LEFT,m_pContext->pGameSpace->height  + ENGINE_SPACING_BOT });
	SDXL_ImGui_Begin("Scene viewer", nullptr,SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove);



	SDXL_ImGui_End();


	//RIGHT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ ENGINE_SPACING_LEFT + m_pContext->pGameSpace->width,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ ENGINE_SPACING_RIGHT,m_pContext->pGameSpace->height + ENGINE_SPACING_BOT });
	SDXL_ImGui_Begin("Inspector", nullptr, SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove);



	SDXL_ImGui_End();


	//Console
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ m_pContext->pGameSpace->pos.x,m_pContext->pGameSpace->height });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ m_pContext->pGameSpace->width, ENGINE_SPACING_BOT + ENGINE_SPACING_TOP });
	
		
	SDXL_ImGui_ConsoleDraw("Console", SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove);



	//SDXL_ImGUI_ConsoleLog("[error] this is a real error");
	//SDXL_ImGUI_ConsoleClear();
	m_pScenes[0]->Debug();
}


#endif
void tyr::SceneManager::Render() const
{
	SDXL_Clear(static_cast<SDXL::SDXLVec4>(ColorBlack));

	m_pScenes[0]->Render();
	SDXL_RenderAll();
	
#ifdef USE_IM_GUI
	Debug();
#endif

	
	SDXL_Present();

	
}
