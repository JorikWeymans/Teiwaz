#include "tyrpch.h"
#include "RigidBodyComp.h"
#include "SceneObject.h"
#include "TyrException.h"
#include "TyrComps.h"
#include "Time.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
tyr::RigidBodyComp::RigidBodyComp(float gravity)
	: tyr::BaseComponent(ComponentType::RigidBody)
	, m_pController(nullptr)
	, m_Gravity(gravity)
	, m_AddedForce(0.f)
	, m_Vel(0.f,0.f)
{
}

void tyr::RigidBodyComp::Initialize()
{
	m_pController = m_pSceneObject->GetComponent<CharacterControllerComp>();
	if (!m_pController) THROW_ERROR(L"RigidBodyComp needs a CharacterController to work!");
	
}

void tyr::RigidBodyComp::AddForce(float x, float y)
{
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	m_Vel.y += y;
}



void tyr::RigidBodyComp::FixedUpdate()
{

	m_Vel.y += m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime;


	//snapping
	if(m_Vel.y < m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime)
	{
		m_Vel.y = m_Gravity * GET_CONTEXT->pTime->fixedDeltaTime;
	}
	m_pController->Move(0.f, m_Vel.y);
}

#ifdef USE_IM_GUI
void tyr::RigidBodyComp::Debug()
{
}

void tyr::RigidBodyComp::RenderEditor()
{
	std::string name = "RigidBody Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//Gravity
		SDXL_ImGui_Text("Gravity: \t");
		SDXL_ImGui_SameLine();
		name = "##Grav" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Gravity, 1, 10, 10);
		//
		//SDXL_ImGui_Text("Height: \t");
		//SDXL_ImGui_SameLine();
		//name = "##ColW" + std::to_string(m_UniqueId);
		//SDXL_ImGui_DragFloat(name.c_str(), &m_Height, 1, 0, GET_CONTEXT->pGameSpace->height);


		SDXL_ImGui_PopItemWidth();
	}

}

void tyr::RigidBodyComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);

	writer.Write(m_Gravity);
}
#endif
