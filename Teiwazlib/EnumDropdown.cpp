#include "tyrpch.h"
#include "EnumDropdown.h"

#ifdef EDITOR_MODE
#include "AnimatorComp.h"

#define COMPONENT_TYPE_WIDTH 150.f

tyr::EnumDropdown* tyr::EnumDropdown::pInstance = nullptr;
tyr::EnumDropdown::EnumDropdown()
	: m_ComponentCount(static_cast<UINT>(magic_enum::enum_count<ComponentType>()))
	, m_TagCount(static_cast<UINT>(magic_enum::enum_count<Tag>()))
{

	m_ComponentItems.resize(m_ComponentCount);
	for (UINT i = 0; i < m_ComponentCount; i++)
		m_ComponentItems[i] = magic_enum::enum_name(static_cast<ComponentType>(static_cast<int>(i))).data();


	
	
	m_TagItems.resize(m_TagCount);
	Tag first = Tag::None;
	for (UINT i = 0; i < m_TagCount; i++)
	{
		auto theEnum = magic_enum::enum_name(first);
		std::string enumString{};
		enumString.resize(theEnum.size());
		memcpy(enumString.data(), theEnum.data(), theEnum.size());

		m_TagItems[i] = enumString;
		first++;
	}
}
tyr::EnumDropdown* tyr::EnumDropdown::GetInstance()
{
	if (!pInstance)
		pInstance = new EnumDropdown();

	return pInstance;
}
void tyr::EnumDropdown::Destroy()
{
	SAFE_DELETE(pInstance);
}


void tyr::EnumDropdown::ComponentTypeDropDown(const char* ImGuiID, ComponentType& selected) const
{
	UINT castSelected = static_cast<UINT>(selected);

	
	SDXL_ImGui_SetNextItemWidth(COMPONENT_TYPE_WIDTH);
	if (SDXL_ImGui_BeginCombo(ImGuiID, m_ComponentItems[castSelected], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_ComponentCount; n++)
		{
			bool isSelected = (castSelected == n);
			if (SDXL_ImGui_Selectable(m_ComponentItems[n], isSelected))
				castSelected = n;
			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	selected = static_cast<ComponentType>(castSelected);
	
}
void tyr::EnumDropdown::TagDropDown(const char* ImGuiID, Tag& selected) const
{
	UINT tag = TagToArrayIndex(selected);
	if (SDXL_ImGui_BeginCombo(ImGuiID, m_TagItems[tag].c_str(), SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_TagCount; n++)
		{
			const bool isSelected = (tag == n);
			if (SDXL_ImGui_Selectable(m_TagItems[n].c_str(), isSelected))
			{
				tag = n;

				if (tag <= 2)
					selected = static_cast<Tag>(tag);
				else
					selected = static_cast<Tag>(pow(2, tag - 1));

			}

			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}
}



UINT tyr::EnumDropdown::TagToArrayIndex(Tag theTag)
{
	int currentValue = static_cast<int>(theTag);

	if (currentValue <= 2)
		return currentValue;

	//else
	int timesDivided = 0;
	while (currentValue != 2)
	{
		currentValue /= 2;
		timesDivided++;
	}

	return timesDivided + 2; // +2 because you stop dividing when you get 2
}

#endif