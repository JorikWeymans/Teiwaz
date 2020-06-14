#include "tyrpch.h"
#include "BubbleComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Physics.h"
tyr::BubbleComp::BubbleComp(bool GoLeft)
	: BaseComponent(ComponentType::Bubble, "Bubble Component")
	, m_pBody(nullptr)
	, m_IsGoingLeft(GoLeft)
	, m_OnColliderHitFunction(std::bind(&BubbleComp::OnColliderHit, this, std::placeholders::_1))
{
}

tyr::BubbleComp::~BubbleComp()
{
	if(m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto pColl = GET_COMPONENT<ColliderComp>();
		if (pColl)
		{
			pColl->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
		}
	}

}

void tyr::BubbleComp::Initialize()
{
	ADD_COMPONENT(new TextureComp(3, PivotMode::Center, tyr::Rect(576.f, 0.f, 48.f, 48.f)));
	auto pColliderComp = ADD_COMPONENT(new ColliderComp(48, 48, PivotMode::Center, true));
	ADD_COMPONENT(new CharacterControllerComp());
	ADD_COMPONENT(new AnimatorComp(4));
	
	m_pBody = ADD_COMPONENT(new RigidBodyComp(0.f, false,4.f));

	if(m_IsGoingLeft)
		m_pBody->AddForce(-300.f, 0.f);
	else
		m_pBody->AddForce(300.f, 0.f);


	pColliderComp->AddOnColliderHitFunction(&m_OnColliderHitFunction);
	
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
void tyr::BubbleComp::InternalRenderEditor()
{
}

void tyr::BubbleComp::OnColliderHit(RaycastHit hit)
{
	if(hit.other->GetTag() == Tag::Enemy)
	{
		SDXL_ImGui_ConsoleLog("Enemy hit");
	}
}

void tyr::BubbleComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
	//Don't save this component
}
#endif
