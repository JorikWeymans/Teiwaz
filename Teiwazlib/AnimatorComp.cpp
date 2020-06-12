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
	:AnimatorComp(0)
{
}

tyr::AnimatorComp::AnimatorComp(AnimatorID id)
	: tyr::BaseComponent(ComponentType::Animator, "Animator Component")
	, m_pAnimator(nullptr)
	, m_AnimatorID(id)
	, m_pTextureComp(nullptr)
{
}

tyr::AnimatorComp::~AnimatorComp()
{
}


void tyr::AnimatorComp::Initialize()
{
	m_pAnimator = CONTENT_MANAGER->GetAnimator(m_AnimatorID);
	

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

void tyr::AnimatorComp::InternalRenderEditor()
{
	SDXL_ImGui_Text("Animator:\t");
	SDXL_ImGui_SameLine();

	AnimatorID prev = m_AnimatorID;
	const std::string name = "##AnimatorCompAnimatorSelection" + std::to_string(m_UniqueId);
	
	ContentManager::GetInstance()->EditorAnimatorDropDown(name.c_str(), m_AnimatorID);

	if(prev != m_AnimatorID)
	{
		m_pAnimator = CONTENT_MANAGER->GetAnimator(m_AnimatorID);
	}
}

void tyr::AnimatorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_AnimatorID);
}
#endif