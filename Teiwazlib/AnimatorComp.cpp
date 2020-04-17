#include "tyrpch.h"
#include "AnimatorComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "Animation.h"
#include "Animator.h"
#include "SceneObject.h"
#include "Time.h"
#include "InputHandler.h"
tyr::AnimatorComp::AnimatorComp()
	: tyr::BaseComponent(ComponentType::Animator)
	, m_pAnimator(nullptr)
	, m_pTextureComp(nullptr)
{
}

tyr::AnimatorComp::~AnimatorComp()
{
	SAFE_DELETE(m_pAnimator);
}

void tyr::AnimatorComp::Initialize()
{

	m_pAnimator = new Animator();



	//When the animation files get corrupt
	//auto idleAni = new tyr::Animation("Idle", 1.f, tyr::SpritePositions{ {0, tyr::Rect(0.f ,0.f,48,48)} });
	//
	//
	//auto walkAni = new tyr::Animation("Walking",.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f ,0.f,48,48)},
	//																		{1, tyr::Rect(48.f,0.f,48,48)},
	//																		{2, tyr::Rect(48.f * 2,0.f,48,48)} ,
	//																		{3, tyr::Rect(48.f * 3,0.f,48,48)} });
	//auto eatAni = new tyr::Animation("Eating",.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f + 4 * 48.f ,0.f,48,48)},
	//																	{1, tyr::Rect(48.f + 4 * 48.f,0.f,48,48)},
	//																	{2, tyr::Rect(48.f * 2 + 4 * 48.f,0.f,48,48)} ,
	//																	{3, tyr::Rect(48.f * 3 + 4 * 48.f,0.f,48,48)} });
	//
	//
	//EatAni->Save();
	//idleAni->Save();
	//walkAni->Save();
	//
	
	auto idleAni = new tyr::Animation("./Data/Animations/Idle.tyrAnimation");
	auto walkAni = new tyr::Animation("./Data/Animations/Walking.tyrAnimation");
	auto eatAni  = new tyr::Animation("./Data/Animations/Eating.tyrAnimation");
	

	
	m_pAnimator->AddAnimation(idleAni);
	m_pAnimator->AddAnimation(walkAni);
	m_pAnimator->AddAnimation(eatAni);





	
	m_pAnimator->SetAnimation("Idle");


	m_pTextureComp = m_pSceneObject->GetComponent<TextureComp>();

	INPUT->AddAction("AWalking", ButtonState::Pressed, 'E');
	INPUT->AddAction("AEating", ButtonState::Pressed, 'T');
}

void tyr::AnimatorComp::Update()
{
	m_pAnimator->Update(GET_CONTEXT->pTime->deltaTime);
	m_pTextureComp->SetSourceRect(m_pAnimator->GetCurrentAnimation());


	static bool isEating = false;
	
	
	if(INPUT->IsActionTriggered("AWalking"))
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

#ifdef USE_IM_GUI


void tyr::AnimatorComp::Debug()
{
}

void tyr::AnimatorComp::RenderEditor()
{
	SDXL_ImGui_Begin("Inspector");

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
	SDXL_ImGui_End();
}

void tyr::AnimatorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
#endif