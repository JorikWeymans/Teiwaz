#include "tyrpch.h"
#include "MaitaComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "MaitaStates.h"
tyr::MaitaComp::MaitaComp(float moveSpeed, float playerDetectionRange)
	:BaseComponent(ComponentType::Maita, "Maita Component")
	, m_pState(nullptr)
	, m_MoveSpeed(moveSpeed)
	, m_RayLength(0)
	, m_PlayerDetectionRange(playerDetectionRange)
{
}

tyr::MaitaComp::~MaitaComp()
{
	m_pState->Exit();
	SAFE_DELETE(m_pState);
}

void tyr::MaitaComp::Initialize()
{
	m_pState = new MaitaWanderingState(GET_CONTEXT, m_pSceneObject, m_MoveSpeed, m_RayLength, m_PlayerDetectionRange);

	m_pState->Enter();
	
}

void tyr::MaitaComp::Update()
{
	auto* pState = m_pState->Update();
	if (pState)
	{
		SAFE_DELETE(m_pState);
		m_pState = pState;

		m_pState->Enter();
	}
}
void tyr::MaitaComp::FixedUpdate()
{
#ifdef EDITOR_MODE
	auto comp = GET_COMPONENT<ColliderComp>();
	if (comp)
		m_RayLength = comp->GetColliderRect().width * .5f + 3.f; //in editor mode collider width can change, update this

#endif


	auto* pState = m_pState->FixedUpdate();
	if (pState)
	{
		SAFE_DELETE(m_pState);
		m_pState = pState;
		m_pState->Enter();
	}
}
#ifdef EDITOR_MODE
void tyr::MaitaComp::Debug()
{
	m_pState->Debug();
}

void tyr::MaitaComp::InternalRenderEditor()
{
	std::string name;

	name = "##MaitaCompSpeed" + std::to_string(m_UniqueId);
	SDXL_ImGui_Text("Speed:    \t");
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_DragFloat(name.c_str(), &m_MoveSpeed))
	{
		GET_COMPONENT<AnimatorComp>()->SetBool("IsHit", true);
	}

	
	name = "##MaitaCompPlayerDetectionRange" + std::to_string(m_UniqueId);
	SDXL_ImGui_Text("Detect:   \t");
	SDXL_ImGui_SameLine();
	SDXL_ImGui_DragFloat(name.c_str(), &m_PlayerDetectionRange);
}

void tyr::MaitaComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_MoveSpeed);
	writer.Write(m_PlayerDetectionRange);
	UNREFERENCED_PARAMETER(writer);
}
#endif
