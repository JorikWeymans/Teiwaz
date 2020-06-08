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

		static UINT TagToArrayIndex(Tag theTag);
	};

#endif
}
