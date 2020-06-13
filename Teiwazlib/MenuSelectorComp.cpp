#include "tyrpch.h"
#include "MenuSelectorComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
tyr::MenuSelectorComp::MenuSelectorComp()
	:BaseComponent(ComponentType::MenuSelector, "Menu Selector Component")
{
}

tyr::MenuSelectorComp::~MenuSelectorComp()
{
}

void tyr::MenuSelectorComp::Initialize()
{

}

void tyr::MenuSelectorComp::PostInitialize()
{
	auto test = GET_COMPONENT_IN_CHILD<TextComp>(0);
	auto test2 = GET_COMPONENT_IN_CHILD<TextComp>(1);
	UNREFERENCED_PARAMETER(test);
	UNREFERENCED_PARAMETER(test2);
}

void tyr::MenuSelectorComp::Update()
{

}

#ifdef EDITOR_MODE
void tyr::MenuSelectorComp::Debug()
{
}

void tyr::MenuSelectorComp::InternalRenderEditor()
{
}

void tyr::MenuSelectorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	UNREFERENCED_PARAMETER(writer);
}
#endif
