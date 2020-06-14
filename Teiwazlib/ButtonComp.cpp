#include "tyrpch.h"
#include "ButtonComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "EnumDropdown.h"
#include "Buttons.h"
tyr::ButtonComp::ButtonComp(ButtonType type, const Color& selected, const Color& notSelected)
	: BaseComponent(ComponentType::Button, "Button Component")
	, m_ButtonType(type)
	, m_pTextComp(nullptr)
	, m_ColorSelected(selected)
	, m_ColorNotSelected(notSelected)
	, m_pButton(nullptr)
{
	
}

tyr::ButtonComp::ButtonComp(ButtonType type, const Color_POD& selected, const Color_POD& notSelected)
	: ButtonComp(type,Color(selected.r, selected.g, selected.b, selected.a),
		Color(notSelected.r, notSelected.g, notSelected.b, notSelected.a))
{}

tyr::ButtonComp::~ButtonComp()
{
	SAFE_DELETE(m_pButton);
}

void tyr::ButtonComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));
	m_pTextComp = GET_COMPONENT<TextComp>();
	SetButton();
}

void tyr::ButtonComp::Update()
{
}
void tyr::ButtonComp::Select()
{
	m_pTextComp->SetColor(m_ColorSelected);
}

void tyr::ButtonComp::DeSelect()
{
	m_pTextComp->SetColor(m_ColorNotSelected);
}

void tyr::ButtonComp::Execute()
{
	m_pButton->Execute();
}
#ifdef EDITOR_MODE

void tyr::ButtonComp::Debug()
{
}
void tyr::ButtonComp::InternalRenderEditor()
{
	std::string name;
	std::string stringedID = std::to_string(m_UniqueId);

	const ButtonType prevType = m_ButtonType;
	SDXL_ImGui_Text("Type:   \t");
	SDXL_ImGui_SameLine();
	name = "##ButtonCompButtonType" + stringedID;
	DROPDOWN_BUTTON_TYPE(name.c_str(), m_ButtonType);

	if(prevType != m_ButtonType)
	{
		SetButton();
	}


	

	SDXL_ImGui_Text("selec:  \t");
	SDXL_ImGui_SameLine(); SDXL_ImGui_SetNextItemWidth(250.f);
	name = "##MenuSelectorCompSelected" + stringedID;
	SDXL_ImGui_ColorEdit4(name.c_str(), &m_ColorSelected.r);

	SDXL_ImGui_Text("Not selec:  ");
	SDXL_ImGui_SameLine(); SDXL_ImGui_SetNextItemWidth(250.f);
	name = "##MenuSelectorCompNotSelected" + stringedID;
	SDXL_ImGui_ColorEdit4(name.c_str(), &m_ColorNotSelected.r);
	
}

void tyr::ButtonComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_ButtonType);
	writer.Write(m_ColorSelected.ToPOD());
	writer.Write(m_ColorNotSelected.ToPOD());
	
}

void tyr::ButtonComp::SetButton()
{
	SAFE_DELETE(m_pButton);

	
	switch (m_ButtonType)
	{
	case ButtonType::QuitGame:
		m_pButton = new QuitButton(GET_CONTEXT);
		break;
	case ButtonType::Start:
		m_pButton = new LoadScene1Button(GET_CONTEXT);
		break;
	default:;
	}
}
#endif
