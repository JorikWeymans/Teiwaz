#pragma once
#include <vector>

#define CONTENT_MANAGER ContentManager::GetInstance()
namespace tyr
{
	class Font;
	class Texture;
	class Animation;
	class ContentManager final
	{
	public:
		static ContentManager* GetInstance();

		void Initialize(const std::string& dataFolder, const std::string& sceneFolder = "Scenes/", const std::string& animationFolder = "Animations/");
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		FontID LoadFont(const std::string& path);
		AnimationID LoadAnimation(const std::string& fileName);

		Texture* GetTexture(TextureID id);
		Font const* GetFont(FontID id);
		Animation* GetAnimation(AnimationID id);
		
	
		std::string GetDataFolder() const;
	private:
		ContentManager();
		~ContentManager();
		
		static ContentManager* pInstance;
		bool m_IsInitialized;
		std::string m_DataFolder, m_SceneFolder, m_AnimationFolder;
		
		std::vector<Texture*> m_pTextures;
		std::vector<Font*>    m_pFonts;
		std::vector<Animation*> m_pAnimations;
		

		
		
	public:
		ContentManager(const ContentManager&) = delete;
		ContentManager(ContentManager&&) = delete;
		ContentManager& operator=(const ContentManager&) = delete;
		ContentManager& operator=(ContentManager&&) = delete;
	};


}
