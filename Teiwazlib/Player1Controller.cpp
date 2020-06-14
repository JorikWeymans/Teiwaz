#include "tyrpch.h"
#include "Player1Controller.h"
#include "InputHandler.h"
#include "GameContext.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include "Time.h"
#include "BinaryWriter.h"


tyr::Player1Controller::Player1Controller(float m_JumpForce)
	: tyr::BaseComponent(ComponentType::Player1Controller, "Player1 Controller Component")
	, m_pCont(nullptr)
	, m_pBody(nullptr)
	, m_pAni(nullptr)
	, m_IsGoningLeft(false)
	, m_JumpForce(m_JumpForce)
	, m_OnHealthChangedFunction(std::bind(&Player1Controller::OnHealthChanged, this, std::placeholders::_1))
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

	INPUT->AddAction("AEating", ButtonState::Pressed, VK_SPACE);
	m_StartPos = GET_TRANSFORM->GetPositionRaw();
	
}

void tyr::Player1Controller::PostInitialize()
{
	
	GET_COMPONENT<PlayerHealthComp>()->AddOnHealthChangedFunction(&m_OnHealthChangedFunction);
}

void tyr::Player1Controller::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("Jump"))
	{
		if (m_pCont->IsGrounded())
			m_pBody->AddForce(0, m_JumpForce);
	}

	static bool isEating = false;


	if (INPUT->IsActionTriggered("AEating"))
	{
		isEating = true;
		m_pAni->SetBool("IsEating", true);
	}

	if (isEating == true)
	{


		if (m_pAni->IsAtEnd())
		{
			isEating = false;
			m_pAni->SetBool("IsEating", false);
		}
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
	writer.Write(m_JumpForce);
	
}

void tyr::Player1Controller::InternalRenderEditor()
{
	std::string name;

	//m_JumpForce
	SDXL_ImGui_Text("JumpForce: \t");
	SDXL_ImGui_SameLine();
	name = "##Player1ControllerComp" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_JumpForce, 1, 10, 10);
}

void tyr::Player1Controller::OnHealthChanged(int amountLeft)
{
	GET_TRANSFORM->SetPositionX(m_StartPos.x);
	GET_TRANSFORM->SetPositionY(m_StartPos.y);
	UNREFERENCED_PARAMETER(amountLeft);
}

#endif

