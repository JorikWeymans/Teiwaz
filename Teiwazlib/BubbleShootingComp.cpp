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
	: BaseComponent(ComponentType::BubbleShooting, "Bubble Shooting Component")
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
void tyr::BubbleShootingComp::InternalRenderEditor()
{

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
	newPos.y += 2.f;
	auto pReturnObj = new SceneObject(Transform(newPos), "Bubble Object", Tag::Bubble, true);
	GET_CONTEXT->pSceneManager->GetCurrentScene()->BufferSceneObject(pReturnObj);


	pReturnObj->AddComponent(new BubbleComp());

	
	return pReturnObj;
}
