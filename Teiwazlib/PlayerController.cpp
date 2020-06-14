#include "tyrpch.h"
#include "PlayerController.h"
#include "InputHandler.h"
#include "GameContext.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include "Time.h"
#include "BinaryWriter.h"


tyr::PlayerController::PlayerController(float m_JumpForce, int playerID)
	: tyr::BaseComponent(ComponentType::PlayerController, "Player Controller Component")
	, m_pCont(nullptr)
	, m_pBody(nullptr)
	, m_pAni(nullptr)
	, m_IsGoningLeft(false)
	, m_JumpForce(m_JumpForce)
	, m_OnHealthChangedFunction(std::bind(&PlayerController::OnHealthChanged, this, std::placeholders::_1))
	, m_PlayerID(playerID)
{
}

void tyr::PlayerController::Initialize()
{
	
	GET_CONTEXT->pInput->AddAction("P1Jump", tyr::ButtonState::Pressed, 'W');
	GET_CONTEXT->pInput->AddAction("P1MoveLeft", tyr::ButtonState::Down, 'A');
	GET_CONTEXT->pInput->AddAction("P1MoveRight", tyr::ButtonState::Down, 'D');
	GET_CONTEXT->pInput->AddAction("P1Shoot", tyr::ButtonState::Pressed, VK_SPACE);

	GET_CONTEXT->pInput->AddAction("P2Jump", tyr::ButtonState::Pressed, -1, ControllerButton::ButtonA);
	GET_CONTEXT->pInput->AddAction("P2MoveLeft", tyr::ButtonState::Down, -1, ControllerButton::ButtonLeft);
	GET_CONTEXT->pInput->AddAction("P2MoveRight", tyr::ButtonState::Down, -1, ControllerButton::ButtonRight);
	GET_CONTEXT->pInput->AddAction("P2Shoot", tyr::ButtonState::Pressed, -1, ControllerButton::ButtonB);

	m_pBody = GET_COMPONENT<RigidBodyComp>();
	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_pAni  = GET_COMPONENT<AnimatorComp>();

	INPUT->AddAction("AEating", ButtonState::Pressed, VK_SPACE);
	m_StartPos = GET_TRANSFORM->GetPositionRaw();
	
}

void tyr::PlayerController::PostInitialize()
{
	
	GET_COMPONENT<PlayerHealthComp>()->AddOnHealthChangedFunction(&m_OnHealthChangedFunction);
}

void tyr::PlayerController::Update()
{
	if(m_PlayerID == 1)
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P1Jump"))
		{
			if (m_pCont->IsGrounded())
				m_pBody->AddForce(0, m_JumpForce);
		}
	}

	else
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P2Jump"))
		{
			if (m_pCont->IsGrounded())
				m_pBody->AddForce(0, m_JumpForce);
		}
	}

}

void tyr::PlayerController::FixedUpdate()
{
	if (m_PlayerID == 1)
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P1MoveLeft")) MoveLeft();
		else if (GET_CONTEXT->pInput->IsActionTriggered("P1MoveRight")) MoveRight();
		else m_pAni->SetFloat("Speed", 0.f);
	}
	else
	{
		if (GET_CONTEXT->pInput->IsActionTriggered("P2MoveLeft")) MoveLeft();
		else if (GET_CONTEXT->pInput->IsActionTriggered("P2MoveRight")) MoveRight();
		else m_pAni->SetFloat("Speed", 0.f);
	}

}

void tyr::PlayerController::MoveLeft()
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

void tyr::PlayerController::MoveRight()
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
#ifdef EDITOR_MODE

void tyr::PlayerController::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_JumpForce);
	writer.Write(m_PlayerID);
}

void tyr::PlayerController::InternalRenderEditor()
{
	std::string name;

	//m_JumpForce
	SDXL_ImGui_Text("JumpForce: \t");
	SDXL_ImGui_SameLine();
	name = "##Player1ControllerComp" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_JumpForce, 1, 10, 10);


	SDXL_ImGui_Text("PL ID:     \t");
	SDXL_ImGui_SameLine();
	name = "##PlayerConterollerPlayerID" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragInt(name.c_str(), &m_PlayerID, 1, 1, 2);
	
}




#endif

void tyr::PlayerController::OnHealthChanged(int amountLeft)
{
	GET_TRANSFORM->SetPositionX(m_StartPos.x);
	GET_TRANSFORM->SetPositionY(m_StartPos.y);
	UNREFERENCED_PARAMETER(amountLeft);
}
