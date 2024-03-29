#include "tyrpch.h"
#include "EnumDropdown.h"

#ifdef EDITOR_MODE
#include "AnimatorComp.h"
#include "AnimatorVariable.h"

#define COMPONENT_TYPE_WIDTH 150.f
#define TAG_WIDTH 120.f
#define EQUATON_WIDTH 100.f
#define VARIABLE_TYPE_WIDTH 60.f
#define PIVOT_MODE_WIDTH 100.f
#define BUTTON_TYPE_WIDTH 100.f
tyr::EnumDropdown* tyr::EnumDropdown::pInstance = nullptr;
tyr::EnumDropdown::EnumDropdown()
	: m_ComponentCount(static_cast<UINT>(magic_enum::enum_count<ComponentType>()))
	, m_TagCount(static_cast<UINT>(magic_enum::enum_count<Tag>()))
	, m_EquationCount(static_cast<UINT>(magic_enum::enum_count<Equation>()))
	, m_VariableTypeCount(static_cast<UINT>(magic_enum::enum_count<VariableType>()))
	, m_PivotModeCount(static_cast<UINT>(magic_enum::enum_count<PivotMode>()))
	, m_ButtonTypeCount(static_cast<UINT>(magic_enum::enum_count<ButtonType>()))
{

	m_ComponentItems.resize(m_ComponentCount);
	for (UINT i = 0; i < m_ComponentCount; i++)
		m_ComponentItems[i] = magic_enum::enum_name(static_cast<ComponentType>(static_cast<int>(i))).data();


	
	
	m_TagItems.resize(m_TagCount);
	Tag first = Tag::None;
	for (UINT i = 0; i < m_TagCount; i++)
	{
		m_TagItems[i] = magic_enum::enum_name(first).data();
		first++;
	}

	m_EquationItems.resize(m_EquationCount);
	for (UINT i = 0; i < m_EquationCount; i++)
		m_EquationItems[i] = magic_enum::enum_name(static_cast<Equation>(i)).data();

	m_VariableTypeItems.resize(m_VariableTypeCount);
	//Manual because magic_enum fails this
	m_VariableTypeItems[0] = "Bool";
	m_VariableTypeItems[1] = "Float";


	m_PivotModeItems.resize(m_PivotModeCount);
	for (UINT i = 0; i < m_PivotModeCount; i++)
		m_PivotModeItems[i] = magic_enum::enum_name(static_cast<PivotMode>(static_cast<int>(i))).data();


	m_ButtonTypeItems.resize(m_ButtonTypeCount);
	for (UINT i{ 0 }; i < m_ButtonTypeCount; i++)
		m_ButtonTypeItems[i] = magic_enum::enum_name(static_cast<ButtonType>(static_cast<int>(i))).data();
	
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


void tyr::EnumDropdown::ComponentTypeDropdown(const char* ImGuiID, ComponentType& selected, int customWidth) const
{
	UINT castSelected = static_cast<UINT>(selected);

	if (customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(COMPONENT_TYPE_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));
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
void tyr::EnumDropdown::TagDropdown(const char* ImGuiID, Tag& selected, int customWidth) const
{
	UINT tag = TagToArrayIndex(selected);

	if (customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(TAG_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));
	if (SDXL_ImGui_BeginCombo(ImGuiID, m_TagItems[tag], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_TagCount; n++)
		{
			const bool isSelected = (tag == n);
			if (SDXL_ImGui_Selectable(m_TagItems[n], isSelected))
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

void tyr::EnumDropdown::EquationDropdown(const char* ImGuiID, Equation& selected, int customWidth) const
{
	UINT castSelected = static_cast<UINT>(selected);

	if(customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(EQUATON_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));
	
	if (SDXL_ImGui_BeginCombo(ImGuiID, m_EquationItems[castSelected], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_EquationCount; n++)
		{
			bool isSelected = (castSelected == n);
			if (SDXL_ImGui_Selectable(m_EquationItems[n], isSelected))
				castSelected = n;
			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	selected = static_cast<Equation>(castSelected);
}
void tyr::EnumDropdown::VariableTypeDropdown(const char* ImGuiID, VariableType& selected, int customWidth) const
{
	UINT castSelected = static_cast<UINT>(selected);

	if(customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(VARIABLE_TYPE_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));
	
	if (SDXL_ImGui_BeginCombo(ImGuiID, m_VariableTypeItems[castSelected], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_VariableTypeCount; n++)
		{
			bool isSelected = (castSelected == n);
			if (SDXL_ImGui_Selectable(m_VariableTypeItems[n], isSelected))
				castSelected = n;
			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	selected = static_cast<VariableType>(castSelected);
}

void tyr::EnumDropdown::PivotModeDropDown(const char* ImGuiID, PivotMode& selected, int customWidth) const
{
	UINT castSelected = static_cast<UINT>(selected);

	if (customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(PIVOT_MODE_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));

	if (SDXL_ImGui_BeginCombo(ImGuiID, m_PivotModeItems[castSelected], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_PivotModeCount; n++)
		{
			bool isSelected = (castSelected == n);
			if (SDXL_ImGui_Selectable(m_PivotModeItems[n], isSelected))
				castSelected = n;
			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	selected = static_cast<PivotMode>(castSelected);
}

void tyr::EnumDropdown::ButtonTypeDropDown(const char* ImGuiID, ButtonType& selected, int customWidth) const
{
	UINT castSelected = static_cast<UINT>(selected);

	if (customWidth == -1)
		SDXL_ImGui_SetNextItemWidth(BUTTON_TYPE_WIDTH);
	else
		SDXL_ImGui_SetNextItemWidth(static_cast<float>(customWidth));

	if (SDXL_ImGui_BeginCombo(ImGuiID, m_ButtonTypeItems[castSelected], SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < m_ButtonTypeCount; n++)
		{
			bool isSelected = (castSelected == n);
			if (SDXL_ImGui_Selectable(m_ButtonTypeItems[n], isSelected))
				castSelected = n;
			if (isSelected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}

	selected = static_cast<ButtonType>(castSelected);
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