#pragma once
#ifdef USE_IM_GUI
namespace tyr
{
	class GameContext;
	class EMenuBar
	{
	public:
		explicit EMenuBar(GameContext* pContext);
		~EMenuBar() = default;
		
		void RenderEditor();
	private:
		GameContext* const m_pContext;
		
	public:
		EMenuBar(const EMenuBar&) = delete;
		EMenuBar(EMenuBar&&) = delete;
		EMenuBar& operator=(const EMenuBar&) = delete;
		EMenuBar& operator=(EMenuBar&&) = delete;
	};
}
#endif
