#include "tyrpch.h"
#include "MenuSelectorComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "TeiwazEngine.h"

tyr::MenuSelectorComp::MenuSelectorComp(const Color& selected, const Color& notSelected)
	:BaseComponent(ComponentType::MenuSelector, "Menu Selector Component")
	, m_pStartGame(nullptr)
	, m_pQuitGame(nullptr)
	, m_Selected(0)
	, m_SelectedColor(selected)
	, m_NotSelectedColor(notSelected)
{
}

tyr::MenuSelectorComp::MenuSelectorComp(const Color_POD& selected, const Color_POD& notSelected)
	: MenuSelectorComp(Color(selected.r, selected.g, selected.b, selected.a), 
					Color(notSelected.r, notSelected.g, notSelected.b, notSelected.a))
{
}

tyr::MenuSelectorComp::~MenuSelectorComp()
{
}

void tyr::MenuSelectorComp::Initialize()
{
	GET_CONTEXT->pInput->AddAction("MenuUP", tyr::ButtonState::Pressed, 'W');
	GET_CONTEXT->pInput->AddAction("MenuDown", tyr::ButtonState::Pressed, 'S');
	GET_CONTEXT->pInput->AddAction("Confirm", tyr::ButtonState::Pressed, VK_SPACE);
}

void tyr::MenuSelectorComp::PostInitialize()
{
	m_pStartGame = GET_COMPONENT_IN_CHILD<TextComp>(0);
	m_pQuitGame = GET_COMPONENT_IN_CHILD<TextComp>(1);

	m_pStartGame->SetColor(m_SelectedColor);
	m_pQuitGame->SetColor(m_NotSelectedColor);
}

void tyr::MenuSelectorComp::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("MenuUP"))
	{
		if (m_Selected == 1)
		{
			m_Selected = 0;
			m_pStartGame->SetColor(m_SelectedColor);
			m_pQuitGame->SetColor(m_NotSelectedColor);

		}
	}

	if (GET_CONTEXT->pInput->IsActionTriggered("MenuDown"))
	{
		if(m_Selected ==0)
		{
			m_Selected = 1;
			m_pStartGame->SetColor(m_NotSelectedColor);
			m_pQuitGame->SetColor(m_SelectedColor);
			
		}
	}


	if (GET_CONTEXT->pInput->IsActionTriggered("Confirm"))
	{
		if(m_Selected == 1)
		{
			TeiwazEngine::WantQuit = true;
		}
	}
}

#ifdef EDITOR_MODE
void tyr::MenuSelectorComp::Debug()
{
}

void tyr::MenuSelectorComp::InternalRenderEditor()
{
	std::string name;
	std::string stringedID = std::to_string(m_UniqueId);
	
	SDXL_ImGui_Text("Color:  \t");
	SDXL_ImGui_SameLine(); SDXL_ImGui_SetNextItemWidth(250.f);
	name = "##MenuSelectorCompSelected" + stringedID;
	SDXL_ImGui_ColorEdit4(name.c_str(), &m_SelectedColor.r);

	SDXL_ImGui_Text("Color:  \t");
	SDXL_ImGui_SameLine(); SDXL_ImGui_SetNextItemWidth(250.f);
	name = "##MenuSelectorCompNotSelected" + stringedID;
	SDXL_ImGui_ColorEdit4(name.c_str(), &m_NotSelectedColor.r);
	
}

void tyr::MenuSelectorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_SelectedColor.ToPOD());
	writer.Write(m_NotSelectedColor.ToPOD());
	UNREFERENCED_PARAMETER(writer);
}
#endif
