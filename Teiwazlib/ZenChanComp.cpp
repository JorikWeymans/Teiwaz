#include "tyrpch.h"
#include "ZenChanComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Time.h"
#include "Physics.h"
#include "BinaryWriter.h"
tyr::ZenChanComp::ZenChanComp()
	: BaseComponent(ComponentType::ZenChan, "ZenChan Component")
	, m_IsGoingLeft(false)
{
}

tyr::ZenChanComp::~ZenChanComp()
{
}

void tyr::ZenChanComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));

	m_pCont = GET_COMPONENT<CharacterControllerComp>();
	m_RayLength = GET_COMPONENT<ColliderComp>()->GetColliderRect().width * .5f + 3.f;
	
}

void tyr::ZenChanComp::Update()
{
}

void tyr::ZenChanComp::FixedUpdate()
{
#ifdef EDITOR_MODE
	m_RayLength = GET_COMPONENT<ColliderComp>()->GetColliderRect().width * .5f + 3.f; //in editor mode collider width can change, update this
#endif
	
	const float elapsed = 150 * TIME->fixedDeltaTime;
	if (m_IsGoingLeft)
	{
		m_pCont->Move(-elapsed, 0);	
	}
	else
		m_pCont->Move(elapsed, 0);

	RaycastHit out;
	if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(1, 0), m_RayLength, out))
	{
		if(out.other->GetTag() == Tag::Background)
		{
			SDXL_ImGui_ConsoleLog("Hit Background");
		}
	}
	
}

#ifdef EDITOR_MODE
void tyr::ZenChanComp::Debug()
{
	auto pos = m_pSceneObject->GetTransform()->GetPosition();
	
	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos ),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(1,0) * m_RayLength )), static_cast<SDXL::SDXLVec4>(ColorCyan));

}

void tyr::ZenChanComp::InternalRenderEditor()
{
}

void tyr::ZenChanComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
#endif
