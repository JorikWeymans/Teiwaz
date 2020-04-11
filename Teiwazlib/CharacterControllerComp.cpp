#include "tyrpch.h"
#include "CharacterControllerComp.h"
#include "SceneObject.h"
#include "TyrException.h"
#include "TyrComps.h"
#include "Vectors.h"
#include "TeiwazEngine.h"
#include "Physics.h"
tyr::CharacterControllerComp::CharacterControllerComp()
	: m_pTransform(nullptr)
	, m_pCollider(nullptr)
	, m_RayCastOffset(0.f)
	, m_IsOnGround(false)
{
#ifdef USE_IM_GUI
	SDXL_ImGui_ConsoleLog("CharacterController added");
#endif
}

void tyr::CharacterControllerComp::Initialize()
{
	m_pCollider = m_pSceneObject->GetComponent<ColliderComp>();
	if (!m_pCollider) THROW_ERROR(L"CharacterController needs a collider to work!");
	m_pTransform = m_pSceneObject->GetTransform();

	m_RayCastOffset = m_pCollider->GetColliderRect().width / 2 - 5;
}

void tyr::CharacterControllerComp::FixedUpdate()
{
	RaycastHit out;
	
	if (GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, 0), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out) ||

		GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(-(m_RayCastOffset), 0), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out)
		)
	{
		m_pSceneObject->GetTransform()->SetPositionY(out.point.y - m_pCollider->GetColliderRect().height / 2, true);
		m_IsOnGround = true;
	}
	else
		m_IsOnGround = false;
}

void tyr::CharacterControllerComp::Move(float x, float y)
{
	auto playerColl = m_pCollider->GetColliderRect();

	bool canMoveX = false;

	Rect* playSpace = GET_CONTEXT->pGameSpace;
	
	if( x < 0.f && (playerColl.pos.x + x) > playSpace->pos.x)
	{

		RaycastHit out;
		if (GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(-1, 0), m_pCollider->GetColliderRect().width / 2, out) /*||
		
			GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(-1, 0), m_pCollider->GetColliderRect().width / 2, out)*/
			)
		{
			auto pos = m_pSceneObject->GetTransform()->GetPosition();
			
			m_pSceneObject->GetTransform()->SetPositionX(out.point.x + m_pCollider->GetColliderRect().width / 2, true);
		
		}
		else
			canMoveX = true;
	}
	else if( x > 0.f && (playerColl.pos.x + x) < playSpace->pos.x + playSpace->width - playerColl.width)
	{
		RaycastHit out;
		if (GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(1, 0), m_pCollider->GetColliderRect().width / 2, out) /*||

			GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(-1, 0), m_pCollider->GetColliderRect().width / 2, out)*/
			)
		{
			auto pos = m_pSceneObject->GetTransform()->GetPosition();

			m_pSceneObject->GetTransform()->SetPositionX(out.point.x - m_pCollider->GetColliderRect().width / 2, true);

		}
		else
			canMoveX = true;
	}

	bool canMoveY = true;
	if( y < 0  && 
		playerColl.pos.y >  playSpace->height)
	{
		m_pTransform->SetPositionY(playSpace->height - ENGINE_SPACING_TOP);
	}



	if (y < 0)
	{
		RaycastHit out;
		if (GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, y), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out) ||
			GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(-(m_RayCastOffset), y), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out)
			)
		{
			
			m_pSceneObject->GetTransform()->SetPositionY(out.point.y - m_pCollider->GetColliderRect().height / 2, true);
			m_IsOnGround = true;
		}
		canMoveY = !m_IsOnGround;
	}

	m_pSceneObject->Translate(canMoveX ? x: 0.f, canMoveY ? y : 0.f);
	
}
#ifdef USE_IM_GUI
void tyr::CharacterControllerComp::Debug()
{
	
	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, 0)),
							static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, 0) + ( Vector2(0,1) * (m_pCollider->GetColliderRect().width / 2))), static_cast<SDXL::SDXLVec4>(ColorWhite));

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(-m_RayCastOffset, 0.f)),
		static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(-m_RayCastOffset, 0.f) + (Vector2(0, 1) * (m_pCollider->GetColliderRect().width / 2))), static_cast<SDXL::SDXLVec4>(ColorWhite));




	
	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(0, - m_RayCastOffset)),
		static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset) + (Vector2(-1, 0) * (m_pCollider->GetColliderRect().width / 2))), static_cast<SDXL::SDXLVec4>(ColorWhite));


	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset)),
		static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset) + (Vector2(1, 0) * (m_pCollider->GetColliderRect().width / 2))), static_cast<SDXL::SDXLVec4>(ColorWhite));
}

void tyr::CharacterControllerComp::RenderEditor()
{
	SDXL_ImGui_Begin("Inspector");

	std::string name = "CharacterController Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//Raycast
		SDXL_ImGui_Text("Offset:  \t");
		SDXL_ImGui_SameLine();
		name = "##Offset" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_RayCastOffset, 1, 0, 48);
		//
		//SDXL_ImGui_Text("Height: \t");
		//SDXL_ImGui_SameLine();
		//name = "##ColW" + std::to_string(m_UniqueId);
		//SDXL_ImGui_DragFloat(name.c_str(), &m_Height, 1, 0, GET_CONTEXT->pGameSpace->height);


		SDXL_ImGui_PopItemWidth();
	}
	SDXL_ImGui_End();
}
#endif