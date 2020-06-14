#include "tyrpch.h"
#include "BubbleShootingComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "InputHandler.h"
#include "SceneObject.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TeiwazEngine.h"
#include "Time.h"
tyr::BubbleShootingComp::BubbleShootingComp()
	: BaseComponent(ComponentType::BubbleShooting, "Bubble Shooting Component")
	, m_ShootCDElapser(0.5f)
	, m_CanShoot(false)
{
}

void tyr::BubbleShootingComp::Initialize()
{
	GET_CONTEXT->pInput->AddAction("Shoot", tyr::ButtonState::Pressed, VK_SPACE);
}

void tyr::BubbleShootingComp::Update()
{
	if (m_ShootCDElapser.Update(TIME->deltaTime))
		m_CanShoot = true;
	
	if (GET_CONTEXT->pInput->IsActionTriggered("Shoot") && m_CanShoot)
	{
		m_CanShoot = false;
		m_ShootCDElapser.Reset();
		
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


	bool isGoingLeft = GET_COMPONENT<Player1Controller>()->IsGoingLeft();
	if(isGoingLeft)
		newPos.x -= 50.f;
	else
		newPos.x += 50.f;

	newPos.y += 2.f;



	
	auto pReturnObj = new SceneObject(Transform(newPos), "Bubble Object", Tag::Bubble, true);
	GET_CONTEXT->pSceneManager->GetCurrentScene()->BufferSceneObject(pReturnObj);


	pReturnObj->AddComponent(new BubbleComp(isGoingLeft));

	
	return pReturnObj;
}
