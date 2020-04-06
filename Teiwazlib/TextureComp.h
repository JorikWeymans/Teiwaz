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
		explicit TextureComp(const std::wstring& texturePath, const PivotMode& pivotMode = PivotMode::TopLeft, const Rect& rect = Rect());
		~TextureComp() override;
		
		void Initialize() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();
		void SetSourceRect(const Rect& rect);

	private:
		std::wstring m_TexturePath;
		Texture* m_pTexture; //Weak pointer
		TransformComp const* m_pTransform; //Weak pointer
		Vector2 m_Pivot;
		Rect m_SrcRect;
	public:
		TextureComp() = delete;
		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator=(const TextureComp&) = delete;
		TextureComp& operator=(TextureComp&&) = delete;

	};
}
