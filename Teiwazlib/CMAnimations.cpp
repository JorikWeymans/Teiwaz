#include "tyrpch.h"
#include "CMAnimations.h"

#include "Animation.h"

#include <algorithm>
#include "ContentManager.h"
#include "BinaryWriter.h"
#include "BinStructureHelpers.h"
#include "StringManipulation.h"


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
#ifdef EDITOR_MODE
void tyr::CMAnimations::RenderEditor()
{
	static int selectedAnimation = -1;

	ShowAnimations(selectedAnimation);

	BtnDeleteAnimation(selectedAnimation);
	BtnMoveAnimationUp(selectedAnimation);
	BtnMoveAnimationDown(selectedAnimation);

	BtnAddAnimation();
}

void tyr::CMAnimations::Save(BinaryWriter& writer)
{
	writer.Write(ContentType::Animation);
	writer.Write(static_cast<UINT>(m_pAnimations.size()));
	std::for_each(m_pAnimations.begin(), m_pAnimations.end(), [&writer](Animation* a) { writer.Write(a->GetName()); });
}


void tyr::CMAnimations::ShowAnimations(int& selectedAnimation)
{
	SDXL_ImGui_Text("ID\tName");

	for (int i{ 0 }; i < static_cast<int>(m_pAnimations.size()); ++i)
	{
		std::string tag = FormatString(" %i\t%s", i, m_pAnimations[i]->GetName().c_str());

		if (SDXL_ImGui_Selectable(tag.c_str(), selectedAnimation == i, SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			selectedAnimation = i;
		}
		if (SDXL_ImGui_IsItemHovered() && SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left))
		{

			//TODO: Open Animation editor
		}
	}
	SDXL_ImGui_Separator();
}

void tyr::CMAnimations::BtnDeleteAnimation(int selectedAnimation)
{
	SDXL_ImGui_Text("            "); SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Delete Animation##CMAnimations"))
	{
		if (selectedAnimation > -1 && m_pAnimations.size() > 1)
		{
			auto deleteThis = m_pAnimations[selectedAnimation];
			m_pAnimations[selectedAnimation] = *(m_pAnimations.end() - 1);
			m_pAnimations.pop_back();
			
			SAFE_DELETE(deleteThis);

			CONTENT_MANAGER->Save();

		}
	}
}
void tyr::CMAnimations::BtnMoveAnimationUp(int& selectedAnimation)
{
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("UP##CMAnimations"))
	{
		if (selectedAnimation > 0)
		{
			auto temp = m_pAnimations[selectedAnimation - 1];
			m_pAnimations[selectedAnimation - 1] = m_pAnimations[selectedAnimation];
			m_pAnimations[selectedAnimation] = temp;
			selectedAnimation--;
			CONTENT_MANAGER->Save();

		}
	}
}
void tyr::CMAnimations::BtnMoveAnimationDown(int& selectedAnimation)
{
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("DOWN##CMAnimations"))
	{
		if (selectedAnimation >= 0 && selectedAnimation < static_cast<int>(m_pAnimations.size() - 1))
		{
			auto temp = m_pAnimations[selectedAnimation + 1];
			m_pAnimations[selectedAnimation + 1] = m_pAnimations[selectedAnimation];
			m_pAnimations[selectedAnimation] = temp;
			selectedAnimation++;
			CONTENT_MANAGER->Save();

		}
	}
}

void tyr::CMAnimations::BtnAddAnimation()
{
	static char newAnimation[40];


	SDXL_ImGui_Text("      "); SDXL_ImGui_SameLine();
	SDXL_ImGui_SetNextItemWidth(200.f);
	SDXL_ImGui_InputTextWithHint("##CMAnimationsNewAnimation", "New Animation name", newAnimation, ARRAY_SIZE(newAnimation));
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add##ContentManager"))
	{

		Animation* pAnimation = Animation::GenerateNew(std::string(newAnimation));
		m_pAnimations.emplace_back(pAnimation);

		CONTENT_MANAGER->Save();

	}
}
#endif

