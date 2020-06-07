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

		void CreateTabItems() override;
		
	protected:
		 void PreTabRender() override;
		 void PostTabRender() override;
		 void OnItemDoubleClick(TabItem& clickedItem) override;
	public:
		ETabScenes(const ETabScenes&) = delete;
		ETabScenes(ETabScenes&&) = delete;
		ETabScenes& operator=(const ETabScenes&) = delete;
		ETabScenes& operator=(ETabScenes&&) = delete;
	};
}
#endif
