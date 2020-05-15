#pragma once
#include <vector>

namespace tyr
{
	class BinaryWriter;
	class ContentManager;
	class Texture;
	
	class TextureManager final
	{
	public:
		TextureManager() = default;
		~TextureManager();

		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Texture* pData);
		
		TextureID LoadTexture(const std::string& dataFolder, const std::string& name);
		Texture* GetTexture(TextureID id) const;
		
#ifdef USE_IM_GUI
		void RenderEditor();
		void ETextureSelector(const char* imGuiID, TextureID& textureID); // Shows a drop down box with all the textures
		void SaveTextures(BinaryWriter& writer);
#endif

	private:
		std::vector<Texture*> m_pTextures;

		
#ifdef USE_IM_GUI
		void BtnRemoveSelectedTexture(int& selected);
#endif
	public:
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;
	};


}
