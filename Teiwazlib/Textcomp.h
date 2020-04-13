#pragma once
#include "BaseComponent.h"
#include "Vectors.h"
#include "TyrEnums.h"
#include "Color.h"

namespace tyr
{
	class Font;
	class TransformComp;
	class TextComp final : public BaseComponent
	{
	public:
		explicit TextComp(const std::wstring& textPath, const std::wstring& text, const Color& color,  const Vector2& offset = Vector2(0.f,0.f));
		~TextComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();

		void SetText(const std::wstring& newText);
#ifdef USE_IM_GUI
		void Save(BinaryWriter& writer) override;
#endif

	private:
		std::wstring m_TextPath;
		std::wstring m_Text;
		Color m_Color;
		
		Font const* m_pFont; //Weak pointer
		TransformComp const* m_pTransform; //Weak pointer
		Vector2 m_Offset;
	public:
		TextComp() = delete;
		TextComp(const TextComp&) = delete;
		TextComp(TextComp&&) = delete;
		TextComp& operator=(const TextComp&) = delete;
		TextComp& operator=(TextComp&&) = delete;

	};
}
