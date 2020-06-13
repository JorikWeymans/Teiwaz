#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class MenuSelectorComp : public BaseComponent
	{
	public:
		MenuSelectorComp();
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
	public:
		MenuSelectorComp(const MenuSelectorComp&) = delete;
		MenuSelectorComp(MenuSelectorComp&&) = delete;
		MenuSelectorComp& operator=(const MenuSelectorComp&) = delete;
		MenuSelectorComp& operator=(MenuSelectorComp&&) = delete;
	};
}

