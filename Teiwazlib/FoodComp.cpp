#include "tyrpch.h"
#include "FoodComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "Physics.h"
#include "GameState.h"
tyr::FoodComp::FoodComp(FoodType type)
	: BaseComponent(ComponentType::Food, "Food Component")
	, m_FoodType(type)
	, m_OnColliderHitFunction(std::bind(&FoodComp::OnColliderHit, this, std::placeholders::_1))
{
}

tyr::FoodComp::~FoodComp()
{
	if (m_pSceneObject && !m_pSceneObject->IsDestroyed())
	{
		auto pColl = GET_COMPONENT<ColliderComp>();
		if (pColl)
		{
			pColl->RemoveOnColliderHitFunction(&m_OnColliderHitFunction);
		}
	}
}

void tyr::FoodComp::Initialize()
{
	GET_COMPONENT<ColliderComp>()->AddOnColliderHitFunction(&m_OnColliderHitFunction);

}

void tyr::FoodComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::FoodComp::Debug()
{
}

void tyr::FoodComp::InternalRenderEditor()
{
}

void tyr::FoodComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_FoodType);
	UNREFERENCED_PARAMETER(writer);
}

void tyr::FoodComp::OnColliderHit(RaycastHit hit)
{
	if (hit.other->GetTag() == Tag::Player)
	{
		switch (m_FoodType)
		{
			case FoodType::Melon:
				GET_CONTEXT->pGameState->AddToScore(100);
				break;
			case FoodType::Fries:
				_FALLTHROUGH
			default:
				GET_CONTEXT->pGameState->AddToScore(200);
		; }
		
		m_pSceneObject->Destroy();
		
	}
}
#endif
