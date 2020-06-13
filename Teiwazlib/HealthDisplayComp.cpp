#include "tyrpch.h"
#include "HealthDisplayComp.h"
#include "BinaryWriter.h"
tyr::HealthDisplayComp::HealthDisplayComp()
	: tyr::BaseComponent(ComponentType::HealthDisplay, "HealthDisplay Component")
{
}

void tyr::HealthDisplayComp::Initialize()
{
}

#ifdef EDITOR_MODE


void tyr::HealthDisplayComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}

void tyr::HealthDisplayComp::InternalRenderEditor()
{
}
#endif
