#pragma once
#ifdef EDITOR_MODE
#include <vector>

namespace tyr
{
	class SceneManager;
	class GameContext;
	class EMenuBar;
	class EWindow;
	class EUI final
	{
	public:
		explicit EUI(GameContext* pContext);
		~EUI();
		
		
		void RenderEditor();
	private:
		GameContext* const m_pContext; //Weak ptr

		EMenuBar* m_pMenu;
		std::vector<EWindow*> m_pWindows;
	public:
		EUI(const EUI&) = delete;
		EUI(EUI&&) = delete;
		EUI& operator=(const EUI&) = delete;
		EUI& operator=(EUI&&) = delete;
	};
}

#endif
