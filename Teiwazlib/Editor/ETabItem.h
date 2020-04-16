#pragma once

#ifdef USE_IM_GUI
namespace  tyr
{
	class GameContext;
	class ETabItem
	{
	public:
		virtual ~ETabItem() = default;
		void RenderEditor();
	protected:
		explicit ETabItem(const char* name, GameContext* pContext);
		virtual void PreRender() = 0;
		virtual void InternalRenderEditor() = 0;


		const char* m_Name;
		GameContext* const m_pContext; //Weak ptr
	public:
		ETabItem(const ETabItem&) = delete;
		ETabItem(ETabItem&&) = delete;
		ETabItem& operator=(const ETabItem&) = delete;
		ETabItem& operator=(ETabItem&&) = delete;
	};
}
#endif
