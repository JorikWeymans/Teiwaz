#include "tyrpch.h"
#include "ZenChanStates.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Physics.h"
#include "Time.h"

// *----------------*
// *----- BASE -----*
// *----------------*
#pragma region Base
tyr::ZenChanState::ZenChanState(GameContext const* pContext, SceneObject* pSceneObject)
	: m_pContext(pContext)
	, m_pSceneObject(pSceneObject)
{
}
#pragma endregion

// *----------------*
// *---- EMPTY -----*
// *----------------*
#pragma region Empty
tyr::ZenChanEmptyState::ZenChanEmptyState()
	: ZenChanState(nullptr, nullptr)
{}
#pragma endregion

// *----------------*
// *-- WANDERING ---*
// *----------------*
#pragma region Wandering
tyr::ZenChanWanderingState::ZenChanWanderingState(GameContext const* pContext, SceneObject* pSceneObject, float& moveSpeed, float& rayLength)
	: ZenChanState(pContext, pSceneObject)
	, m_MoveSpeed(moveSpeed)
	, m_RayLength(rayLength)
	, m_pCont(nullptr)
	, m_pBody(nullptr)
	, m_JumpCounter(1.5f)
	, m_NoDiSwitchTimer(0.2f)
	, m_CanSwitchDirection(false)
	, m_IsGoingLeft(false)
	, m_HasBeenHit(false)
	, m_OnColliderHitFunction(std::bind(&ZenChanWanderingState::OnColliderHit, this, std::placeholders::_1))
{
}

void tyr::ZenChanWanderingState::Enter()
{
	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_pBody = GET_COMPONENT<RigidBodyComp>();

	auto col = GET_COMPONENT<ColliderComp>();
	m_RayLength = col->GetColliderRect().width * .5f + 3.f;

	m_pBody->HasGravity(true);
	m_pBody->ResetForceAndVelocity();
	
	//https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
	//This is an override, each collider can only have one onColliderHitFunction
	col->AddOnColliderHitFunction(&m_OnColliderHitFunction);
}

void tyr::ZenChanWanderingState::Exit()
{
	if(m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto col = GET_COMPONENT<ColliderComp>();
		if (col)
			col->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
	}

}


tyr::ZenChanState* tyr::ZenChanWanderingState::Update()
{
	if (m_NoDiSwitchTimer.Update(TIME->deltaTime))
		m_CanSwitchDirection = true;

	if (m_JumpCounter.Update(TIME->deltaTime))
	{
		if (m_pCont->IsGrounded())
			m_pBody->AddForce(0, 374.f);
		m_JumpCounter.Reset();
	}

	if(m_HasBeenHit)
	{
		Exit();
		return new ZenChanInBubbleState(m_pContext, m_pSceneObject, m_pBody);
	}
	return nullptr;
}

tyr::ZenChanState* tyr::ZenChanWanderingState::FixedUpdate()
{
	const float elapsed = m_MoveSpeed * TIME->fixedDeltaTime;
	if (m_IsGoingLeft)
	{
		m_pCont->Move(-elapsed, 0);
	}
	else
		m_pCont->Move(elapsed, 0);


	RaycastHit out;
	if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(1, 0), m_RayLength, out))
	{
		if (out.other->GetTag() == Tag::Background && m_CanSwitchDirection)
		{
			m_CanSwitchDirection = false;
			m_NoDiSwitchTimer.Reset();
			m_IsGoingLeft = true;
			GET_TRANSFORM->SetScale(-1.f, 1.f);

		}
	}
	else if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(-1, 0), m_RayLength, out))
	{
		if (out.other->GetTag() == Tag::Background && m_CanSwitchDirection)
		{
			m_CanSwitchDirection = false;
			m_NoDiSwitchTimer.Reset();
			m_IsGoingLeft = false;
			GET_TRANSFORM->SetScale(1.f, 1.f);
		}
	}

	return nullptr;
}


#ifdef EDITOR_MODE
void tyr::ZenChanWanderingState::Debug()
{
	auto pos = GET_TRANSFORM->GetPosition();

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(1, 0) * m_RayLength)), static_cast<SDXL::SDXLVec4>(ColorCyan));

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(-1, 0) * m_RayLength)), static_cast<SDXL::SDXLVec4>(ColorCyan));
}
#endif


void tyr::ZenChanWanderingState::OnColliderHit(RaycastHit hit)
{
	if (hit.other->GetTag() == Tag::Player)
	{
		hit.other->GetComponent<PlayerHealthComp>()->LoseHealth();
	}

	if(hit.other->GetTag() == Tag::Bubble)
	{
		m_HasBeenHit = true;
		hit.other->Destroy();
	}
}
#pragma endregion

// *----------------*
// *--- IN BUBBLE---*
// *----------------*
#pragma region InBubble
tyr::ZenChanInBubbleState::ZenChanInBubbleState(GameContext const* pContext, SceneObject* pSceneObject, RigidBodyComp* pBody)
	: ZenChanState(pContext, pSceneObject)
	, m_pBody(pBody)
	, m_HasBeenHit(false)
	, m_OnColliderHitFunction(std::bind(&ZenChanInBubbleState::OnColliderHit, this, std::placeholders::_1))
{
}

void tyr::ZenChanInBubbleState::Enter()
{
	GET_COMPONENT<AnimatorComp>()->SetBool("IsHit", true);
	m_pBody->HasGravity(false);
	m_pBody->ResetForceAndVelocity();

	GET_COMPONENT<ColliderComp>()->AddOnColliderHitFunction(&m_OnColliderHitFunction);
	
}

void tyr::ZenChanInBubbleState::Exit()
{
	m_pBody->ResetForceAndVelocity();
	if (m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto col = GET_COMPONENT<ColliderComp>();
		if (col)
			col->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
	}
}

tyr::ZenChanState* tyr::ZenChanInBubbleState::Update()
{
	if(m_HasBeenHit)
	{
		Exit();
		return new ZenChanPoppedState(m_pContext, m_pSceneObject);
	}
	return nullptr;
}
tyr::ZenChanState* tyr::ZenChanInBubbleState::FixedUpdate()
{
	float pos = m_pSceneObject->GetTransform()->GetPositionRaw().y;
	if (pos < 540.f)
		m_pBody->AddForce(0.f, 1.f);

	
	return nullptr;
}

void tyr::ZenChanInBubbleState::OnColliderHit(RaycastHit hit)
{
	if(hit.other->GetTag() == Tag::Player)
	{
		m_HasBeenHit =true;
	}
}
#pragma endregion

// *----------------*
// *---- POPPED ----*
// *----------------*
#pragma region Popped
tyr::ZenChanPoppedState::ZenChanPoppedState(GameContext const* pContext, SceneObject* pSceneObject)
	: ZenChanState(pContext, pSceneObject)
	, m_pAni(nullptr)
{
}

void tyr::ZenChanPoppedState::Enter()
{
	m_pAni = GET_COMPONENT<AnimatorComp>();
	m_pAni->SetBool("IsPopped", true);

	REMOVE_COMPONENT(RigidBodyComp);
	REMOVE_COMPONENT(CharacterControllerComp);
	REMOVE_COMPONENT(ColliderComp);
	
}

void tyr::ZenChanPoppedState::Exit()
{
	m_pSceneObject->Destroy();
}

tyr::ZenChanState* tyr::ZenChanPoppedState::Update()
{
	if (m_pAni->IsAtEnd())
	{
		Exit();
		return new ZenChanEmptyState();
	}
	

	return nullptr;
}


#pragma endregion 
