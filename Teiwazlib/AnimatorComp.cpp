#include "tyrpch.h"
#include "AnimatorComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "Animation.h"
#include "Animator.h"
#include "SceneObject.h"
#include "Time.h"
#include "InputHandler.h"
#include "ContentManager.h"

tyr::AnimatorComp::AnimatorComp()
	: tyr::BaseComponent(ComponentType::Animator)
	, m_pAnimator(nullptr)
	, m_pTextureComp(nullptr)
{
}

tyr::AnimatorComp::~AnimatorComp()
{
}


void tyr::AnimatorComp::Initialize()
{
	m_pAnimator = CONTENT_MANAGER->GetAnimator(0);
	

	m_pTextureComp = m_pSceneObject->GetComponent<TextureComp>();
	
	INPUT->AddAction("AEating", ButtonState::Pressed, VK_SPACE);
}

void tyr::AnimatorComp::Update()
{
	m_pAnimator->Update(GET_CONTEXT->pTime->deltaTime);
	m_pTextureComp->SetSourceRect(m_pAnimator->GetCurrentAnimation());


	static bool isEating = false;
	
	
	if(INPUT->IsActionTriggered("AEating"))
	{
		isEating = true;
		m_pAnimator->SetBool("IsEating", true);
	}

	if(isEating == true)
	{
	
		
		if(m_pAnimator->IsAtEnd())
		{
			isEating = false;
			m_pAnimator->SetBool("IsEating", false);
		}
	}

}
void tyr::AnimatorComp::SetFloat(const std::string& variable, float amount)
{
	m_pAnimator->SetFloat(variable, amount);
}

#ifdef EDITOR_MODE


void tyr::AnimatorComp::Debug()
{
}

void tyr::AnimatorComp::RenderEditor()
{
	//if(SDXL_ImGui_Begin("Inspector"))
	{
		std::string name = "Animator Component##" + std::to_string(m_UniqueId);
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
}

void tyr::AnimatorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
#endif