#include "tyrpch.h"
#include "CMAnimators.h"

#include "Animator.h"
#include "BinStructureHelpers.h"
#include "BinaryWriter.h"
tyr::CMAnimators::CMAnimators()
	:CMBase("CMAnimator", "New Animator name")
{
}

void tyr::CMAnimators::Save(BinaryWriter& writer)
{
	writer.Write(ContentType::Animators);
	writer.Write(static_cast<UINT>(m_pContent.size()));
}

void tyr::CMAnimators::OnBtnDeleteClicked(Animator* pDeletedContent)
{
	UNREFERENCED_PARAMETER(pDeletedContent);
}

void tyr::CMAnimators::OnBtnAddClicked(const std::string& what)
{
	UNREFERENCED_PARAMETER(what);
}

void tyr::CMAnimators::OnItemDoubleClicked(int selected)
{
	UNREFERENCED_PARAMETER(selected);
}
