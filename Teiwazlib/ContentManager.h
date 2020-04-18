#pragma once
#include <vector>

#define CONTENT_MANAGER ContentManager::GetInstance()
namespace tyr
{
	class Font;
	class Texture;
	class ContentManager final
	{
	public:
		static ContentManager* GetInstance();

		void Initialize(const std::string& dataFolder, const std::string& sceneFolder = "Scenes/", const std::string& animationFolder = "Animations/");
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		Texture* GetTexture(TextureID id);
		
		FontID LoadFont(const std::string& path);
		Font const* GetFont(FontID id);

		AnimationID LoadAnimation(const std::string& AnimationName);
		
	
		std::string GetDataFolder() const;
	private:
		ContentManager();
		~ContentManager();
		
		static ContentManager* m_pInstance;
		bool m_IsInitialized;
		std::string m_DataFolder;
		
		std::vector<Texture*> m_pTextures;
		std::vector<Font*>    m_pFonts;

	public:
		ContentManager(const ContentManager&) = delete;
		ContentManager(ContentManager&&) = delete;
		ContentManager& operator=(const ContentManager&) = delete;
		ContentManager& operator=(ContentManager&&) = delete;
	};


}
