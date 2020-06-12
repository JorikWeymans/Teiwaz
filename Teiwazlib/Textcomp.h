#pragma once
#include "BaseComponent.h"
#include "Vectors.h"
#include "TyrEnums.h"
#include "Color.h"

namespace tyr
{
	class TransformComp;
	class TextComp final : public BaseComponent
	{
	public:
		explicit TextComp(const std::string& textPath, const std::string& text, const Color& color,  const Vector2& offset = Vector2(0.f,0.f));
		~TextComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();

		void SetText(const std::string& newText);
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;


	protected:
		void InternalRenderEditor() override {}
#endif

	private:
		std::string m_TextPath;
		std::string m_Text;
		Color m_Color;
		
		unsigned int m_Font;
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
