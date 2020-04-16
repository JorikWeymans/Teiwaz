#pragma once
#include "ETabItem.h"
#include <vector>
#ifdef USE_IM_GUI
namespace  tyr
{
	class GameContext;
	class Texture;
	class ETabScenes final : public ETabItem
	{
	private:
		struct SceneItem
		{
			explicit SceneItem(const std::string& _path, const std::string& _name)
				: path(_path), name(_name), isHovered(false) {}
			std::string path;
			std::string name;
			bool isHovered;
		};
	public:
		explicit ETabScenes(GameContext* pContext);
		virtual ~ETabScenes() = default;

	protected:
		
		 void PreRender() override;
		 void InternalRenderEditor() override;

	private:
		std::string m_SceneFolder;
		std::vector<SceneItem> m_Files;
		Texture* m_pTexture;
	public:
		ETabScenes(const ETabScenes&) = delete;
		ETabScenes(ETabScenes&&) = delete;
		ETabScenes& operator=(const ETabScenes&) = delete;
		ETabScenes& operator=(ETabScenes&&) = delete;
	};
}
#endif
