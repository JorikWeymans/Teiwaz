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
#include "EUI.h"

tyr::SceneManager::SceneManager()
	: m_pContext(nullptr)
	, m_pScenes(std::vector<Scene*>())
	, m_pCurrentScene(nullptr)
	, m_WantFlush(false)
#ifdef USE_IM_GUI
	, m_pEditorUI(nullptr)
#endif
{
	
}

tyr::SceneManager::~SceneManager()
{
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [](Scene* s) {SAFE_DELETE(s)});
#ifdef USE_IM_GUI
	SAFE_DELETE(m_pEditorUI);
#endif
}

void tyr::SceneManager::Initialize(GameContext* pContext)
{
	m_pContext = pContext;
#ifdef USE_IM_GUI
	m_pEditorUI = new EUI(pContext);
#endif
}

void tyr::SceneManager::AddScene(Scene* pScene)
{
	pScene->m_pContext = m_pContext;
	pScene->Initialize();

	m_pScenes.emplace_back(pScene);
	if (!m_pCurrentScene) SetCurrentScene(pScene->GetName());
}

void tyr::SceneManager::SetCurrentScene(const std::string& SceneName)
{
	auto found = std::find_if(m_pScenes.begin(), m_pScenes.end(), [&SceneName](Scene* s) { return s->GetName() == SceneName; });
	if(found != m_pScenes.end())
	{
		m_pCurrentScene = *found;
	}
}

void tyr::SceneManager::Update()
{
	
	m_pCurrentScene->Update();
}

void tyr::SceneManager::FixedUpdate()
{
	m_pCurrentScene->FixedUpdate();
}

void tyr::SceneManager::FlushCurrentScene()
{
	m_pCurrentScene->Flush();
	
}
#ifdef USE_IM_GUI
void tyr::SceneManager::RenderEditor()
{
	SDXL_RenderDebugRect(SDXL::SDXLVec2{ ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP }, m_pContext->pGameSpace->width, m_pContext->pGameSpace->height, static_cast<SDXL::SDXLVec4>(ColorBlue));

	const SDXL_ImGuiWindowFlags windowFlags = SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove;

	m_pEditorUI->RenderEditor();

	
	m_pCurrentScene->Debug();

	if(m_WantFlush)
	{
		FlushCurrentScene();
	}
}


void tyr::SceneManager::SaveCurrentScene()
{

	std::stringstream ss;
	ss << ContentManager::GetInstance()->GetDataFolder();
	ss << "Scenes/" << m_pCurrentScene->GetName() << ".tyrScene";
	
	{
		BinaryWriter writer(ss.str());
		// Header
		// Long double (binary rep of JorikWey
		ULONG64 header = 0x4A6F72696B576579;
		writer.Write(header);
	
		m_pCurrentScene->Save(writer);
		writer.Write(ObjectType::End);
	
	
		writer.Close();

		//m_pCurrentScene->Flush();
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

void tyr::SceneManager::SetCurrentSceneName(const std::string& name)
{
	m_pCurrentScene->m_Name = name;
}

const std::string& tyr::SceneManager::GetCurrentSceneName() const
{
	return m_pCurrentScene->GetName();
}


#endif

#ifdef USE_IM_GUI
void tyr::SceneManager::Render()
#else
void tyr::SceneManager::Render() const
#endif

{
	SDXL_Clear(static_cast<SDXL::SDXLVec4>(ColorBlack));

	m_pCurrentScene->Render();
	SDXL_RenderAll();
	
#ifdef USE_IM_GUI
	RenderEditor();
#endif

	
	SDXL_Present();

	
}
