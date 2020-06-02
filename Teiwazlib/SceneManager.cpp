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
#include "./Editor/EUI.h"
#include "CMScenes.h"
tyr::SceneManager::SceneManager()
	: m_pContext(nullptr)
	, m_pCurrentScene(nullptr)
	, m_WantFlush(false)
#ifdef EDITOR_MODE
	, m_pEditorUI(nullptr)
#endif
{
	
}

tyr::SceneManager::~SceneManager()
{
#ifdef EDITOR_MODE
	SAFE_DELETE(m_pEditorUI);
#endif
}

void tyr::SceneManager::Initialize(GameContext* pContext)
{
	m_pContext = pContext;
#ifdef EDITOR_MODE
	m_pEditorUI = new EUI(pContext);
#endif
}

void tyr::SceneManager::AddScene(Scene* pScene)
{
	UNREFERENCED_PARAMETER(pScene);
}

void tyr::SceneManager::SetCurrentScene(const std::string& SceneName)
{
	m_pCurrentScene = ContentManager::GetInstance()->GetScenes()->GetScene(SceneName);
	m_pCurrentScene->m_pContext = m_pContext;
	m_pCurrentScene->Initialize();

}

void tyr::SceneManager::SetCurrentScene(SceneID id)
{
	m_pCurrentScene = ContentManager::GetInstance()->GetScenes()->GetScene(id);
	m_pCurrentScene->m_pContext = m_pContext;
	m_pCurrentScene->Initialize();

}

void tyr::SceneManager::Update()
{
	if(!m_pContext->paused)
		m_pCurrentScene->Update();
}

void tyr::SceneManager::FixedUpdate()
{
	if (!m_pContext->paused)
		m_pCurrentScene->FixedUpdate();
}

void tyr::SceneManager::FlushCurrentScene()
{
	m_pCurrentScene->Flush();
	
}
#ifdef EDITOR_MODE
void tyr::SceneManager::RenderEditor()
{
	SDXL_RenderDebugRect(SDXL::SDXLVec2{ ENGINE_SPACING_LEFT,ENGINE_SPACING_TOP }, m_pContext->pGameSpace->width, m_pContext->pGameSpace->height, static_cast<SDXL::SDXLVec4>(ColorBlue));

	const SDXL_ImGuiWindowFlags windowFlags = SDXL_ImGuiWindowFlags_NoResize | SDXL_ImGuiWindowFlags_NoCollapse | SDXL_ImGuiWindowFlags_NoMove;

	

	m_pEditorUI->RenderEditor();
	m_pCurrentScene->RenderEditor();



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
		// Long double (JorikWeymansTyrScene hashed via Adler32 to this value)
		ULONG64 header = 0x545e0811;
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

bool tyr::SceneManager::DoesSceneExist(std::string& sceneName)
{
	UNREFERENCED_PARAMETER(sceneName);
	//for(auto s : m_pScenes)
	//{
	//	if (s->GetName() == sceneName)
	//		return true;
	//}

	return false;
	
}


#endif

#ifdef EDITOR_MODE
void tyr::SceneManager::Render()
#else
void tyr::SceneManager::Render() const
#endif

{
	SDXL_Clear(static_cast<SDXL::SDXLVec4>(ColorBlack));

	m_pCurrentScene->Render();
	SDXL_RenderAll();
	
#ifdef EDITOR_MODE
	RenderEditor();
#endif

	
	SDXL_Present();

	
}
