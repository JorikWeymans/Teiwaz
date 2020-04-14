#pragma once
#include <string>
#include <vector>

//E Prefix to indicate that this is only a script for the editor
namespace tyr
{

	class Texture;
	class SceneManager;
	class ESceneHolder final
	{
		struct SceneItem
		{
			explicit SceneItem(const std::string& _path, const std::string& _name)
				: path(_path), name(_name), isHovered(false) {}
			std::string path;
			std::string name;
			bool isHovered;
		};
		
	public:
		explicit ESceneHolder(const std::string& dataFolder, SceneManager* pContentManager);
		~ESceneHolder() = default;
		void RenderEditor();

	private:
		std::string m_SceneFolder;
		std::vector<SceneItem> m_Files;
		Texture* m_pTexture;
		SceneManager* m_pContentManager; //weak ptr
	public:

		ESceneHolder(const ESceneHolder&) = delete;
		ESceneHolder(ESceneHolder&&) = delete;
		ESceneHolder& operator=(const ESceneHolder&) = delete;
		ESceneHolder& operator=(ESceneHolder&&) = delete;
	};
}

