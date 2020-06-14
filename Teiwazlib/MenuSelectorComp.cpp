#include "tyrpch.h"
#include "MenuSelectorComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "TeiwazEngine.h"

tyr::MenuSelectorComp::MenuSelectorComp()
	:BaseComponent(ComponentType::MenuSelector, "Menu Selector Component")
	, m_Selected(0)
{
}



tyr::MenuSelectorComp::~MenuSelectorComp()
{
}

void tyr::MenuSelectorComp::Initialize()
{
	GET_CONTEXT->pInput->AddAction("MenuUP", tyr::ButtonState::Pressed, 'W', ControllerButton::ButtonLS);
	GET_CONTEXT->pInput->AddAction("MenuDown", tyr::ButtonState::Pressed, 'S', ControllerButton::ButtonRS);
	GET_CONTEXT->pInput->AddAction("Confirm", tyr::ButtonState::Pressed, VK_SPACE, ControllerButton::ButtonA);
}

void tyr::MenuSelectorComp::PostInitialize()
{
	m_pButtons.resize(2);
	m_pButtons[0] = GET_COMPONENT_IN_CHILD<ButtonComp>(0);
	m_pButtons[1] = GET_COMPONENT_IN_CHILD<ButtonComp>(1);


	
	const UINT size = static_cast<UINT>(m_pButtons.size());
	for(UINT i{1}; i < size; i++)
	{
		m_pButtons[i]->DeSelect();
	}
	m_pButtons[0]->Select();
}

void tyr::MenuSelectorComp::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("MenuUP"))
	{
		std::for_each(m_pButtons.begin(), m_pButtons.end(), [](ButtonComp* pB) {pB->DeSelect(); });
		if (m_Selected == m_pButtons.size() - 1)
			m_Selected = 0;
		else
			m_Selected++;

		m_pButtons[m_Selected]->Select();
		
	}

	if (GET_CONTEXT->pInput->IsActionTriggered("MenuDown"))
	{
		std::for_each(m_pButtons.begin(), m_pButtons.end(), [](ButtonComp* pB) {pB->DeSelect(); });
		if (m_Selected == 0)
			m_Selected = m_pButtons.size() - 1;
		else
			m_Selected--;

		m_pButtons[m_Selected]->Select();
	}


	if (GET_CONTEXT->pInput->IsActionTriggered("Confirm"))
	{
		m_pButtons[m_Selected]->Execute();
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
