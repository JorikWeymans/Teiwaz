#include "tyrpch.h"
#include "RigidBodyComp.h"
#include "SceneObject.h"
#include "TyrException.h"
#include "TyrComps.h"
#include "Time.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
tyr::RigidBodyComp::RigidBodyComp(float gravity, bool useGravity)
	: tyr::BaseComponent(ComponentType::RigidBody)
	, m_pController(nullptr)
	, m_Vel(0.f, 0.f)
	, m_Force(0.f, 0.f)
	, m_UseGravity(useGravity)
	, m_Gravity(gravity)
	, m_ForceMultiplier(2.f)
{}

void tyr::RigidBodyComp::Initialize()
{
	m_pController = m_pSceneObject->GetComponent<CharacterControllerComp>();
	if (!m_pController) THROW_ERROR(L"RigidBodyComp needs a CharacterController to work!");
	
}

void tyr::RigidBodyComp::AddForce(float x, float y) noexcept
{
	m_Force.x += x;
	m_Force.y += y;
}

void tyr::RigidBodyComp::FixedUpdate()
{
	Vector2 thisFrameVel(0.f, 0.f);
	UpdateForce(thisFrameVel);


	thisFrameVel.y += m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime;
	m_Vel.y = thisFrameVel.y;
	
	//if(m_UseGravity)
	//	m_Vel.y += m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime;
	//
	//
	////snapping
	//if(m_Vel.y < m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime)
	//{
	//	m_Vel.y = m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime;
	//}

	
	m_pController->Move(0.f, thisFrameVel.y);
}


void tyr::RigidBodyComp::UpdateForce(Vector2& thisFrameVel) noexcept
{
	float amountX = 0.f, amountY = 0.f;

	if (std::abs(m_Force.x) > 0.01)
	{
		amountX = m_Force.x * GET_CONTEXT->pTime->fixedDeltaTime * m_ForceMultiplier;
		m_Force.x -= amountX;
	}
	if (std::abs(m_Force.y) > 0.01)
	{
		amountY = m_Force.y * GET_CONTEXT->pTime->fixedDeltaTime * m_ForceMultiplier;
		m_Force.y -= amountY;
		//m_Vel.y += amountY;
		
	}
	thisFrameVel.x = amountX;
	thisFrameVel.y = amountY;

	
	//m_pController->Move(amountX, amountY);
}

#ifdef EDITOR_MODE
void tyr::RigidBodyComp::Debug()
{
}

void tyr::RigidBodyComp::RenderEditor()
{
	const std::string strUniqueID = std::to_string(m_UniqueId);
	std::string name = "RigidBody Component##" + strUniqueID;

	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);


		//m_UseGravity
		SDXL_ImGui_Text("Gravity: \t");
		SDXL_ImGui_SameLine();
		name = "##RigidbodyCompUseGravity" + strUniqueID;
		SDXL_ImGui_Checkbox(name.c_str(), &m_UseGravity);

		//m_Gravity
		if (m_UseGravity)
		{

			SDXL_ImGui_Text("Gravity: \t");
			SDXL_ImGui_SameLine();
			name = "##RigidBodyCompGravity" + strUniqueID;
			SDXL_ImGui_DragFloat(name.c_str(), &m_Gravity, 1, 10, 10);
		}


		//m_Vel
		SDXL_ImGui_TextDisabled("Velocity:\t");
		SDXL_ImGui_SameLine();
		name = "##RigidBodyCompVelocity" + strUniqueID;
		auto displayVel = m_Vel;
		SDXL_ImGui_DragFloat2(name.c_str(), &displayVel.x);

		//m_Force
		SDXL_ImGui_TextDisabled("Force:   \t");
		SDXL_ImGui_SameLine();
		name = "##RigidBodyCompForce" + strUniqueID;
		auto displayForce = m_Force;
		SDXL_ImGui_DragFloat2(name.c_str(), &displayForce.x);


		SDXL_ImGui_PopItemWidth();
	}

}

void tyr::RigidBodyComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);

	writer.Write(m_Gravity);
}

#endif
