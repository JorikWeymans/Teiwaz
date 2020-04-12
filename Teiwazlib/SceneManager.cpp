#include "tyrpch.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "Vectors.h"
#include <sstream>
#include "TeiwazEngine.h"
#include "GameContext.h"
#include "Color.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include "ContentManager.h"

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
void tyr::SceneManager::RenderEditor()
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
			if(SDXL_ImGui_MenuItem("SaveScene", "s"))
			{
				SaveScene();
			}
			SDXL_ImGui_EndMenu();
		}
		SDXL_ImGui_EndMainMenuBar();
	}


	SDXL_ImGuiWindowFlags windowFlags = SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove;
	//LEFT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ 0.f,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ ENGINE_SPACING_LEFT,m_pContext->pGameSpace->height  + ENGINE_SPACING_BOT });

	SDXL_ImGui_Begin(m_pScenes[0]->GetName().c_str(), nullptr, windowFlags);



	SDXL_ImGui_End();


	//RIGHT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ ENGINE_SPACING_LEFT + m_pContext->pGameSpace->width,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ ENGINE_SPACING_RIGHT,m_pContext->pGameSpace->height + ENGINE_SPACING_BOT });
	SDXL_ImGui_Begin("Inspector", nullptr, windowFlags);



	SDXL_ImGui_End();


	//Bottom
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::float2{ m_pContext->pGameSpace->pos.x,m_pContext->pGameSpace->height });
	SDXL_ImGui_SetNextWindowSize(SDXL::float2{ m_pContext->pGameSpace->width, ENGINE_SPACING_BOT + ENGINE_SPACING_TOP });

	SDXL_ImGui_Begin("Bottom" ,nullptr, windowFlags | SDXL_ImGuiWindowFlags_NoDecoration);
	if(SDXL_ImGui_BeginTabBar("Console##Bottom"))
	{
		//if (SDXL_ImGui_BeginTabItem("Other"))
		//{
		//	if(SDXL_ImGui_Button("Save Scene"))
		//	{
		//		SaveScene();
		//	}
		//	SDXL_ImGui_EndTabItem();
		//}

		if (SDXL_ImGui_ConsoleBegin("Console", SDXL_ImGuiTabBarFlags_None))
		{
			SDXL_ImGui_ConsoleDraw();
			SDXL_ImGui_ConsoleEnd();
		}
		SDXL_ImGui_EndTabBar();
	}

	

	SDXL_ImGui_End();


	//SDXL_ImGUI_ConsoleLog("[error] this is a real error");
	//SDXL_ImGUI_ConsoleClear();
	m_pScenes[0]->Debug();
}

void tyr::SceneManager::SaveScene()
{
	std::stringstream ss;
	ss << ContentManager::GetInstance()->GetDataFolder();
	ss << "Scenes/";
	ss << "Test";
	ss << ".tyrScene";
	BinaryWriter writer(ss.str());
	// Header
	// Long double (binary rep of JorikWey
	ULONG64 header = 0x4A6F72696B576579;
	writer.Write(header);
	
	m_pScenes[0]->Save(writer);





	
	writer.Close();


	BinaryReader reader(ss.str());
	ULONG64 k = reader.Read<ULONG64>();
	if(k == header)
	{
		SDXL_ImGui_ConsoleLog("This is a tyrScene");
	}

	

}


#endif

#ifdef USE_IM_GUI
void tyr::SceneManager::Render()
#else
void tyr::SceneManager::Render() const
#endif

{
	SDXL_Clear(static_cast<SDXL::SDXLVec4>(ColorBlack));

	m_pScenes[0]->Render();
	SDXL_RenderAll();
	
#ifdef USE_IM_GUI
	RenderEditor();
#endif

	
	SDXL_Present();

	
}
