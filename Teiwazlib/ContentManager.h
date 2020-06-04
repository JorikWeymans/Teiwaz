#pragma once
#include <vector>

#define CONTENT_MANAGER ContentManager::GetInstance()
namespace tyr
{
	class GameContext;
	struct TabItem;
	class Font;
	class Texture;
	class Animation;
	class TextureComp;
	class CMTextures;
	class CMScenes;
	class Scene;
	class ContentManager final
	{
	private:
		enum class ContentWindow : int
		{
			None = -1, Textures = 0, Scenes = 1, Animations = 2,
		};
		
	public:
		static ContentManager* GetInstance();
		
		//This file is an engine predetermined file
		void Initialize(GameContext* pContext); 
		
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		FontID LoadFont(const std::string& path);
		AnimationID LoadAnimation(const std::string& fileName);

		_NODISCARD Texture*    GetTexture(TextureID id) const; 
		_NODISCARD Font const* GetFont(FontID id);
		_NODISCARD Animation*  GetAnimation(AnimationID id);
		_NODISCARD Animation*  GetAnimation(const std::string& fileName);
		_NODISCARD AnimationID GetAnimationID(const std::string& fileName);
		_NODISCARD Animation*  GetAnimation(std::string& name); //this does not load the animation, returns pointer to an existing animation (else nullptr)
		_NODISCARD std::vector<TabItem> GetAnimationsInFolder() const; //Should not be in the program's hot code

		const std::string& GetDataFolder() const noexcept { return m_DataFolder; }
		std::string GetAbsoluteSceneFolder() const { return m_DataFolder + m_SceneFolder; }
		_NODISCARD CMScenes* GetScenes() const noexcept { return m_pCMScenes; }
		_NODISCARD Scene* GetCurrentScene() const noexcept;
		void SetCurrentScene(SceneID id);

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
		
		CMTextures* m_pCMTextures;
		CMScenes* m_pCMScenes;
		std::vector<Font*>    m_pFonts;
		std::vector<Animation*> m_pAnimations;
		GameContext* m_pContext; //Weak ptr
#ifdef EDITOR_MODE
		
		bool m_OpenContentManager = false, m_OpenFilePathSettings = false, m_AreContentSettingsOpen = true;
		ContentWindow m_SelectedContentWindow;
		void EMainMenuBarItem();
		void EMainWindow();
		void EMenuBar();
		void EContentSelectorWindow();
		
		void ESettingsContentPath();

		void ERenderContentWindow() const;
		
		char m_CharDataPath[256] {}, m_CharSceneFolder[30] {}, m_CharAnimationFolder[30] {}, m_CharTextureFolder[30] {};
		
#endif
		
	public:
		ContentManager(const ContentManager&) = delete;
		ContentManager(ContentManager&&) = delete;
		ContentManager& operator=(const ContentManager&) = delete;
		ContentManager& operator=(ContentManager&&) = delete;
	};


}
