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
#include "Transform.h"
#include "BinStructureHelpers.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include "Factory.h"
#include "ESceneHolder.h"
tyr::SceneManager::SceneManager(GameContext* pContext)
	: m_pContext(pContext)
	, m_pScenes(std::vector<Scene*>())
	, m_WantFlush(false)
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

void tyr::SceneManager::FlushCurrentScene()
{
	m_pScenes[0]->Flush();
	
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
				SaveCurrentScene();
			}
			SDXL_ImGui_EndMenu();
		}
		SDXL_ImGui_EndMainMenuBar();
	}


	SDXL_ImGuiWindowFlags windowFlags = SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove;
	//LEFT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ 0.f,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ ENGINE_SPACING_LEFT,m_pContext->pGameSpace->height  + ENGINE_SPACING_BOT });

	SDXL_ImGui_Begin(m_pScenes[0]->GetName().c_str(), nullptr, windowFlags);



	SDXL_ImGui_End();


	//RIGHT
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ ENGINE_SPACING_LEFT + m_pContext->pGameSpace->width,ENGINE_SPACING_TOP });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ ENGINE_SPACING_RIGHT,m_pContext->pGameSpace->height + ENGINE_SPACING_BOT });
	SDXL_ImGui_Begin("Inspector", nullptr, windowFlags);



	SDXL_ImGui_End();


	//Bottom
	SDXL_ImGui_SetNextWindowBgAlpha(1.f);
	SDXL_ImGui_SetNextWindowPos(SDXL::Float2{ m_pContext->pGameSpace->pos.x,m_pContext->pGameSpace->height });
	SDXL_ImGui_SetNextWindowSize(SDXL::Float2{ m_pContext->pGameSpace->width, ENGINE_SPACING_BOT + ENGINE_SPACING_TOP });

	SDXL_ImGui_Begin("Bottom" ,nullptr, windowFlags | SDXL_ImGuiWindowFlags_NoDecoration);
	if(SDXL_ImGui_BeginTabBar("Console##Bottom"))
	{


		if (SDXL_ImGui_ConsoleBegin("Console", SDXL_ImGuiTabBarFlags_None))
		{
			SDXL_ImGui_ConsoleDraw();
			SDXL_ImGui_ConsoleEnd();
		}
		
		static ESceneHolder holder(ContentManager::GetInstance()->GetDataFolder(), this);
		
		if (SDXL_ImGui_BeginTabItem("SceneHolder"))
{
			holder.RenderEditor();
			SDXL_ImGui_EndTabItem();
		}

		SDXL_ImGui_EndTabBar();
	}


	SDXL_ImGui_End();


	//SDXL_ImGUI_ConsoleLog("[error] this is a real error");
	//SDXL_ImGUI_ConsoleClear();
	m_pScenes[0]->Debug();

	if(m_WantFlush)
	{
		FlushCurrentScene();
	}
}

void tyr::SceneManager::SaveCurrentScene()
{

	std::stringstream ss;
	ss << ContentManager::GetInstance()->GetDataFolder();
	ss << "Scenes/" << "Test" << ".tyrScene";
	
	{
		BinaryWriter writer(ss.str());
		// Header
		// Long double (binary rep of JorikWey
		ULONG64 header = 0x4A6F72696B576579;
		writer.Write(header);
	
		m_pScenes[0]->Save(writer);
		writer.Write(ObjectType::End);
	
	
		writer.Close();

		//m_pScenes[0]->Flush();
	}

	SDXL_ImGui_ConsoleLog("Scene is saved");




	//{
	//	BinaryReader reader(ss.str());
	//	// rn
	//	// header
	//	ULONG64 header = reader.Read<ULONG64>();
	//	if (header != 0x4A6F72696B576579)
	//	{
	//		SDXL_ImGui_ConsoleLogError("This is no a scene");
	//	}
	//		// sceneName
	//	std::string sceneName = reader.ReadString();
	//	UNREFERENCED_PARAMETER(sceneName);

	//	
	//	try
	//	{
	//		while (reader.Read<ObjectType>() == ObjectType::SceneObject)
	//		{
	//			auto parent = LoadSceneObject(reader, nullptr);

	//			const size_t childs = reader.Read<size_t>();
	//			for(size_t i{0}; i < childs; ++i  )
	//			{
	//				reader.Read<ObjectType>(); //no need to check, this is always an SeneObject.
	//				LoadSceneObject(reader, parent);
	//				reader.Read<size_t>(); //no need to save, only 1 depth child relation allowed
	//			}
	//		}
	//	}
	//	catch(TyrException& e)
	//	{
	//		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
	//	}
	//
	//		
	//}



	



	
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
