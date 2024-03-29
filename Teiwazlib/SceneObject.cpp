#include "tyrpch.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComp.h"
#include <algorithm>
#include "BinaryWriter.h"
#include "TyrComps.h"
#include <string_view>
#include "EnumDropdown.h"
#include "ContentManager.h"
int tyr::SceneObject::counter = 0;
tyr::SceneObject::SceneObject(const tyr::Transform& transform, const std::string& name, Tag tag, bool AppendCounter)
	: SceneObject(new TransformComp(transform), name, tag, AppendCounter) {}

tyr::SceneObject::SceneObject(TransformComp* pTransform, const std::string& name, Tag tag, bool AppendCounter)
	: m_pComponents(std::vector<BaseComponent*>())
	, m_pChilds(std::vector<SceneObject*>())
	, m_pParent(nullptr)
	, m_pTransform(pTransform)
	, m_IsDestroyed(false)
	, m_name(name)
	, m_pContext(nullptr)
	, m_Tag(tag)
	, m_IsActive(true)
#ifdef EDITOR_MODE
	, m_SelectedItem(-1)
#endif

{
	if (AppendCounter)
		m_name += std::to_string(counter);
	counter++;

#ifdef EDITOR_MODE

	strcpy_s(m_ChangedObjectName, m_name.c_str());


	auto intID = reinterpret_cast<uint32_t>(this);
	m_UniqueId = "##" + std::to_string(intID); //Add the ## because we don't want to see that ID in the editor



	
#endif
}

tyr::SceneObject::SceneObject()
	: SceneObject(Transform(Vector2()))
{
}

tyr::SceneObject::~SceneObject()
{
	SAFE_DELETE(m_pTransform);
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](BaseComponent* b) {SAFE_DELETE(b)});
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [](SceneObject* s) {SAFE_DELETE(s)});
}

void tyr::SceneObject::Update()
{
	CheckForDestroyedChilds();
	CheckForDestroyedComponents();
	
	if(m_IsActive)
	{
		//gameobject can be destroyed in ever comp, so that's why it is checked ever time
		std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if(!m_IsDestroyed)
				s->Update();
		});
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
		{
			if(!m_IsDestroyed)
				b->Update();
		});
	}
}

void tyr::SceneObject::Destroy()
{
	m_IsDestroyed = true;
}

void tyr::SceneObject::FixedUpdate()
{
	if (m_IsActive)
	{
		std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
			{
				if (!m_IsDestroyed)
					s->FixedUpdate();
			});


		std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
			{
				if (!m_IsDestroyed && !b->IsDestroyed())
					b->FixedUpdate();
			});
	}

}

void tyr::SceneObject::SetActive(bool value) noexcept
{
	m_IsActive = value;
}
#ifdef EDITOR_MODE
void tyr::SceneObject::Debug()
{
	if(m_IsActive)
	{
		std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
			{
				if (!m_IsDestroyed)
					s->Debug();
			});


		std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
			{
				if (!m_IsDestroyed)
					b->Debug();
			});
	}

	
}

void tyr::SceneObject::RenderEditor(bool showChildren)
{
	
	if(!m_pChilds.empty() && showChildren)
	{
		SDXL_ImGui_Indent();
		
		for (int i{ 0 }; i < static_cast<int>(m_pChilds.size()); i++)
		{
			if (SDXL_ImGui_Selectable(m_pChilds[i]->GetEditorName().c_str(), m_SelectedItem == i))
			{
				m_SelectedItem = i;

			}

		}

		if (m_SelectedItem != -1)
		{
			m_pChilds.at(m_SelectedItem)->RenderEditor(showChildren);

			ESceneObjectManipulation();

		}
		
		SDXL_ImGui_Unindent();
	}

	if(m_SelectedItem == -1)
	{
		
		if (SDXL_ImGui_Begin("Inspector"))
		{
			RenderProperties();
			
			m_pTransform->RenderEditor();
			std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
				{
					if (!m_IsDestroyed)
						b->RenderEditor();
				});

			AddComponentButton();

			SDXL_ImGui_End();
		}
		
	}
	
	

}

void tyr::SceneObject::Save(BinaryWriter& writer)
{
	writer.Write(ObjectType::SceneObject);
	writer.WriteString(m_name);
	writer.Write(m_Tag);
	writer.Write(m_IsActive);
	
	UINT size = m_pComponents.size() + 1; //+1 is for the transform comp not saved in vec
	writer.Write(size);
	m_pTransform->Save(writer);
	//Save transform
	
	
	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&writer](BaseComponent* b) { b->Save(writer); });
	
	//Save Childs
	writer.Write(m_pChilds.size());
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&writer](SceneObject* s) { s->Save(writer); });
	//Save components
	
}

void tyr::SceneObject::AddComponentButton()
{
	//When playing, you are not able to add Components
	if (!m_pContext->paused)
		return;
	
	SDXL_ImGui_Separator();

	static ComponentType selectedComp = ComponentType::CharacterController;
	DROPDOWN_COMPONENT_TYPE("##ComponentsSceneObj", selectedComp);
	

	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add Component"))
	{
		

		BaseComponent* theComp = nullptr;
		bool usedNotImplemented = false;
		switch (selectedComp)
		{
			case ComponentType::CharacterController:
				theComp = new CharacterControllerComp();
			break;
			case ComponentType::Collider:
				theComp = new ColliderComp(100, 100, PivotMode::TopLeft, false);
			break;
			case ComponentType::FPS:
				theComp = new FPSComp(FPSCompType::Update);
			break;
			case ComponentType::RigidBody:
				theComp = new RigidBodyComp(-150.f);
			break;
			case ComponentType::Text:
				theComp = new TextComp(0, "New Text", Color(1, 1, 1, 1));
			break;
			case ComponentType::Texture:
				theComp = new TextureComp(0);
			break;
			case ComponentType::Transform:
				usedNotImplemented = true;
			break;
			case ComponentType::PlayerController:
				theComp = new PlayerController();
			break;
			case ComponentType::Animator:
				theComp = new AnimatorComp();
			break;
			case ComponentType::BubbleShooting:
				theComp = new BubbleShootingComp();
			break;
			case ComponentType::ZenChan:
				theComp = new ZenChanComp();
				break;
			case ComponentType::Maita:
				theComp = new MaitaComp();
				break;
			case ComponentType::PlayerHealth:
				theComp = new PlayerHealthComp();
				break;
			case ComponentType::HealthDisplay:
				theComp = new HealthDisplayComp();
				break;
			case ComponentType::MenuSelector:
				theComp = new MenuSelectorComp();
				break;
			case ComponentType::Button:
				theComp = new ButtonComp();
				break;
			case ComponentType::Food:
				theComp = new FoodComp();
				break;
			case ComponentType::ScoreDisplay:
				theComp = new ScoreDisplayComp();
				break;
			case ComponentType::AutoDestroy:
				theComp = new AutoDestroyComp(2.f);
				break;
			case ComponentType::Rock:
				theComp = new RockComp();
				break;
			default:
				usedNotImplemented = true;
			 }


		if(usedNotImplemented)
			SDXL_ImGui_ConsoleLogError("This component cannot be added, yet");
	
		else
		{
			AddComponent(theComp);
			SDXL_ImGui_ConsoleLog("The component is added");
		}
		

		

		
	}

}

void tyr::SceneObject::ESceneObjectManipulation()
{
	if (!m_pContext->paused) return;
	
	
	if (SDXL_ImGui_Button("Add Child##SceneObject"))
	{
		AddChild(new SceneObject());
	}
	SDXL_ImGui_SameLine();
	
	
	if (SDXL_ImGui_Button("Remove Child##SceneObject"))
	{
		m_pChilds[m_SelectedItem]->Destroy();
		m_SelectedItem = -1;
		CheckForDestroyedChilds();
	}

	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("UP##SceneObject"))
	{
		if (m_SelectedItem > 0)
		{
			auto temp = m_pChilds[m_SelectedItem - 1];
			m_pChilds[m_SelectedItem - 1] = m_pChilds[m_SelectedItem];
			m_pChilds[m_SelectedItem] = temp;
			m_SelectedItem--;

		}
	}
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("DOWN##SceneObject"))
	{
		if (m_SelectedItem >= 0 && m_SelectedItem < static_cast<int>(m_pChilds.size() - 1))
		{
			auto temp = m_pChilds[m_SelectedItem + 1];
			m_pChilds[m_SelectedItem + 1] = m_pChilds[m_SelectedItem];
			m_pChilds[m_SelectedItem] = temp;
			m_SelectedItem++;
			CONTENT_MANAGER->Save();

		}
	}
	
}
#endif

void tyr::SceneObject::Render() const
{
	if(m_IsActive)
	{
		std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
			{
				if (!m_IsDestroyed)
					s->Render();
			});

		std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
			{
				if (!m_IsDestroyed && !b->IsDestroyed())
					b->Render();
			});
	}

}


void tyr::SceneObject::AddChild(SceneObject* pChild)
{
	auto found = std::find(m_pChilds.begin(), m_pChilds.end(), pChild);
	if (found == m_pChilds.end())
	{
		pChild->m_pContext = m_pContext;
		pChild->Initialize();
		pChild->m_pParent = this;
		m_pChilds.emplace_back(pChild);

	}
	
}

void tyr::SceneObject::Translate(float x, float y)
{
	m_pTransform->Translate(x, y);
}

void tyr::SceneObject::RemoveComponent(BaseComponent* pComp)
{
	pComp->Destroy();

}


void tyr::SceneObject::Initialize()
{
	m_pTransform->m_pSceneObject = this;
	m_pTransform->Initialize();
}

void tyr::SceneObject::PostInitialize()
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s) { s->PostInitialize(); });
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b) { b->PostInitialize(); });
}

void tyr::SceneObject::CheckForDestroyedChilds()
{
	UINT size = static_cast<UINT>(m_pChilds.size());
	for (UINT i{ 0 }; i < size; i++)
	{
		if (m_pChilds[i]->IsDestroyed())
		{
			SceneObject* pDeleteObject = m_pChilds[i];
			if (i == m_pChilds.size() - 1)
			{
				m_pChilds.pop_back();
				SAFE_DELETE(pDeleteObject);
				break; //Break to avoid mistakes, should not happen because it is the last one in the vec
			}
			//else

			m_pChilds.erase(std::find(m_pChilds.begin(), m_pChilds.end(), pDeleteObject));
			SAFE_DELETE(pDeleteObject);
			size--;
		}
	}
}

void tyr::SceneObject::CheckForDestroyedComponents()
{
	UINT size = static_cast<UINT>(m_pComponents.size());
	for (UINT i{ 0 }; i < size; i++)
	{
		if (m_pComponents[i]->IsDestroyed())
		{
			BaseComponent* pDeleteComp = m_pComponents[i];
			if (i == m_pComponents.size() - 1)
			{
				m_pComponents.pop_back();
				SAFE_DELETE(pDeleteComp);
				break; //Break to avoid mistakes, should not happen because it is the last one in the vec
			}
			//else

			m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), pDeleteComp));
			SAFE_DELETE(pDeleteComp);
			size--;
		}
	}
}

#ifdef EDITOR_MODE
void tyr::SceneObject::RenderProperties()
{
	std::string id = "Properties" + m_UniqueId;
	if (SDXL_ImGui_CollapsingHeader(id.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		PropertyChangeName(id);
		PropertyTag(id);

		DROPDOWN_TAG(id.c_str(), m_Tag);

		SDXL_ImGui_Text("Active:  \t");
		SDXL_ImGui_SameLine();
		SDXL_ImGui_Checkbox("##SceneObjectIsActive", &m_IsActive);
		
		
		SDXL_ImGui_PopItemWidth();
	}
}

void tyr::SceneObject::PropertyChangeName(std::string& id)
{
	id = m_UniqueId + "ObjectName";
	SDXL_ImGui_Text("Name:    \t");
	SDXL_ImGui_SameLine();
	SDXL_ImGui_SetNextItemWidth(200.f);
	SDXL_ImGui_InputText(id.c_str(), m_ChangedObjectName, OBJECT_NAME_MAX_CHAR, nullptr);



	id = "Save" + m_UniqueId;
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button(id.c_str()))
	{
		m_name = m_ChangedObjectName;
	}

	id = "x" + m_UniqueId;
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button(id.c_str()))
	{
		strcpy_s(m_ChangedObjectName, m_name.c_str());
	}
}
void tyr::SceneObject::PropertyTag(std::string& id)
{
	id = m_UniqueId + "Tag";
	SDXL_ImGui_Text("Tag:     \t");
	SDXL_ImGui_SameLine();


}
#endif