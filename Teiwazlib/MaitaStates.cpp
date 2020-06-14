#include "tyrpch.h"
#include "MaitaStates.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Physics.h"
#include "Time.h"
#include "SceneManager.h"

#include "FoodPrefab.h"
#include "RockPrefab.h"
// *----------------*
// *----- BASE -----*
// *----------------*
#pragma region Base
tyr::MaitaState::MaitaState(GameContext const* pContext, SceneObject* pSceneObject)
	: m_pContext(pContext)
	, m_pSceneObject(pSceneObject)
{
}
#pragma endregion

// *----------------*
// *---- EMPTY -----*
// *----------------*
#pragma region Empty
tyr::MaitaEmptyState::MaitaEmptyState()
	: MaitaState(nullptr, nullptr)
{}
#pragma endregion

// *----------------*
// *-- WANDERING ---*
// *----------------*
#pragma region Wandering
tyr::MaitaWanderingState::MaitaWanderingState(GameContext const* pContext, SceneObject* pSceneObject, float& moveSpeed, float& rayLength, float& playerDetectionRange)
	: MaitaState(pContext, pSceneObject)
	, m_MoveSpeed(moveSpeed)
	, m_RayLength(rayLength)
	, m_PlayerDetectionRange(playerDetectionRange)
	, m_pCont(nullptr)
	, m_pBody(nullptr)
	, m_JumpCounter(2.5f)
	, m_NoDiSwitchTimer(0.2f)
	, m_CanSwitchDirection(false)
	, m_IsGoingLeft(false)
	, m_HasBeenHit(false)
	, m_ThrowRockElapser(0.5f)
	, m_CanThrowRock(false)
	, m_OnColliderHitFunction(std::bind(&MaitaWanderingState::OnColliderHit, this, std::placeholders::_1))
{
}

void tyr::MaitaWanderingState::Enter()
{
	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_pBody = GET_COMPONENT<RigidBodyComp>();

	auto col = GET_COMPONENT<ColliderComp>();
	m_RayLength = col->GetColliderRect().width * .5f + 3.f;

	m_pBody->HasGravity(true);
	m_pBody->ResetForceAndVelocity();

	col->AddOnColliderHitFunction(&m_OnColliderHitFunction);
}

void tyr::MaitaWanderingState::Exit()
{
	if (m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto col = GET_COMPONENT<ColliderComp>();
		if (col)
			col->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
	}

}


tyr::MaitaState* tyr::MaitaWanderingState::Update()
{
	if (m_NoDiSwitchTimer.Update(TIME->deltaTime))
		m_CanSwitchDirection = true;

	if (m_JumpCounter.Update(TIME->deltaTime))
	{
		if (m_pCont->IsGrounded())
			m_pBody->AddForce(0, 374.f);
		m_JumpCounter.Reset();
	}

	if (m_HasBeenHit)
	{
		Exit();
		return new MaitaInBubbleState(m_pContext, m_pSceneObject, m_pBody);
	}
	return nullptr;
}

tyr::MaitaState* tyr::MaitaWanderingState::FixedUpdate()
{
	const float elapsed = m_MoveSpeed * TIME->fixedDeltaTime;
	if (m_IsGoingLeft)
	{
		m_pCont->Move(-elapsed, 0);
	}
	else
		m_pCont->Move(elapsed, 0);

	UpdateWallHit();
	UpdateThrowRock();

	return nullptr;
}


#ifdef EDITOR_MODE
void tyr::MaitaWanderingState::Debug()
{
	auto pos = GET_TRANSFORM->GetPosition();

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(1, 0) * m_RayLength)), static_cast<SDXL::SDXLVec4>(ColorCyan));

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(-1, 0) * m_RayLength)), static_cast<SDXL::SDXLVec4>(ColorCyan));
	
	if(m_IsGoingLeft)
	{
		SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
			static_cast<SDXL::SDXLVec2>(pos + (Vector2(-1, 0) * m_PlayerDetectionRange)), static_cast<SDXL::SDXLVec4>(ColorYellow));
	}
	else
	{
		SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
			static_cast<SDXL::SDXLVec2>(pos + (Vector2(1, 0) * m_PlayerDetectionRange)), static_cast<SDXL::SDXLVec4>(ColorYellow));
	}
}
#endif


void tyr::MaitaWanderingState::UpdateWallHit()
{
	RaycastHit out;
	if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(1, 0), m_RayLength, out, false))
	{
		if (out.other->GetTag() == Tag::Background && m_CanSwitchDirection)
		{
			m_CanSwitchDirection = false;
			m_NoDiSwitchTimer.Reset();
			m_IsGoingLeft = true;
			GET_TRANSFORM->SetScale(-1.f, 1.f);

		}
	}
	else if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(-1, 0), m_RayLength, out, false))
	{
		if (out.other->GetTag() == Tag::Background && m_CanSwitchDirection)
		{
			m_CanSwitchDirection = false;
			m_NoDiSwitchTimer.Reset();
			m_IsGoingLeft = false;
			GET_TRANSFORM->SetScale(1.f, 1.f);
		}
	}
}

void tyr::MaitaWanderingState::UpdateThrowRock()
{

	if (m_ThrowRockElapser.Update(TIME->fixedDeltaTime))
		m_CanThrowRock = true;

	RaycastHit out;
	if(RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), m_IsGoingLeft ? Vector2(-1,0) : Vector2(1, 0), m_PlayerDetectionRange, out, false))
	{
		if(out.other->GetTag() == Tag::Player && m_CanThrowRock)
		{
			m_CanThrowRock = false;
			m_ThrowRockElapser.Reset();

			auto pos = GET_TRANSFORM->GetPositionRaw();
			if (m_IsGoingLeft)
				pos.x -= 20.f;
			else
				pos.x += 20.f;
			
			RockPrefab::Generate(m_pContext->pSceneManager->GetCurrentScene(), pos, m_IsGoingLeft);
			
			SDXL_ImGui_ConsoleLog("hit player");
		}
	}


	
}

void tyr::MaitaWanderingState::OnColliderHit(RaycastHit hit)
{
	if (hit.other->GetTag() == Tag::Player)
	{
		hit.other->GetComponent<PlayerHealthComp>()->LoseHealth();
	}

	if (hit.other->GetTag() == Tag::Bubble)
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
tyr::MaitaInBubbleState::MaitaInBubbleState(GameContext const* pContext, SceneObject* pSceneObject, RigidBodyComp* pBody)
	: MaitaState(pContext, pSceneObject)
	, m_pBody(pBody)
	, m_HasBeenHit(false)
	, m_OnColliderHitFunction(std::bind(&MaitaInBubbleState::OnColliderHit, this, std::placeholders::_1))
{
}

void tyr::MaitaInBubbleState::Enter()
{
	GET_COMPONENT<AnimatorComp>()->SetBool("IsHit", true);
	m_pBody->HasGravity(false);
	m_pBody->ResetForceAndVelocity();

	GET_COMPONENT<ColliderComp>()->AddOnColliderHitFunction(&m_OnColliderHitFunction);

}

void tyr::MaitaInBubbleState::Exit()
{
	m_pBody->ResetForceAndVelocity();
	if (m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto col = GET_COMPONENT<ColliderComp>();
		if (col)
			col->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
	}
}

tyr::MaitaState* tyr::MaitaInBubbleState::Update()
{
	if (m_HasBeenHit)
	{
		Exit();
		return new MaitaPoppedState(m_pContext, m_pSceneObject);
	}
	return nullptr;
}
tyr::MaitaState* tyr::MaitaInBubbleState::FixedUpdate()
{
	float pos = m_pSceneObject->GetTransform()->GetPositionRaw().y;
	if (pos < 540.f)
		m_pBody->AddForce(0.f, 1.f);


	return nullptr;
}

void tyr::MaitaInBubbleState::OnColliderHit(RaycastHit hit)
{
	if (hit.other->GetTag() == Tag::Player)
	{
		m_HasBeenHit = true;
	}
}
#pragma endregion

// *----------------*
// *---- POPPED ----*
// *----------------*
#pragma region Popped
tyr::MaitaPoppedState::MaitaPoppedState(GameContext const* pContext, SceneObject* pSceneObject)
	: MaitaState(pContext, pSceneObject)
	, m_pAni(nullptr)
{
}

void tyr::MaitaPoppedState::Enter()
{
	m_pAni = GET_COMPONENT<AnimatorComp>();
	m_pAni->SetBool("IsPopped", true);

	REMOVE_COMPONENT(RigidBodyComp);
	REMOVE_COMPONENT(CharacterControllerComp);
	REMOVE_COMPONENT(ColliderComp);

}

void tyr::MaitaPoppedState::Exit()
{
	FoodPrefab::Generate(m_pContext->pSceneManager->GetCurrentScene(), GET_TRANSFORM->GetPositionRaw(), FoodType::Fries);

	m_pSceneObject->Destroy();
}

tyr::MaitaState* tyr::MaitaPoppedState::Update()
{
	if (m_pAni->IsAtEnd())
	{
		Exit();
		return new MaitaEmptyState();
	}


	return nullptr;
}


#pragma endregion 
