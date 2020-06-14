#include "tyrpch.h"
#include "BubbleShootingComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "SceneObject.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TeiwazEngine.h"
#include "Time.h"
tyr::BubbleShootingComp::BubbleShootingComp()
	: BaseComponent(ComponentType::BubbleShooting, "Bubble Shooting Component")
	, m_ShootCDElapser(0.5f)
	, m_CanShoot(false)
	, m_PlayerID(0)
	, m_IsShooting(false)
{
}

void tyr::BubbleShootingComp::Initialize()
{
	m_PlayerID = GET_COMPONENT<PlayerController>()->GetPlayerID();
	m_pAni = GET_COMPONENT<AnimatorComp>();
}

void tyr::BubbleShootingComp::Update()
{
	if (m_ShootCDElapser.Update(TIME->deltaTime))
		m_CanShoot = true;

	if(m_PlayerID == 1)
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P1Shoot") && m_CanShoot)
		{
			m_CanShoot = false;
			m_ShootCDElapser.Reset();

			CreateBubble();

			m_IsShooting = true;
			m_pAni->SetBool("IsEating", true);
		}
	}
	else
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P2Shoot") && m_CanShoot)
		{
			m_CanShoot = false;
			m_ShootCDElapser.Reset();

			CreateBubble();


		}
	}


	if(m_IsShooting)
	{
		if(m_pAni->IsAtEnd())
		{
			m_IsShooting = false;
			m_pAni->SetBool("IsEating", false);
		}
	}


}

void tyr::BubbleShootingComp::FixedUpdate()
{

#ifdef EDITOR_MODE
	m_PlayerID = GET_COMPONENT<PlayerController>()->GetPlayerID();
#endif
}
#ifdef EDITOR_MODE
void tyr::BubbleShootingComp::InternalRenderEditor()
{

}

void tyr::BubbleShootingComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
#endif
tyr::SceneObject* tyr::BubbleShootingComp::CreateBubble() const
{
	auto newPos = m_pSceneObject->GetTransform()->GetPositionRaw();


	bool isGoingLeft = GET_COMPONENT<PlayerController>()->IsGoingLeft();
	if(isGoingLeft)
		newPos.x -= 50.f;
	else
		newPos.x += 50.f;

	newPos.y += 2.f;



	
	auto pReturnObj = new SceneObject(Transform(newPos), "Bubble Object", Tag::Bubble, true);
	GET_CONTEXT->pSceneManager->GetCurrentScene()->BufferSceneObject(pReturnObj);


	pReturnObj->AddComponent(new BubbleComp(isGoingLeft));

	
	return pReturnObj;
}
