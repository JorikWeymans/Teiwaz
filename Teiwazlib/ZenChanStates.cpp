#include "tyrpch.h"
#include "ZenChanStates.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Physics.h"
#include "Time.h"

// *----------------*
// *----- BASE -----*
// *----------------*
tyr::ZenChanState::ZenChanState(GameContext const* pContext, SceneObject* pSceneObject)
	: m_pContext(pContext)
	, m_pSceneObject(pSceneObject)
{
}

// *----------------*
// *-- WANDERING ---*
// *----------------*
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
{
}

void tyr::ZenChanWanderingState::Enter()
{
	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_pBody = GET_COMPONENT<RigidBodyComp>();

	auto col = GET_COMPONENT<ColliderComp>();
	m_RayLength = col->GetColliderRect().width * .5f + 3.f;

	//https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
	//This is an override, each collider can only have one onColliderHitFunction
	col->onColliderHitFunction = std::bind(&ZenChanWanderingState::OnColliderHit, this, std::placeholders::_1);
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
}



tyr::ZenChanBrainDeadState::ZenChanBrainDeadState(GameContext const* pContext, SceneObject* pSceneObject)
	: ZenChanState(pContext, pSceneObject)
{
}

tyr::ZenChanState* tyr::ZenChanBrainDeadState::Update()
{
	return nullptr;
}
