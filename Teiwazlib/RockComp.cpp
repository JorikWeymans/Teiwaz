#include "tyrpch.h"
#include "RockComp.h"
#include "BinaryWriter.h"
tyr::RockComp::RockComp()
	: BaseComponent(ComponentType::Rock, "Auto Destroy Component")
{
}

void tyr::RockComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::RockComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}

void tyr::RockComp::InternalRenderEditor()
{
}
#endif
