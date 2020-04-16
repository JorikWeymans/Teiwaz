#pragma once

#ifdef USE_IM_GUI
#include <string>
#include <vector>
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

#endif
