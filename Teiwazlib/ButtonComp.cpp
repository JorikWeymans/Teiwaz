#include "tyrpch.h"
#include "ButtonComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "EnumDropdown.h"

tyr::ButtonComp::ButtonComp(ButtonType type, const Color& selected, const Color& notSelected)
	: BaseComponent(ComponentType::Button, "Button Component")
	, m_ButtonType(type)
	, m_ColorSelected(selected)
	, m_ColorNotSelected(notSelected)
	, m_pTextComp(nullptr)
{
}

tyr::ButtonComp::ButtonComp(ButtonType type, const Color_POD& selected, const Color_POD& notSelected)
	: ButtonComp(type,Color(selected.r, selected.g, selected.b, selected.a),
		Color(notSelected.r, notSelected.g, notSelected.b, notSelected.a))
{}

tyr::ButtonComp::~ButtonComp()
{
}

void tyr::ButtonComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));
	m_pTextComp = GET_COMPONENT<TextComp>();

}

void tyr::ButtonComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::ButtonComp::Select()
{
	m_pTextComp->SetColor(m_ColorSelected);
}

void tyr::ButtonComp::DeSelect()
{
	m_pTextComp->SetColor(m_ColorNotSelected);
}

void tyr::ButtonComp::Debug()
{
}

void tyr::ButtonComp::InternalRenderEditor()
{
	std::string name;
	std::string stringedID = std::to_string(m_UniqueId);
	SDXL_ImGui_Text("Type:   \t");
	SDXL_ImGui_SameLine();
	name = "##ButtonCompButtonType" + stringedID;
	DROPDOWN_BUTTON_TYPE(name.c_str(), m_ButtonType);



	

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
#endif
