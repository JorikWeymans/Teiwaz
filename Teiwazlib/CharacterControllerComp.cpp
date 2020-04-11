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

	bool canMoveY = true;
	if( y < 0  && 
		playerColl.pos.y >  playSpace->height)
	{
		m_pTransform->SetPositionY(playSpace->height - ENGINE_SPACING_TOP);
	}

	if (GET_CONTEXT->pPhysics->Raycast(m_pTransform->GetPosition() - Vector2(0, y), Vector2(0, 1), m_pCollider->GetColliderRect().width / 2))
	{
		canMoveY = false;
		SDXL_ImGui_ConsoleLog("They are intersecting");
	}

	m_pSceneObject->Translate(canMoveX ? x: 0.f, canMoveY ? y : 0.f);
	
}
#ifdef USE_IM_GUI
void tyr::CharacterControllerComp::Debug()
{
	
	SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition()), 
							static_cast<SDXL::SDXLVec2>(m_pTransform->GetPosition() + ( Vector2(0,1) * (m_pCollider->GetColliderRect().width / 2))), static_cast<SDXL::SDXLVec4>(ColorWhite));
	
}

void tyr::CharacterControllerComp::RenderEditor()
{
	SDXL_ImGui_Begin("Inspector");

	std::string name = "CharacterController Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//POSITION
		//SDXL_ImGui_Text("Width:  \t");
		//SDXL_ImGui_SameLine();
		//name = "##ColH" + std::to_string(m_UniqueId);
		//SDXL_ImGui_DragFloat(name.c_str(), &m_Width, 1, 0, GET_CONTEXT->pGameSpace->width);
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