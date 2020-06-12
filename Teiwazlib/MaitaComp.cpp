#include "tyrpch.h"
#include "MaitaComp.h"

tyr::MaitaComp::MaitaComp()
	:BaseComponent(ComponentType::Maita, "Maita Component")
{
}

tyr::MaitaComp::~MaitaComp()
{
}

void tyr::MaitaComp::Initialize()
{
}

void tyr::MaitaComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::MaitaComp::Debug()
{
}

void tyr::MaitaComp::InternalRenderEditor()
{
}

void tyr::MaitaComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
}
#endif
