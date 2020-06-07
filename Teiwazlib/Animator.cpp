#include "tyrpch.h"
#include "Animator.h"
#include <algorithm>
#include "Animation.h"
#include "ContentManager.h"




tyr::Connection::Connection(AnimationID _Lhs, AnimationID _Rhs, AnimatorVariable&& _Variable)
	: lhs(_Lhs)
	, rhs(_Rhs)
	, variable(std::move(_Variable))
{
}

tyr::Animator::Animator()
	: m_pCurrent(nullptr)
{
	m_pConnections.emplace_back(new Connection(1, 0, AnimatorVariable( "Speed", 0.f, Equation::BiggerThan)));
	m_pConnections.emplace_back(new Connection( 0, 1, AnimatorVariable("Speed", 0.f, Equation::Equal)));
	
	m_pConnections.emplace_back(new Connection( 1,2, AnimatorVariable("IsEating",true,  Equation::Equal)));
	m_pConnections.emplace_back(new Connection(0, 2, AnimatorVariable("IsEating", true, Equation::Equal)));
	

	m_pConnections.emplace_back(new Connection(2, 1, AnimatorVariable("IsEating", false, Equation::Equal)));
	m_pConnections.emplace_back(new Connection(2, 0, AnimatorVariable("IsEating", false, Equation::Equal)));

	
}

tyr::Animator::~Animator()
{
	//std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [](auto& a) {delete a.second; a.second = nullptr; });
	std::for_each(m_pConnections.begin(), m_pConnections.end(), [](auto& a) {delete a; a = nullptr; });
	m_pAnimations.clear();
	
}

void tyr::Animator::AddAnimation(AnimationID id)
{
	Animation* pTHeAnimation = CONTENT_MANAGER->GetAnimation(id);
	AddAnimation(pTHeAnimation);
}
void tyr::Animator::AddAnimation(Animation* pAni)
{
	const AnimationID id = CONTENT_MANAGER->GetAnimationID(pAni);
	const auto found = m_pAnimations.find(id);
	if (found == m_pAnimations.end())
	{
		m_pAnimations.insert({ id, pAni });
	}
	
}

void tyr::Animator::SetAnimation(AnimationID id)
{
	const auto found = m_pAnimations.find(id);
	if (found != m_pAnimations.end())
	{

		if (m_pCurrent) m_pCurrent->Reset();
		m_pCurrent = found->second;
	}
	
}

void tyr::Animator::Update(float elapsed)
{
	m_pCurrent->Update(elapsed);
}

void tyr::Animator::SetFloat(const std::string& variable, float value)
{
	for(auto pcon : m_pConnections)
	{
		if (pcon->variable.GetName() != variable) continue;
		if (pcon->variable.GetType() != VariableType::Float) continue;
		if (pcon->lhs != CONTENT_MANAGER->GetAnimationID(m_pCurrent)) continue;


		if(pcon->variable.DoEquation(value))
			SetAnimation(pcon->rhs);
		
	}
}

void tyr::Animator::SetBool(const std::string& variable, bool value)
{
	for (auto pcon : m_pConnections)
	{
		if (pcon->variable.GetName() != variable) continue;
		if (pcon->variable.GetType() != VariableType::Bool) continue;
		if (pcon->lhs != CONTENT_MANAGER->GetAnimationID(m_pCurrent)) continue;


		if (pcon->variable.DoEquation(value))
			SetAnimation(pcon->rhs);


	}
	
}

bool tyr::Animator::IsAtEnd() const
{
	return m_pCurrent->IsAtEnd();
}

const tyr::Rect& tyr::Animator::GetCurrentAnimation() const
{
	return m_pCurrent->GetCurrentAnimation();
}
