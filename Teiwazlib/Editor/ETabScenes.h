#pragma once
#include "ETabItem.h"
#include <vector>
#ifdef EDITOR_MODE
namespace  tyr
{
	class GameContext;
	class ETabScenes final : public ETabItem
	{
	public:
		explicit ETabScenes(GameContext* pContext);
		virtual ~ETabScenes() = default;

	protected:
		
		 void PreRender() override;
		 void InternalRenderEditor() override;

	private:
		std::vector<TabItem> m_TabItems;
		TextureID m_Texture;
	public:
		ETabScenes(const ETabScenes&) = delete;
		ETabScenes(ETabScenes&&) = delete;
		ETabScenes& operator=(const ETabScenes&) = delete;
		ETabScenes& operator=(ETabScenes&&) = delete;
	};
}
#endif
