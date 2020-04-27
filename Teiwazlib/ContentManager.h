#pragma once
#include <vector>

#define CONTENT_MANAGER ContentManager::GetInstance()
namespace tyr
{
	struct TabItem;
	class Font;
	class Texture;
	class Animation;
	class ContentManager final
	{
	public:
		static ContentManager* GetInstance();

		void Initialize(const std::string& dataFolder, 
							const std::string& sceneFolder = "Scenes/", 
							const std::string& animationFolder = "Animations/", 
							const std::string& textureFolder = "Textures/");

		//void InitialzeFormFile(const std::string& File);
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		FontID LoadFont(const std::string& path);
		AnimationID LoadAnimation(const std::string& fileName);

		Texture* GetTexture(TextureID id);
		Font const* GetFont(FontID id);
		Animation* GetAnimation(AnimationID id);
		Animation* GetAnimation(std::string& name); //this does not load the animation, returns pointer to an existing animation (else nullptr)
		
		std::vector<TabItem> GetAnimationsInFolder() const; //Should not be in the program's hot code
		
		
		std::string GetDataFolder() const;

#ifdef USE_IM_GUI
		void RenderEditor(); //called in EMenuBar RenderEditor()
#endif
	private:
		ContentManager();
		~ContentManager();
		
		static ContentManager* pInstance;
		bool m_IsInitialized;
		std::string m_DataFolder, m_SceneFolder, m_AnimationFolder, m_TextureFolder;
		
		std::vector<Texture*> m_pTextures;
		std::vector<Font*>    m_pFonts;
		std::vector<Animation*> m_pAnimations;

#ifdef USE_IM_GUI

		void TextureWindow();
		
		char m_CharDataPath[256] {};
		char m_CharSceneFolder[30] {};
		char m_CharAnimationFolder[30] {};
		char m_CharTextureFolder[30] {};
		
#endif
		
	public:
		ContentManager(const ContentManager&) = delete;
		ContentManager(ContentManager&&) = delete;
		ContentManager& operator=(const ContentManager&) = delete;
		ContentManager& operator=(ContentManager&&) = delete;
	};


}
