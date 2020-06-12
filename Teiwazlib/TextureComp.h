#pragma once
#include "BaseComponent.h"
#include "TyrEnums.h"
#include "Vectors.h"

namespace tyr
{
	class TransformComp;
	class Texture;
	class TextureComp final: public BaseComponent
	{
	public:
		explicit TextureComp(TextureID id, const PivotMode& pivotMode = PivotMode::TopLeft,
							const Rect& rect = Rect(), const Vector2& offset = Vector2(0.f, 0.f));
			explicit TextureComp(TextureID id, const Vector2& pivot ,
				const Rect& rect, const Vector2& offset);
		~TextureComp() override;
		
		void Initialize() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();
		void SetSourceRect(const Rect& rect);

#ifdef EDITOR_MODE
		void EditorTexture(std::string& name);
		void EditorPosition(std::string& name);
		void EditorOffset(std::string& name);
		void Save(BinaryWriter& writer) override;

	protected:
		void InternalRenderEditor() override;
#endif
	private:
		TextureID m_TextureID;
		TransformComp const* m_pTransform; //Weak pointer
		Vector2 m_Pivot;
		Rect m_SrcRect;
		Vector2 m_Offset;

#ifdef EDITOR_MODE

#endif
	public:
		TextureComp() = delete;
		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator=(const TextureComp&) = delete;
		TextureComp& operator=(TextureComp&&) = delete;

	};
}
