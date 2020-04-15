#include "tyrpch.h"
#include "AnimatorComp.h"
#include "TyrComps.h"
#include "BinaryWriter.h"
#include "Animation.h"
#include "Animator.h"
#include "SceneObject.h"
#include "Time.h"
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

	auto walkAni = new tyr::Animation(.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f ,0.f,48,48)},
																			{1, tyr::Rect(48.f,0.f,48,48)},
																			{2, tyr::Rect(48.f * 2,0.f,48,48)} ,
																			{3, tyr::Rect(48.f * 3,0.f,48,48)} });
	auto EatAni = new tyr::Animation(.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f + 4 * 48.f ,0.f,48,48)},
																		{1, tyr::Rect(48.f + 4 * 48.f,0.f,48,48)},
																		{2, tyr::Rect(48.f * 2 + 4 * 48.f,0.f,48,48)} ,
																		{3, tyr::Rect(48.f * 3 + 4 * 48.f,0.f,48,48)} });
	m_pAnimator->AddAnimation("Walking", walkAni);
	m_pAnimator->AddAnimation("Eating", EatAni);
	m_pAnimator->SetAnimation("Walking");


	m_pTextureComp = m_pSceneObject->GetComponent<TextureComp>();
	
}

void tyr::AnimatorComp::Update()
{
	m_pAnimator->Update(GET_CONTEXT->pTime->deltaTime);
	m_pTextureComp->SetSourceRect(m_pAnimator->GetCurrentAnimation());
}

void tyr::AnimatorComp::Debug()
{
}

void tyr::AnimatorComp::RenderEditor()
{
}

void tyr::AnimatorComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
}
