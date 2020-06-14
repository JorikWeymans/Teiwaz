#include "tyrpch.h"
#include "ZenChanComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Time.h"
#include "Physics.h"
#include "BinaryWriter.h"
#include "ZenChanStates.h"
tyr::ZenChanComp::ZenChanComp(float movespeed)
	: BaseComponent(ComponentType::ZenChan, "ZenChan Component")
	, m_pState(nullptr)
	, m_RayLength(0.f)
	, m_MoveSpeed(movespeed)
{

}

tyr::ZenChanComp::~ZenChanComp()
{
	m_pState->Exit();
	SAFE_DELETE(m_pState);
}
void tyr::ZenChanComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));
	//

	m_pState = new ZenChanWanderingState(GET_CONTEXT, m_pSceneObject, m_MoveSpeed, m_RayLength);

	m_pState->Enter();
	
	
}


void tyr::ZenChanComp::Update()
{
	ZenChanState* state = m_pState->Update();
	if(state)
	{
		SAFE_DELETE(m_pState);
		m_pState = state;
	}
}

void tyr::ZenChanComp::FixedUpdate()
{
#ifdef EDITOR_MODE
	m_RayLength = GET_COMPONENT<ColliderComp>()->GetColliderRect().width * .5f + 3.f; //in editor mode collider width can change, update this
#endif

	ZenChanState* state =  m_pState->FixedUpdate();
	if (state)
	{
		SAFE_DELETE(m_pState);
		m_pState = state;
	}
}


#ifdef EDITOR_MODE

void tyr::ZenChanComp::Debug()
{
	auto pos = GET_TRANSFORM->GetPosition();
	
	m_pState->Debug();

}

void tyr::ZenChanComp::InternalRenderEditor()
{
	std::string name;

	name = "##ZenChanCompSpeed"  + std::to_string(m_UniqueId);
	SDXL_ImGui_Text("Speed:    \t");
	SDXL_ImGui_SameLine();
	if(SDXL_ImGui_DragFloat(name.c_str(), &m_MoveSpeed))
	{
		GET_COMPONENT<AnimatorComp>()->SetBool("IsHit", true);
	}




	
	
}

void tyr::ZenChanComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_MoveSpeed);
}
#endif
