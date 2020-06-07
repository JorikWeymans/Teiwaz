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
	ADD_COMPONENT(new TextureComp(3, PivotMode::Center, tyr::Rect(576.f, 0.f, 48.f, 48.f)));
	ADD_COMPONENT(new ColliderComp(48, 48, PivotMode::Center, false));
	ADD_COMPONENT(new CharacterControllerComp());
	
	m_pBody = ADD_COMPONENT(new RigidBodyComp(0.f, false,4.f));
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
