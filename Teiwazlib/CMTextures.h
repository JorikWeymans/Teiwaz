#pragma once
#include <vector>

namespace tyr
{
	class BinaryWriter;
	class ContentManager;
	class Texture;
	
	class CMTextures final
	{
	public:
		CMTextures() = default;
		~CMTextures();

		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Texture* pData) noexcept;
		
		TextureID LoadTexture(const std::string& dataFolder, const std::string& name);
		Texture* GetTexture(TextureID id) const;
		
#ifdef EDITOR_MODE
		void RenderEditor();
		void ETextureSelector(const char* imGuiID, TextureID& textureID); // Shows a drop down box with all the textures
		void SaveTextures(BinaryWriter& writer);
#endif

	private:
		std::vector<Texture*> m_pTextures;

		
#ifdef EDITOR_MODE
		void BtnRemoveSelectedTexture(int& selected);
		
		void ShowTextures(int& selectedTexture);

		void BtnDeleteTexture(int selectedTexture);
		void BtnMoveTextureUp(int& selectedTexture);
		void BtnMoveTextureDown(int& selectedTexture);

		void BtnLoadTexture();
#endif
	public:
		CMTextures(const CMTextures&) = delete;
		CMTextures(CMTextures&&) = delete;
		CMTextures& operator=(const CMTextures&) = delete;
		CMTextures& operator=(CMTextures&&) = delete;
	};


}
