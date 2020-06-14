#pragma once
#include <vector>

namespace tyr
{
	enum class VariableType : unsigned char;
	enum class Equation : unsigned char;
#ifdef EDITOR_MODE
#define DROPDOWN_TAG EnumDropdown::GetInstance()->TagDropdown
#define DROPDOWN_COMPONENT_TYPE EnumDropdown::GetInstance()->ComponentTypeDropdown
#define DROPDOWN_EQUATION EnumDropdown::GetInstance()->EquationDropdown
#define DROPDOWN_VARIABLE_TYPE EnumDropdown::GetInstance()->VariableTypeDropdown
#define DROPDOWN_PIVOT_MODE EnumDropdown::GetInstance()->PivotModeDropDown
#define DROPDOWN_BUTTON_TYPE EnumDropdown::GetInstance()->ButtonTypeDropDown
	
	enum class ComponentType : UINT;
	class EnumDropdown final
	{
	public:
		static EnumDropdown* GetInstance();
		static void Destroy();

		
		void ComponentTypeDropdown(const char* ImGuiID, ComponentType& selected, int customWidth = -1) const;
		void TagDropdown(const char* ImGuiID, Tag& selected, int customWidth = -1) const;
		void EquationDropdown(const char* ImGuiID, Equation& selected, int customWidth = -1) const;
		void VariableTypeDropdown(const char* ImGuiID, VariableType& selected, int customWidth = -1) const;
		void PivotModeDropDown(const char* ImGuiID, PivotMode& selected, int customWidth = -1) const;
		void ButtonTypeDropDown(const char* ImGuiID, ButtonType& selected, int customWidth = -1) const;
	private:
		EnumDropdown();
		
		static EnumDropdown* pInstance;

		const UINT m_ComponentCount;
		std::vector<const char*> m_ComponentItems;
		
		const UINT m_TagCount;
		std::vector<const char*> m_TagItems;

		const UINT m_EquationCount;
		std::vector<const char*> m_EquationItems;

		const UINT m_VariableTypeCount;
		std::vector<const char*> m_VariableTypeItems;

		const UINT m_PivotModeCount;
		std::vector<const char*> m_PivotModeItems;

		const UINT m_ButtonTypeCount;
		std::vector<const char*> m_ButtonTypeItems;

		
		static UINT TagToArrayIndex(Tag theTag);
	};

#endif
}
