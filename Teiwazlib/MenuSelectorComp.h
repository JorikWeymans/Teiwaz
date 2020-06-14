#pragma once
#include "BaseComponent.h"
#include "Color.h"

namespace tyr
{
	class TextComp;
	class MenuSelectorComp final : public BaseComponent
	{
	public:
		explicit MenuSelectorComp();
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
	public:
		MenuSelectorComp(const MenuSelectorComp&) = delete;
		MenuSelectorComp(MenuSelectorComp&&) = delete;
		MenuSelectorComp& operator=(const MenuSelectorComp&) = delete;
		MenuSelectorComp& operator=(MenuSelectorComp&&) = delete;
	};
}

