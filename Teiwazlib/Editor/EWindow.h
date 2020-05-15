#pragma once

#ifdef EDITOR_MODE
namespace  tyr
{
	class GameContext;
	class EWindow
	{
	public:
		
		virtual ~EWindow() = default;

		void RenderEditor();
	protected:
		explicit EWindow(const char* name, GameContext* pContext);
		virtual void PreRender() = 0;
		virtual void InternalRenderEditor() = 0;



		const char* m_Name;
		GameContext* const m_pContext; //Weak ptr
		SDXL_ImGuiWindowFlags m_Flags;
	public:
		EWindow(const EWindow&) = delete;
		EWindow(EWindow&&) = delete;
		EWindow& operator=(const EWindow&) = delete;
		EWindow& operator=(EWindow&&) = delete;
	};
}
#endif
