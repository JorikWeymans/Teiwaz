#include "tyrpch.h"
#include "CharacterControllerComp.h"
#include "SceneObject.h"
#include "TyrException.h"
#include "TyrComps.h"
#include "Vectors.h"
#include "TeiwazEngine.h"

tyr::CharacterControllerComp::CharacterControllerComp()
	: m_pTransform(nullptr)
	, m_pCollider(nullptr)
{
}

void tyr::CharacterControllerComp::Initialize()
{
	m_pCollider = m_pSceneObject->GetComponent<ColliderComp>();
	if (!m_pCollider) THROW_ERROR(L"CharacterController needs a collider to work!");
	m_pTransform = m_pSceneObject->GetTransform();
}

void tyr::CharacterControllerComp::Move(float x, float y)
{
	auto playerColl = m_pCollider->GetColliderRect();

	bool canMoveX = false;

	Rect* playSpace = GET_CONTEXT->pGameSpace;
	
	if( x < 0.f && (playerColl.pos.x + x) > playSpace->pos.x)
	{
		canMoveX = true;
	}
	else if( x > 0.f && (playerColl.pos.x + x) < playSpace->pos.x + playSpace->width - playerColl.width)
	{
		canMoveX = true;
	}

	if(y < 0  && playerColl.pos.y > playSpace->pos.y + playSpace->height)
	{
		m_pSceneObject->SetPositionY(playSpace->pos.y + playSpace->height - ENGINE_SPACING_TOP);
	}

	

	m_pSceneObject->Translate(canMoveX ? x: 0.f, y);
	
}
