#include "tyrpch.h"
#include "BubbleShootingComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "SceneObject.h"

tyr::BubbleShootingComp::BubbleShootingComp()
	: BaseComponent(ComponentType::BubbleShootingComp)
{
}

void tyr::BubbleShootingComp::Initialize()
{
	GET_CONTEXT->pInput->AddAction("Shoot", tyr::ButtonState::Pressed, VK_SPACE);
}

void tyr::BubbleShootingComp::Update()
{
	if (GET_CONTEXT->pInput->IsActionTriggered("Shoot"))
	{
		SDXL_ImGui_ConsoleLog("Shooting");
	}
}

void tyr::BubbleShootingComp::RenderEditor()
{
	std::string name = "Bubble Shooting Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//Raycast

		//
		//SDXL_ImGui_Text("Height: \t");
		//SDXL_ImGui_SameLine();
		//name = "##ColW" + std::to_string(m_UniqueId);
		//SDXL_ImGui_DragFloat(name.c_str(), &m_Height, 1, 0, GET_CONTEXT->pGameSpace->height);


		SDXL_ImGui_PopItemWidth();
	}
	//SDXL_ImGui_End();
}

void tyr::BubbleShootingComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
