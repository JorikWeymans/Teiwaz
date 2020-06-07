#pragma once
#include "ETabItem.h"
#include <vector>
#ifdef EDITOR_MODE
namespace tyr
{
	class ETabAnimators final : public ETabItem
	{
	public:
		explicit ETabAnimators(GameContext* pContext);
		virtual ~ETabAnimators() = default;
		void CreateTabItems() override;
		
	protected:
		void PreTabRender() override;
		void PostTabRender() override;
		void OnItemDoubleClick(TabItem& clickedItem) override;

	public:
		ETabAnimators(const ETabAnimators&) = delete;
		ETabAnimators(ETabAnimators&&) = delete;
		ETabAnimators& operator=(const ETabAnimators&) = delete;
		ETabAnimators& operator=(ETabAnimators&&) = delete;
	};
}

#endif