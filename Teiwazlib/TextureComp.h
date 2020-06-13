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
							const Rect& rect = Rect(), const Vector2& offset = Vector2(0.f, 0.f), bool isTextureMap = false,
							bool isRepeating = false, int repeatX = 1, int repeatY = 1);
			explicit TextureComp(TextureID id, const Vector2& pivot ,
				const Rect& rect, const Vector2& offset, bool isTextureMap, bool isRepeating, int repeatX, int repeatY);
		~TextureComp() override;
		
		void Initialize() override;
		
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Destroy();
		void SetSourceRect(const Rect& rect);
		void SetRepeatingX(int value) noexcept { m_RepeatX = value; }
#ifdef EDITOR_MODE

		void Save(BinaryWriter& writer) override;

	protected:
		void InternalRenderEditor() override;
#endif
	private:
		TextureID m_TextureID;
		TransformComp const* m_pTransform; //Weak pointer
		Vector2 m_Pivot;

		bool m_IsTextureMap;
		Rect m_SrcRect;
		Vector2 m_Offset;

		bool m_RepeatTexture;
		int m_RepeatX, m_RepeatY; //Keep this together used in ImGui with dragInt2
		void ResetRenderParameters();
#ifdef EDITOR_MODE
		void EditorTexture(std::string& name, const std::string& uID);
		void EditorPosition(std::string& name, const std::string& uID);
		void EditorOffset(std::string& name, const std::string& uID);
		void EditorIsTextureMap(std::string& name, const std::string uID);
		void EditorRenderParameters(std::string& name, const std::string& uID);
		
		void EditorIsRepeatedTexture(std::string& name, const std::string& uID);
		void EditorRepeatParameters(std::string& name, const std::string& uID);
#endif
	public:
		TextureComp() = delete;
		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator=(const TextureComp&) = delete;
		TextureComp& operator=(TextureComp&&) = delete;

	};
}
