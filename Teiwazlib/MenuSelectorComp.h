#pragma once
#include "BaseComponent.h"
#include "Color.h"

namespace tyr
{
	class TextComp;
	class MenuSelectorComp final : public BaseComponent
	{
	public:
		explicit MenuSelectorComp(const Color& selected = Color(1.f, 1.f, 1.f), const Color& notSelected = Color(.7f, .7f,.7f));
		explicit MenuSelectorComp(const Color_POD& selected, const Color_POD& notSelected);
		~MenuSelectorComp();

		void Initialize() override;
		void PostInitialize() override;
		
		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		TextComp* m_pStartGame, * m_pQuitGame;
		UINT m_Selected;
		Color m_SelectedColor, m_NotSelectedColor;
	public:
		MenuSelectorComp(const MenuSelectorComp&) = delete;
		MenuSelectorComp(MenuSelectorComp&&) = delete;
		MenuSelectorComp& operator=(const MenuSelectorComp&) = delete;
		MenuSelectorComp& operator=(MenuSelectorComp&&) = delete;
	};
}

