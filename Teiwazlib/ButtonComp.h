#pragma once
#include "BaseComponent.h"
#include "Color.h"
namespace tyr
{
	class TextComp;
	class ButtonComp final : public BaseComponent
	{
	public:
		explicit ButtonComp(ButtonType type = ButtonType::QuitGame, const Color& selected = Color(1.f, 1.f, 1.f), const Color& notSelected = Color(.7f, .7f, .7f));
		explicit ButtonComp(ButtonType type, const Color_POD& selected, const Color_POD& notSelected);
		
		~ButtonComp();

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}

		void Select();
		void DeSelect();
		
#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		ButtonType m_ButtonType;
		TextComp* m_pTextComp;
		Color m_ColorSelected, m_ColorNotSelected;
	public:
		ButtonComp(const ButtonComp&) = delete;
		ButtonComp(ButtonComp&&) = delete;
		ButtonComp& operator=(const ButtonComp&) = delete;
		ButtonComp& operator=(ButtonComp&&) = delete;
	};
}

