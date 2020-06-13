#include "tyrpch.h"
#include "PlayerHealthComp.h"

tyr::PlayerHealthComp::PlayerHealthComp()
	: tyr::BaseComponent(ComponentType::PlayerHealth, "PlayerHealth Component")
	, m_NmbrLives(3)
{
}

void tyr::PlayerHealthComp::Initialize()
{
}

#ifdef EDITOR_MODE
void tyr::PlayerHealthComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
}

void tyr::PlayerHealthComp::InternalRenderEditor()
{
}
#endif
