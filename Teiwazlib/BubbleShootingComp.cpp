#include "tyrpch.h"
#include "BubbleShootingComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "SceneObject.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TeiwazEngine.h"

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
		CreateBubble();

		


#ifdef EDITOR_MODE
		SDXL_ImGui_ConsoleLog("Shooting");
#endif
	}
}
#ifdef EDITOR_MODE
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
#endif
tyr::SceneObject* tyr::BubbleShootingComp::CreateBubble() const
{
	auto newPos = m_pSceneObject->GetTransform()->GetPositionRaw();
	newPos.x -= 50.f;
	auto pReturnObj = new SceneObject(Transform(newPos), "Bubble Object", Tag::None, true);
	GET_CONTEXT->pSceneManager->GetCurrentScene()->BufferSceneObject(pReturnObj);

	pReturnObj->AddComponent(new TextureComp(2, PivotMode::Center, tyr::Rect(576.f,0.f,48.f,48.f)));
	pReturnObj->AddComponent(new ColliderComp(48, 48, PivotMode::Center, true));
	pReturnObj->AddComponent(new BubbleComp());

	
	return pReturnObj;
}
