#include "tyrpch.h"
#include "Animation.h"

tyr::Animation::Animation(const std::string& animationName, float tpf,SpritePositions&& sp)
	: m_AnimationName(animationName)
	, m_AniElapser(tpf)
	, m_CurrentAnimation(0)

{
	m_AniSprites = std::move(sp);
	
	
}

void tyr::Animation::Update(float elapsed)
{

	if(m_AniElapser.Update(elapsed))
	{
		m_CurrentAnimation++;
		if (m_CurrentAnimation >= m_AniSprites.size())
		{
		
			m_CurrentAnimation = 0;
		}
		m_AniElapser.Reset();
	}

}

const tyr::Rect& tyr::Animation::GetCurrentAnimation() const
{
	return m_AniSprites.at(m_CurrentAnimation);
}

void tyr::Animation::Reset()
{
	m_AniElapser.Reset();
	m_CurrentAnimation = 0;
}
