#pragma once
#include <vector>

namespace tyr
{
#ifdef EDITOR_MODE
#define DROPDOWN_TAG EnumDropdown::GetInstance()->TagDropDown
#define DROPDOWN_COMPONENT_TYPE EnumDropdown::GetInstance()->ComponentTypeDropDown
	enum class ComponentType : UINT;
	class EnumDropdown final
	{
	public:
		static EnumDropdown* GetInstance();
		static void Destroy();

		
		void ComponentTypeDropDown(const char* ImGuiID, ComponentType& selected) const;
		void TagDropDown(const char* ImGuiID, Tag& selected) const;

	private:
		EnumDropdown();
		
		static EnumDropdown* pInstance;

		const UINT m_ComponentCount;
		std::vector<const char*> m_ComponentItems;
		const UINT m_TagCount;
		std::vector<std::string> m_TagItems;


		static UINT TagToArrayIndex(Tag theTag);
	};

#endif
}
