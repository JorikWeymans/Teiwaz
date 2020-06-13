#include "tyrpch.h"
#include "HealthDisplayComp.h"
#include "BinaryWriter.h"
#include "SceneObject.h"
#include "GameContext.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TyrComps.h"
tyr::HealthDisplayComp::HealthDisplayComp()
	: tyr::BaseComponent(ComponentType::HealthDisplay, "HealthDisplay Component")
	, m_pTexture(nullptr)
	, m_OnHealthChangedFunction(std::bind(&HealthDisplayComp::OnHealthChanged, this, std::placeholders::_1))
{
}

void tyr::HealthDisplayComp::Initialize()
{
	auto obj = GET_OBJECT_WITH_NAME("Player1");

	obj->GetComponent<PlayerHealthComp>()->AddOnHealthChangedFunction(&m_OnHealthChangedFunction);
	m_pTexture = GET_COMPONENT<TextureComp>();
}

void tyr::HealthDisplayComp::OnHealthChanged(int amountLeft)
{
	m_pTexture->SetRepeatingX(amountLeft);
	
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
