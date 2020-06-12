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
	m_pAnimator->Initialize();
	
	m_pTextureComp = GET_COMPONENT<TextureComp>();


}
void tyr::AnimatorComp::Update()
{
	m_pAnimator->Update(GET_CONTEXT->pTime->deltaTime);
	m_pTextureComp->SetSourceRect(m_pAnimator->GetCurrentAnimation());
	
}
void tyr::AnimatorComp::SetFloat(const std::string& variable, float value)
{
	m_pAnimator->SetFloat(variable, value);
}
void tyr::AnimatorComp::SetBool(const std::string& variable, bool value)
{
	m_pAnimator->SetBool(variable, value);
}

bool tyr::AnimatorComp::IsAtEnd() const noexcept
{
	return m_pAnimator->IsAtEnd();
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
		m_pAnimator->Initialize();

		SDXL_ImGui_ConsoleLog("this is a log");
	}
}

void tyr::AnimatorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_AnimatorID);
}
#endif