#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class TransformComp;
	class TextureComp final: public BaseComponent
	{
	public:
		TextureComp(const std::wstring& texturePath);
		~TextureComp() override;
		
		void Initialize() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();


	private:
		std::wstring m_TexturePath;
		SDXL::SDXLImage* m_pTexture;
		const TransformComp* m_pTranform; //Weak pointer
	public:
		TextureComp() = delete;
		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator=(const TextureComp&) = delete;
		TextureComp& operator=(TextureComp&&) = delete;

	};
}
