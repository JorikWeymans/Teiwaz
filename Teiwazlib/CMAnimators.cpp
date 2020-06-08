#include "tyrpch.h"
#include "CMAnimators.h"


#include "BinStructureHelpers.h"
#include "BinaryWriter.h"
#include "Animator.h"
tyr::CMAnimators::CMAnimators()
	:CMBase("CMAnimator", "New Animator name")
{
}

tyr::Animator* tyr::CMAnimators::GetAnimator(AnimatorID id) const noexcept
{
	if (id >= m_pContent.size()) return nullptr;

	return m_pContent[id];
}

void tyr::CMAnimators::Save(BinaryWriter& writer)
{
	writer.Write(ContentType::Animators);
	writer.Write(static_cast<UINT>(m_pContent.size()));
	std::for_each(m_pContent.begin(), m_pContent.end(), [&writer](Animator* pA) { writer.Write(pA->GetName()); });
}

void tyr::CMAnimators::OnBtnDeleteClicked(Animator* pDeletedContent)
{
	UNREFERENCED_PARAMETER(pDeletedContent);
}

void tyr::CMAnimators::OnBtnAddClicked(const std::string& what)
{
	m_pContent.emplace_back(Animator::GenerateNew(what));
}

void tyr::CMAnimators::OnItemDoubleClicked(int selected)
{
	UNREFERENCED_PARAMETER(selected);
}
