#include "tyrpch.h"
#include "RockComp.h"
#include "BinaryWriter.h"
#include "Physics.h"
#include "SceneObject.h"
#include "TyrComps.h"
tyr::RockComp::RockComp()
	: BaseComponent(ComponentType::Rock, "Auto Destroy Component")
	, m_OnColliderHitFunction(std::bind(&RockComp::OnColliderHit, this, std::placeholders::_1))
{
}

tyr::RockComp::~RockComp()
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

void tyr::RockComp::Initialize()
{
	GET_COMPONENT<ColliderComp>()->AddOnColliderHitFunction(&m_OnColliderHitFunction);

}

void tyr::RockComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::RockComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}

void tyr::RockComp::InternalRenderEditor()
{
}

void tyr::RockComp::OnColliderHit(RaycastHit hit)
{
	if(hit.other->GetTag() == Tag::Player)
	{
		hit.other->GetComponent<PlayerHealthComp>()->LoseHealth();
		m_pSceneObject->Destroy();
	}
}
#endif
