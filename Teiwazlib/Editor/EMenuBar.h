#pragma once
#ifdef USE_IM_GUI
namespace tyr
{
	class GameContext;
	class Texture;
	class EAnimation;
	class EMenuBar
	{
	public:
		explicit EMenuBar(GameContext* pContext);
		~EMenuBar();
		
		void RenderEditor();
	private:
		GameContext* const m_pContext;
		Texture* m_pTexture;
		EAnimation* m_pEditorAni;
	public:
		EMenuBar(const EMenuBar&) = delete;
		EMenuBar(EMenuBar&&) = delete;
		EMenuBar& operator=(const EMenuBar&) = delete;
		EMenuBar& operator=(EMenuBar&&) = delete;
	};
}
#endif