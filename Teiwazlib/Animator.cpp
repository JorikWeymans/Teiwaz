#include "tyrpch.h"
#include "Animator.h"
#include <algorithm>
#include "Animation.h"
tyr::Animator::Animator()
	: m_pCurrent(nullptr)
{
}

tyr::Animator::~Animator()
{
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [](auto& a) {delete a.second; a.second = nullptr; });
	m_pAnimations.clear();
}

void tyr::Animator::AddAnimation(const std::string& name, Animation* ani)
{
	const auto found = m_pAnimations.find(name);
	if (found == m_pAnimations.end())
	{
		m_pAnimations.insert({ name, ani });
	}
	
}

void tyr::Animator::SetAnimation(const std::string& name)
{
	const auto found = m_pAnimations.find(name);
	if (found != m_pAnimations.end())
	{
		m_pCurrent = found->second;
	}
	
}

void tyr::Animator::Update(float elapsed)
{
	m_pCurrent->Update(elapsed);
}

const tyr::Rect& tyr::Animator::GetCurrentAnimation() const
{
	return m_pCurrent->GetCurrentAnimation();
}
