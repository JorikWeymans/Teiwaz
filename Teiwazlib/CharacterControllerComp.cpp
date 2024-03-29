#include "tyrpch.h"
#include "CharacterControllerComp.h"
#include "SceneObject.h"
#include "TyrException.h"
#include "TyrComps.h"
#include "Vectors.h"
#include "TeiwazEngine.h"
#include "Physics.h"
#include "BinaryWriter.h"
#include "time.h"


tyr::CharacterControllerComp::CharacterControllerComp(float rayCastOffset)
	: tyr::BaseComponent(ComponentType::CharacterController, "CharacterController Component")
	, m_pTransform(nullptr)
	, m_pCollider(nullptr)
	, m_Force(Vector2(0.f,0.f))
	, m_RayCastOffset(rayCastOffset)
	, m_IsOnGround(false)
{
}

void tyr::CharacterControllerComp::Initialize()
{
	m_pCollider = m_pSceneObject->GetComponent<ColliderComp>();
	if (!m_pCollider) THROW_ERROR(L"CharacterController needs a collider to work!");
	m_pTransform = m_pSceneObject->GetTransform();

	//m_RayCastOffset = m_pCollider->GetColliderRect().width / 2 - 5;
}

void tyr::CharacterControllerComp::FixedUpdate()
{
	//UpdateForce();
	DoGroundCheck();

}
void tyr::CharacterControllerComp::DoGroundCheck() noexcept
{
	RaycastHit out;

	if (RAYCAST(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, 0), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out, true) ||

		RAYCAST(m_pTransform->GetPosition() - Vector2(-(m_RayCastOffset), 0), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out, true)
		)
	{
		//m_pSceneObject->GetTransform()->SetPositionY(out.point.y - m_pCollider->GetColliderRect().height / 2, true);
		m_IsOnGround = true;
	}
	else
		m_IsOnGround = false;

}

bool tyr::CharacterControllerComp::CalculateFalling(float y, const Rect& playerColl, const Rect* pPlaySpace) noexcept
{
	bool canMove = true;
	//When falling
	if (y < 0 )
	{
		//Screenwrapping
		if (playerColl.GetPos().y > pPlaySpace->GetHeight())
			m_pTransform->SetPositionY(pPlaySpace->GetHeight() - ENGINE_SPACING_TOP);

		//check for collider, also clip with the collider to prevent getting stuck in ground
		RaycastHit out;
		if (RAYCAST(m_pTransform->GetPosition() - Vector2(m_RayCastOffset, y), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out, true) ||
			RAYCAST(m_pTransform->GetPosition() - Vector2(-(m_RayCastOffset), y), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2, out, true)
			)
		{

			m_pSceneObject->GetTransform()->SetPositionY(out.point.y - m_pCollider->GetColliderRect().height / 2, true);
			m_IsOnGround = true;
		}
		canMove = !m_IsOnGround;
	}

	return canMove;
}

void tyr::CharacterControllerComp::Move(const Vector2& vec) noexcept
{
	Move(vec.x, vec.y);
}

void tyr::CharacterControllerComp::Move(float x, float y)noexcept
{
	auto playerColl = m_pCollider->GetColliderRect();

	bool canMoveX = false;

	Rect* playSpace = GET_CONTEXT->pGameSpace;

	const bool canMoveY = CalculateFalling(y, playerColl, playSpace);
	
	if( x < 0.f && (playerColl.pos.x + x) > playSpace->pos.x)
	{

		RaycastHit out;
		if (RAYCAST(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(-1, 0), m_pCollider->GetColliderRect().width / 2, out, true))
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
		if (RAYCAST(m_pTransform->GetPosition() - Vector2(0, -m_RayCastOffset), Vector2(1, 0), m_pCollider->GetColliderRect().width / 2, out, true))
		{
			auto pos = m_pSceneObject->GetTransform()->GetPosition();

			m_pSceneObject->GetTransform()->SetPositionX(out.point.x - m_pCollider->GetColliderRect().width / 2, true);

		}
		else
			canMoveX = true;
	}



	
	m_pSceneObject->Translate(canMoveX ? x: 0.f, canMoveY ? y : 0.f);
	
}

#ifdef EDITOR_MODE
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

void tyr::CharacterControllerComp::InternalRenderEditor()
{
	std::string name;
	//Raycast
	SDXL_ImGui_Text("Offset:  \t");
	SDXL_ImGui_SameLine();
	name = "##CharControllerOffset" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_RayCastOffset, 1, 0, 48);

}

void tyr::CharacterControllerComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_RayCastOffset);
	
}

#endif
