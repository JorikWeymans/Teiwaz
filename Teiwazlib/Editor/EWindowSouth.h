#pragma once
#include <vector>
#ifdef USE_IM_GUI
#include "EWindow.h"
namespace tyr
{
	class GameContext;
	class ETabItem;
	class EWindowSouth final: public EWindow
	{
	public:
		explicit EWindowSouth(GameContext* pContext);
		~EWindowSouth();
		
	protected:
		void PreRender() override;
		void InternalRenderEditor() override;

	private:
		std::vector<ETabItem*> m_pTabItems;
	public:
		EWindowSouth(const EWindowSouth&) = delete;
		EWindowSouth(EWindowSouth&&) = delete;
		EWindowSouth& operator=(const EWindowSouth&) = delete;
		EWindowSouth& operator=(EWindowSouth&&) = delete;

	};


}

#endif