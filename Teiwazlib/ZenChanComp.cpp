#include "tyrpch.h"
#include "ZenChanComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Time.h"
#include "Physics.h"
#include "BinaryWriter.h"
tyr::ZenChanComp::ZenChanComp(float movespeed)
	: BaseComponent(ComponentType::ZenChan, "ZenChan Component")
	, m_pCont(nullptr)
	, m_NoDiSwitchTimer(0.2f)
	, m_CanSwitchDirection(false)
	, m_IsGoingLeft(false)
	, m_RayLength(0.f)
	, m_MoveSpeed(movespeed)
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

	auto col = GET_COMPONENT<ColliderComp>();

	//https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
	//This is an override, each collider can only have one onColliderHitFunction
	col->onColliderHitFunction = std::bind(&ZenChanComp::OnColliderHit, this, std::placeholders::_1);
	
	
}


void tyr::ZenChanComp::Update()
{
	if (m_NoDiSwitchTimer.Update(TIME->deltaTime))
		m_CanSwitchDirection = true;
	
}

void tyr::ZenChanComp::FixedUpdate()
{
#ifdef EDITOR_MODE
	m_RayLength = GET_COMPONENT<ColliderComp>()->GetColliderRect().width * .5f + 3.f; //in editor mode collider width can change, update this
#endif
	
	const float elapsed = m_MoveSpeed * TIME->fixedDeltaTime;
	if (m_IsGoingLeft)
	{
		m_pCont->Move(-elapsed, 0);
	}
	else
		m_pCont->Move(elapsed, 0);

	
	RaycastHit out;
	if (RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(1, 0), m_RayLength, out))
	{
		if(out.other->GetTag() == Tag::Background && m_CanSwitchDirection)
		{
			m_CanSwitchDirection = false;
			m_NoDiSwitchTimer.Reset();
			m_IsGoingLeft = true;
			GET_TRANSFORM->SetScale(-1.f, 1.f);
			
		}
	}
	else if(RAYCAST(m_pSceneObject->GetTransform()->GetPosition(), Vector2(-1, 0), m_RayLength, out))
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

#ifdef EDITOR_MODE
void tyr::ZenChanComp::OnColliderHit(RaycastHit hit)
{
	//TODO: Implement this, to many bugs to fix easly
	UNREFERENCED_PARAMETER(hit);
	
	//if(hit.other->GetTag() == Tag::Background)
	//{
	//	if(m_pSceneObject->GetTransform()->GetPosition().x < hit.other->GetTransform()->GetPosition().x && 
	//		!m_IsGoingLeft && 
	//		m_CanSwitchDirection)
	//	{
	//		m_IsGoingLeft = true;
	//		m_CanSwitchDirection = false;
	//		m_NoDiSwitchTimer.Reset();
	//	}
	//
	//	if (m_pSceneObject->GetTransform()->GetPosition().x > hit.other->GetTransform()->GetPosition().x &&
	//		m_IsGoingLeft && 
	//		m_CanSwitchDirection)
	//	{
	//		m_IsGoingLeft = false;
	//		m_CanSwitchDirection = false;
	//		m_NoDiSwitchTimer.Reset();
	//	}
	//}
}

void tyr::ZenChanComp::Debug()
{
	auto pos = m_pSceneObject->GetTransform()->GetPosition();
	
	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos ),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(1,0) * m_RayLength )), static_cast<SDXL::SDXLVec4>(ColorCyan));

	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(pos),
		static_cast<SDXL::SDXLVec2>(pos + (Vector2(-1, 0) * m_RayLength)), static_cast<SDXL::SDXLVec4>(ColorCyan));

}

void tyr::ZenChanComp::InternalRenderEditor()
{
	std::string name;

	name = "##ZenChanCompSpeed"  + std::to_string(m_UniqueId);
	SDXL_ImGui_Text("Speed    :\t");
	SDXL_ImGui_SameLine();
	SDXL_ImGui_DragFloat(name.c_str(), &m_MoveSpeed);
	
}

void tyr::ZenChanComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_MoveSpeed);
}
#endif
