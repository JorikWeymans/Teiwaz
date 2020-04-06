#include "tyrpch.h"
#include "Animation.h"

tyr::Animation::Animation()
	: m_AniElapser(0.2f)
	, m_CurrentAnimation(0)
{
	for(unsigned int i{0}; i < 8; i++)
	{
		m_AniSprites.emplace_back(Rectangle(i * 48.f, 0.f, 48, 48));
	}
	
}

void tyr::Animation::Update(float elapsed)
{

	if(m_AniElapser.Update(elapsed))
	{
		m_CurrentAnimation++;
		if (m_CurrentAnimation >= m_AniSprites.size())
			m_CurrentAnimation = 0;

		m_AniElapser.Reset();
	}
	
}

const tyr::Rectangle& tyr::Animation::GetCurrentAnimation() const
{
	return m_AniSprites[m_CurrentAnimation];
}
