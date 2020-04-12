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

		void Initialize(const std::wstring& dataFolder);
		static void Destroy();

		Texture* LoadTexture(const std::wstring& path);
		Font const* LoadFont(const std::wstring& path);
		const std::wstring& GetDataFolderW() const { return m_DataFolder; }
		std::string GetDataFolder() const;
	private:
		ContentManager();
		~ContentManager();
		
		static ContentManager* m_pInstance;
		bool m_IsInitialized;
		std::wstring m_DataFolder;
		
		std::vector<Texture*> m_pTextures;
		std::vector<Font*>    m_pFonts;

	public:
		ContentManager(const ContentManager&) = delete;
		ContentManager(ContentManager&&) = delete;
		ContentManager& operator=(const ContentManager&) = delete;
		ContentManager& operator=(ContentManager&&) = delete;
	};


}
