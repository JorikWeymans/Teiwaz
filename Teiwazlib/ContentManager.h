#pragma once
#include <vector>

#define CONTENT_MANAGER ContentManager::GetInstance()
namespace tyr
{
	struct TabItem;
	class Font;
	class Texture;
	class Animation;
	class TextureComp;
	class TextureManager;
	class ContentManager final
	{
	public:
		static ContentManager* GetInstance();

		void Initialize(const std::string& dataFolder, 
							const std::string& sceneFolder = "Scenes/",
							const std::string& textureFolder = "Textures/",
							const std::string& fontFolder = "Fonts/",
							const std::string& animationFolder = "Animations/");
		
		//This file is an engine predetermined file
		void InitializeFromFile(); 
		
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		FontID LoadFont(const std::string& path);
		AnimationID LoadAnimation(const std::string& fileName);

		Texture* GetTexture(TextureID id) const; 
		Font const* GetFont(FontID id);
		Animation* GetAnimation(AnimationID id);
		Animation* GetAnimation(const std::string& fileName);
		AnimationID GetAnimationID(const std::string& fileName);
		Animation* GetAnimation(std::string& name); //this does not load the animation, returns pointer to an existing animation (else nullptr)
		
		std::vector<TabItem> GetAnimationsInFolder() const; //Should not be in the program's hot code
		
		
		std::string GetDataFolder() const;

#ifdef EDITOR_MODE
		void RenderEditor(); //called in EMenuBar RenderEditor()
		void EditorTextureSelector(const char* imGuiID, TextureID& textureID);
		void Save();

		friend TextureComp;
#endif
	private:
		ContentManager();
		~ContentManager();
		void LoadAnimation(const std::string& fileName, AnimationID arrayIndex);

		
		static ContentManager* pInstance;
		bool m_IsInitialized;
		std::string m_DataFolder, m_SceneFolder, m_TextureFolder, m_FontFolder, m_AnimationFolder ;
		
		TextureManager* m_pTextures;
		std::vector<Font*>    m_pFonts;
		std::vector<Animation*> m_pAnimations;

#ifdef EDITOR_MODE

		void SceneWindow();
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
