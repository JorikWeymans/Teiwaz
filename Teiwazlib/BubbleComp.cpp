#include "tyrpch.h"
#include "BubbleComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
tyr::BubbleComp::BubbleComp()
	: BaseComponent(ComponentType::BubbleComp)
	, m_pBody(nullptr)
{
}

void tyr::BubbleComp::Initialize()
{
	m_pSceneObject->AddComponent(new CharacterControllerComp());
	m_pBody = m_pSceneObject->AddComponent(new RigidBodyComp(0.f, false,4.f));
	m_pBody->AddForce(-300.f, 0.f);
	
}

void tyr::BubbleComp::Update()
{
		
}

void tyr::BubbleComp::FixedUpdate()
{
	//m_pController->Move(1.f, 0.f);
	if(std::abs(m_pBody->GetForce().x) < 0.2)
	{
		float pos = m_pSceneObject->GetTransform()->GetPositionRaw().y;
		if(pos < 560.f)
			m_pBody->AddForce(0.f, 1.f);

		
	}
}

#ifdef EDITOR_MODE
void tyr::BubbleComp::RenderEditor()
{
}

void tyr::BubbleComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
	//Don't save this component
}
#endif
