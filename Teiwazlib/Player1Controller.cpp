#include "tyrpch.h"
#include "Player1Controller.h"
#include "InputHandler.h"
#include "GameContext.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include "Time.h"
#include "BinaryWriter.h"


tyr::Player1Controller::Player1Controller()
	: tyr::BaseComponent(ComponentType::Player1Controller)
	, m_pCont(nullptr)
	, m_pBody(nullptr)
	, m_pAni(nullptr)
	, m_IsGoningLeft(false)
{
}

void tyr::Player1Controller::Initialize()
{
	
	GET_CONTEXT->pInput->AddAction("Jump", tyr::ButtonState::Pressed, 'W');
	GET_CONTEXT->pInput->AddAction("MoveLeft", tyr::ButtonState::Down, 'A');
	GET_CONTEXT->pInput->AddAction("MoveRight", tyr::ButtonState::Down, 'D');

	m_pBody = GET_COMPONENT<RigidBodyComp>();
	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_pAni  = GET_COMPONENT<AnimatorComp>();
	
}

void tyr::Player1Controller::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("Jump"))
	{
		if (m_pCont->IsGrounded())
			m_pBody->AddForce(0, 300.f);
	}
}

void tyr::Player1Controller::FixedUpdate()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("MoveLeft"))
	{
		const float elapsed = GET_CONTEXT->pTime->fixedDeltaTime;


		
		m_pCont->Move(-150 * elapsed, 0);
		m_pAni->SetFloat("Speed", 150 * elapsed);
		if (!m_IsGoningLeft)
		{
			m_IsGoningLeft = true;
			m_pSceneObject->GetTransform()->Scale(-1, 1);
		}

	}
	else if (GET_CONTEXT->pInput->IsActionTriggered("MoveRight"))

	{
		//m_Ani->SetAnimation("Walking");
		const float elapsed = GET_CONTEXT->pTime->fixedDeltaTime;

		m_pCont->Move(150 * elapsed, 0);
		m_pAni->SetFloat("Speed", 150 * elapsed);
		
		if (m_IsGoningLeft)
		{
			m_IsGoningLeft = false;
			const auto scale = abs(m_pSceneObject->GetTransform()->GetScale());
			m_pSceneObject->GetTransform()->SetScale(scale.x, scale.y);

		}

	}
	else
	{
		m_pAni->SetFloat("Speed", 0.f);
	}
}
#ifdef EDITOR_MODE

void tyr::Player1Controller::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	
}

#endif

