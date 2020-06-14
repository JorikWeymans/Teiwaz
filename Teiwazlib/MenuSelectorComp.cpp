#include "tyrpch.h"
#include "MenuSelectorComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "TeiwazEngine.h"

tyr::MenuSelectorComp::MenuSelectorComp()
	:BaseComponent(ComponentType::MenuSelector, "Menu Selector Component")
	, m_pStartGame(nullptr)
	, m_pQuitGame(nullptr)
	, m_Selected(0)
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

	//m_pStartGame->SetColor(m_SelectedColor);
	//m_pQuitGame->SetColor(m_NotSelectedColor);
}

void tyr::MenuSelectorComp::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("MenuUP"))
	{
		if (m_Selected == 1)
		{
			m_Selected = 0;
			//m_pStartGame->SetColor(m_SelectedColor);
			//m_pQuitGame->SetColor(m_NotSelectedColor);

		}
	}

	if (GET_CONTEXT->pInput->IsActionTriggered("MenuDown"))
	{
		if(m_Selected ==0)
		{
			m_Selected = 1;
			//m_pStartGame->SetColor(m_NotSelectedColor);
			//m_pQuitGame->SetColor(m_SelectedColor);
			
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
	UNREFERENCED_PARAMETER(name);
	UNREFERENCED_PARAMETER(stringedID);

	
}

void tyr::MenuSelectorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
#endif
