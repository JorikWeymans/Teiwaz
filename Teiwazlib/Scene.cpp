#include "tyrpch.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>
#include <sstream>
#include "BinaryWriter.h"
#include "ContentManager.h"
#include "BinaryReader.h"
#include "Factory.h"
#include "TyrComps.h"

tyr::Scene::Scene(const std::string& name)
	: Scene(name, "")
{
	
}

tyr::Scene::Scene(const std::string& name, const std::string& path)
	: m_pContext(nullptr)
	, m_Name(name) , m_Path(path)
	, m_IsLoaded(false)
{
}

tyr::Scene::~Scene()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) { s->m_IsDestroyed =true;  SAFE_DELETE(s)});
}

void tyr::Scene::Load()
{
	if (m_Path.empty()) return;
	if (m_IsLoaded) return;
	
	try
	{
		const std::string fullFile = m_Path + m_Name + ".tyrScene";
		BinaryReader reader(fullFile);
		// rn
		// header
		ULONG64 header = reader.Read<ULONG64>();
		if (header != 0x545e0811)
		{
			THROW_ERROR(L"This is not a scene");

		}
		// sceneName
		std::string sceneName = reader.ReadString();
		UNREFERENCED_PARAMETER(sceneName);


		while (reader.Read<ObjectType>() == ObjectType::SceneObject)
		{
			auto parent = LoadSceneObject(reader, nullptr);

			const UINT childs = reader.Read<UINT>();
			for (UINT i{ 0 }; i < childs; ++i)
			{
				reader.Read<ObjectType>(); //no need to check, this is always an SeneObject.
				LoadSceneObject(reader, parent);
				reader.Read<unsigned int>(); //no need to save, only 1 depth child relation allowed
			}
		}

		PostInitialize();
		m_IsLoaded = true;
	}
	catch (TyrException & e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
	}
	
}

void tyr::Scene::UnLoad()
{
	//TODO: CALL Unload on sceneObject if implemented
	m_IsLoaded = false;
}

void tyr::Scene::AddSceneObject(SceneObject* pObj)
{
	pObj->m_pContext = m_pContext;
	pObj->Initialize();
	
	m_pSceneObjects.emplace_back(pObj);
}

void tyr::Scene::BufferSceneObject(SceneObject* pObj)
{
	pObj->m_pContext = m_pContext;
	pObj->Initialize();
	
	m_pBufferedObjects.emplace_back(pObj);
}

void tyr::Scene::Update()
{
	if(!m_pBufferedObjects.empty())
	{
		for (auto pS: m_pBufferedObjects)
		{
			//pS->m_pContext = m_pContext;
			//pS->Load();
			m_pSceneObjects.emplace_back(pS);
		}
		m_pBufferedObjects.clear();
		
		
	}

	CheckForDestroyedObjects();


	
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Update(); });
}

void tyr::Scene::FixedUpdate()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->FixedUpdate(); });
}

tyr::SceneObject* tyr::Scene::GetFirstSceneObjectWithTag(Tag tag) const
{
	const auto found = std::find_if(m_pSceneObjects.begin(), m_pSceneObjects.end(), [tag](SceneObject* pS) {return pS->GetTag() == tag; });
	if (found != m_pSceneObjects.end())
		return *found;

	return nullptr;
	
}

tyr::SceneObject* tyr::Scene::GetFirstObjectWithName(const std::string& name) const
{
	const auto found = std::find_if(m_pSceneObjects.begin(), m_pSceneObjects.end(), [name](SceneObject* pS) {return pS->GetName() == name; });
	if (found != m_pSceneObjects.end())
		return *found;

	return nullptr;
}

void tyr::Scene::CheckForDestroyedObjects()
{
	UINT size = static_cast<UINT>(m_pSceneObjects.size());
	for (UINT i{ 0 }; i < size; i++)
	{
		if (m_pSceneObjects[i]->IsDestroyed())
		{
			SceneObject* pDeleteObject = m_pSceneObjects[i];
			if (i == m_pSceneObjects.size() - 1)
			{
				m_pSceneObjects.pop_back();
				SAFE_DELETE(pDeleteObject);
				break; //Break to avoid mistakes, should not happen because it is the last one in the vec
			}
			//else

			m_pSceneObjects.erase(std::find(m_pSceneObjects.begin(), m_pSceneObjects.end(), pDeleteObject));
			SAFE_DELETE(pDeleteObject);
			size--;
		}
	}
}

void tyr::Scene::PostInitialize()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* pS) { pS->PostInitialize(); });
}

#ifdef EDITOR_MODE
void tyr::Scene::RenderEditor()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Debug(); });

	if (!SDXL_ImGui_Begin(m_Name.c_str(), nullptr)) return;


	static int itemPopUP = -1;
	
	for(int i{0}; i < static_cast<int>(m_pSceneObjects.size()); i++)
	{
		if (SDXL_ImGui_Selectable(m_pSceneObjects[i]->GetEditorName().c_str(), m_SelectedItem == i, SDXL_ImGuiSelectableFlags_AllowDoubleClick | SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			m_SelectedItem = i;
			m_pSceneObjects.at(m_SelectedItem)->m_SelectedItem = -1;
			if(SDXL_ImGui_IsItemHovered() && SDXL_ImGui_IsMouseDoubleClicked(0))
			{
				m_ItemDoubleClicked = !m_ItemDoubleClicked;
			}
		}
		if (i == m_SelectedItem)
		{
			m_pSceneObjects.at(m_SelectedItem)->RenderEditor(m_ItemDoubleClicked);
			
		}

		//if (SDXL_ImGui_IsItemHovered() || itemPopUP == i)
		//{
		//
		//	if (SDXL_ImGui_BeginPopupContextWindow("SceneObjectNameEditor"))
		//	{
		//	
		//		SDXL_ImGui_EndPopup();
		//	}
		//	else
		//	{
		//		itemPopUP = -1;
		//	}
		//}
	}


	
	SDXL_ImGui_Separator();

	if(m_pContext->paused) //Only Add SceneObject when paused
	{
		ESceneObjectManipulation();

	}


	
	SDXL_ImGui_End();
}

void tyr::Scene::Save()
{
	std::stringstream ss;
	ss << ContentManager::GetInstance()->GetAbsoluteSceneFolder();
	ss << m_Name << SCENE_SUFFIX;
	
	BinaryWriter writer(ss.str());
	if(writer.IsOpen())
	{
		ULONG64 header = 0x545e0811;
		writer.Write(header);
		
		writer.WriteString(m_Name);
		std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [&writer](SceneObject* s) {s->Save(writer); });


		
		writer.Write(ObjectType::End);


		writer.Close();
	}
	
	//Save name
	//Save Objects

	
	
}

tyr::Scene* tyr::Scene::GenerateNew(const std::string& name, const std::string& path)
{
	Scene* returnScene = new Scene(name, path);
	returnScene->Save();
	return returnScene;
}



void tyr::Scene::ESceneObjectManipulation()
{
	if (m_SelectedItem != -1)
	{
		if(SDXL_ImGui_Button("Add Child##Scene"))
		{
			m_pSceneObjects[m_SelectedItem]->AddChild(new SceneObject());
		}
	} SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add Object##Scene"))
	{
		AddSceneObject(new SceneObject());

	}

	if (m_SelectedItem != -1)
	{
		SDXL_ImGui_SameLine();


		if (SDXL_ImGui_Button("Remove Object##Scene"))
		{
			m_pSceneObjects[m_SelectedItem]->Destroy();
			m_SelectedItem = -1;
			CheckForDestroyedObjects();
		}
	}

	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("UP##Scene"))
	{
		if (m_SelectedItem > 0)
		{
			auto temp = m_pSceneObjects[m_SelectedItem - 1];
			m_pSceneObjects[m_SelectedItem - 1] = m_pSceneObjects[m_SelectedItem];
			m_pSceneObjects[m_SelectedItem] = temp;
			m_SelectedItem--;

		}
	}
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("DOWN##Scene"))
	{
		if (m_SelectedItem >= 0 && m_SelectedItem < static_cast<int>(m_pSceneObjects.size() - 1))
		{
			auto temp = m_pSceneObjects[m_SelectedItem + 1];
			m_pSceneObjects[m_SelectedItem + 1] = m_pSceneObjects[m_SelectedItem];
			m_pSceneObjects[m_SelectedItem] = temp;
			m_SelectedItem++;
			CONTENT_MANAGER->Save();

		}
	}
}
#endif
void tyr::Scene::Flush()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {SAFE_DELETE(s)});
	m_pSceneObjects.clear();
}
void tyr::Scene::Render() const
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Render(); });
}



tyr::SceneObject* tyr::Scene::LoadSceneObject(tyr::BinaryReader& reader, tyr::SceneObject* parent)
{
	SceneObject* newObject = nullptr;
	const std::string newObjectName = reader.ReadString();
	const Tag objectTag = reader.Read<Tag>();
	const bool isActive = reader.Read<bool>();

	UINT size = reader.Read<UINT>();
	for (UINT i{ 0 }; i < size; i++)
	{
		const ComponentType type = reader.Read<ComponentType>();

		//maybe one function to just pass component type
		switch (type)
		{
		case ComponentType::Transform: //should always be the first
			newObject = new SceneObject(Factory::CreateComponent<TransformComp>(reader), newObjectName, objectTag);
			newObject->SetActive(isActive);
			
			if (parent) parent->AddChild(newObject);
			else
				AddSceneObject(newObject);
			break;
		case ComponentType::CharacterController:
			newObject->AddComponent(Factory::CreateComponent<CharacterControllerComp>(reader));
			break;
		case ComponentType::Collider:
			newObject->AddComponent(Factory::CreateComponent<ColliderComp>(reader));
			break;
		case ComponentType::FPS:
			newObject->AddComponent(Factory::CreateComponent<FPSComp>(reader));
			break;
		case ComponentType::RigidBody:
			newObject->AddComponent(Factory::CreateComponent<RigidBodyComp>(reader));
			break;
		case ComponentType::Text:
			newObject->AddComponent(Factory::CreateComponent<TextComp>(reader));
			break;
		case ComponentType::Texture:
			newObject->AddComponent(Factory::CreateComponent<TextureComp>(reader));
			break;
		case ComponentType::PlayerController:
			newObject->AddComponent(Factory::CreateComponent<PlayerController>(reader)); //WIP
			break;
		case ComponentType::Animator:
			newObject->AddComponent(Factory::CreateComponent<AnimatorComp>(reader));
			break;
		case ComponentType::BubbleShooting:
			newObject->AddComponent(Factory::CreateComponent<BubbleShootingComp>(reader));
			break;
		case ComponentType::Maita:
			newObject->AddComponent(Factory::CreateComponent<MaitaComp>(reader));
			break;
		case ComponentType::ZenChan:
			newObject->AddComponent(Factory::CreateComponent<ZenChanComp>(reader));
			break;
		case ComponentType::PlayerHealth:
			newObject->AddComponent(Factory::CreateComponent<PlayerHealthComp>(reader));
			break;
		case ComponentType::HealthDisplay:
			newObject->AddComponent(Factory::CreateComponent<HealthDisplayComp>(reader));
			break;
		case ComponentType::MenuSelector:
			newObject->AddComponent(Factory::CreateComponent<MenuSelectorComp>(reader));
			break;
		case ComponentType::Button:
			newObject->AddComponent(Factory::CreateComponent<ButtonComp>(reader));
			break;
		case ComponentType::Food:
			newObject->AddComponent(Factory::CreateComponent<FoodComp>(reader));
			break;
		case ComponentType::ScoreDisplay:
			newObject->AddComponent(Factory::CreateComponent<ScoreDisplayComp>(reader));
			break;
		case ComponentType::AutoDestroy:
			newObject->AddComponent(Factory::CreateComponent<AutoDestroyComp>(reader));
			break;
		case ComponentType::Rock:
			newObject->AddComponent(Factory::CreateComponent<RockComp>(reader));
			break;
		default:
			THROW_ERROR(L"This component is not implemented yet");
		}


	}
	return newObject;
}
