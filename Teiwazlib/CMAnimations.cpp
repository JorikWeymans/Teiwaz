#include "tyrpch.h"
#include "CMAnimations.h"

#include "Animation.h"

#include <algorithm>
#include "ContentManager.h"
#include "BinaryWriter.h"
#include "BinStructureHelpers.h"


tyr::CMAnimations::~CMAnimations()
{
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [](Animation* pA) {SAFE_DELETE(pA); });
}

void tyr::CMAnimations::Resize(unsigned newSize)
{
	m_pAnimations.resize(newSize, nullptr);
}

void tyr::CMAnimations::InsertAt(unsigned index, Animation* pData) noexcept
{
	m_pAnimations.at(index) = pData;
}

tyr::Animation* tyr::CMAnimations::GetAnimation(const std::string& animationName) const
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationName);
	if (found != m_pAnimations.end())
	{
		return *found;
	}

	return nullptr;
}

tyr::Animation* tyr::CMAnimations::GetAnimation(AnimationID id) const
{
	if (id >= m_pAnimations.size()) return nullptr;

	return m_pAnimations[id];
}

AnimationID tyr::CMAnimations::GetAnimationID(const std::string& animationName) const
{
	auto found = std::find(m_pAnimations.begin(), m_pAnimations.end(), animationName);

	if (found != m_pAnimations.end())
	{
		return static_cast<AnimationID>(std::distance(m_pAnimations.begin(), found));
	}

	return 0; //When animation is not found, return the first one
}

void tyr::CMAnimations::RenderEditor()
{
}

void tyr::CMAnimations::Save(BinaryWriter& writer)
{
	writer.Write(ContentType::Animation);
	writer.Write(static_cast<UINT>(m_pAnimations.size()));
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [&writer](Animation* a) { writer.Write(a->GetName()); });
}

