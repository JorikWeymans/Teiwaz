#include "tyrpch.h"
#include "PlayerHealthComp.h"
#include "BinaryWriter.h"
tyr::PlayerHealthComp::PlayerHealthComp()
	: tyr::BaseComponent(ComponentType::PlayerHealth, "PlayerHealth Component")
	, m_NmbrLives(3)
{
}

void tyr::PlayerHealthComp::Initialize()
{
}
void tyr::PlayerHealthComp::RemoveHealth()
{
	m_NmbrLives--;
}
#ifdef EDITOR_MODE


void tyr::PlayerHealthComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);	
}

void tyr::PlayerHealthComp::InternalRenderEditor()
{
}
#endif
