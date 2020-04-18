#include "tyrpch.h"
#include "Animator.h"
#include <algorithm>
#include "Animation.h"
#include "ContentManager.h"

tyr::Animator::Animator()
	: m_pCurrent(nullptr)
{
	const auto equalTo0 = [](const float  b) -> bool { return b < 0.02f; };
	const auto moreThan0 = [](const float  b) -> bool { return b > 0.02f; };

	const auto isTrue = [](const bool b) -> bool { return b; };
	const auto isFalse = [](const bool b) -> bool { return !b; };

	m_pConnections.emplace_back(new Connection{ "Bub_Idle","Bub_Walking", "Speed",  moreThan0 });
	m_pConnections.emplace_back(new Connection{ "Bub_Walking", "Bub_Idle", "Speed", equalTo0 });
	
	m_pConnections.emplace_back(new Connection{ "Bub_Idle","Bub_Eating", "IsEating",equalTo0,  isTrue });
	m_pConnections.emplace_back(new Connection{ "Bub_Walking", "Bub_Eating", "IsEating", equalTo0, isTrue});

	m_pConnections.emplace_back(new Connection{ "Bub_Eating","Bub_Idle", "IsEating", equalTo0, isFalse });
	m_pConnections.emplace_back(new Connection{ "Bub_Eating", "Bub_Walking", "IsEating", equalTo0, isFalse });
	
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
	const std::string& name = pAni->GetName();
	const auto found = m_pAnimations.find(pAni->GetName());
	if (found == m_pAnimations.end())
	{
		m_pAnimations.insert({ name, pAni });
	}
	
}

void tyr::Animator::SetAnimation(const std::string& name)
{
	UNREFERENCED_PARAMETER(name);
	const auto found = m_pAnimations.find(name);
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
	UNREFERENCED_PARAMETER(variable);

	for(auto pcon : m_pConnections)
	{
		if (pcon->VariableName != variable) continue;
		if (pcon->A != m_pCurrent->GetName()) continue;

		if(pcon->floatTest(value))
		{
			SetAnimation(pcon->B);
		}
		
	}
}

void tyr::Animator::SetBool(const std::string& variable, bool value)
{
	for (auto pcon : m_pConnections)
	{
		if (pcon->VariableName != variable) continue;
		if (pcon->A != m_pCurrent->GetName()) continue;

		if (pcon->boolTest(value))
		{
			SetAnimation(pcon->B);
		}

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
