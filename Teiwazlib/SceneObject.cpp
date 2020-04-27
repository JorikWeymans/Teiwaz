#include "tyrpch.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComp.h"
#include <algorithm>
#include "BinaryWriter.h"
#include "TyrComps.h"
#include <string_view>
int tyr::SceneObject::counter = 0;
tyr::SceneObject::SceneObject(const tyr::Transform& transform, const std::string& name)
	: SceneObject(new TransformComp(transform), name) {}

tyr::SceneObject::SceneObject(TransformComp* pTransform, const std::string& name)
	: m_pComponents(std::vector<BaseComponent*>())
	, m_pChilds(std::vector<SceneObject*>())
	, m_pParent(nullptr)
	, m_pTransform(pTransform)
	, m_IsDestroyed(false)
	, m_name(name)
	, m_pContext(nullptr)
#ifdef USE_IM_GUI
	, m_SelectedItem(-1)
#endif

{
	counter++;
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
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->Update();
		});

	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
			b->Update();
	});
}

void tyr::SceneObject::FixedUpdate()
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->FixedUpdate();
		});

	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
		b->FixedUpdate();
	});
}
#ifdef USE_IM_GUI
void tyr::SceneObject::Debug()
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

void tyr::SceneObject::RenderEditor(bool showChildren)
{
	
	if(!m_pChilds.empty() && showChildren)
	{
		SDXL_ImGui_Indent();


		for (int i{ 0 }; i < static_cast<int>(m_pChilds.size()); i++)
		{
			if (SDXL_ImGui_Selectable(m_pChilds[i]->GetName().c_str(), m_SelectedItem == i))
			{
				m_SelectedItem = i;

			}

		}

		if (m_SelectedItem != -1)
		{
			m_pChilds.at(m_SelectedItem)->RenderEditor(showChildren);
		}

		SDXL_ImGui_Unindent();
	}

	if(m_SelectedItem == -1)
	{
		
		if (SDXL_ImGui_Begin("Inspector"))
		{
			m_pTransform->RenderEditor();
			std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
				{
					if (!m_IsDestroyed)
						b->RenderEditor();
				});

			AddComponentButton();
		}
		
	}
	

}

void tyr::SceneObject::Save(BinaryWriter& writer)
{
	writer.Write(ObjectType::SceneObject);
	writer.WriteString(m_name);
	
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
	SDXL_ImGui_Separator();
	static const int ComponentCount = static_cast<int>(magic_enum::enum_count<ComponentType>());
	static const char* items[ComponentCount];

	if (items[0] == nullptr)
		for (int i = 0; i < ComponentCount; i++)
			items[i] = magic_enum::enum_name(static_cast<ComponentType>(i)).data();

	
	static const char* item_current = items[0];

	SDXL_ImGui_SetNextItemWidth(150.f);
	if (SDXL_ImGui_BeginCombo("##ComponentsSceneObj", item_current, SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < ComponentCount; n++)
		{
			bool is_selected = (item_current == items[n]);
			if (SDXL_ImGui_Selectable(items[n], is_selected))
				item_current = items[n];
			if (is_selected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add Component"))
	{
		AddComponent(new ColliderComp(100, 100, PivotMode::TopLeft, false));
	}
	SDXL_ImGui_End();
}
#endif

void tyr::SceneObject::Render() const
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
		if (!m_IsDestroyed)
			s->Render();
		});
	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{if
		(!m_IsDestroyed)
		b->Render();
	});
}

void tyr::SceneObject::AddComponent(BaseComponent* pComp)
{
	auto found = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if(found == m_pComponents.end())
	{
		pComp->m_pSceneObject = this;
		pComp->Initialize();
		
		m_pComponents.emplace_back(pComp);
		
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

tyr::TransformComp* tyr::SceneObject::GetTransform() const
{
	return m_pTransform;
}

void tyr::SceneObject::Translate(float x, float y)
{
	m_pTransform->Translate(x, y);
}

const tyr::GameContext* tyr::SceneObject::GetGameContext() const
{
	return m_pContext;
}

void tyr::SceneObject::Initialize()
{
	m_pTransform->m_pSceneObject = this;
	m_pTransform->Initialize();
}
