#pragma once
#ifdef USE_IM_GUI
#include "EWindow.h"
namespace tyr
{
	class EWindowInspector final : public EWindow
	{
	public:
		EWindowInspector(GameContext* pContext);
		~EWindowInspector() = default;
	protected:
		void PreRender() override;
		void InternalRenderEditor() override;

	public:

		EWindowInspector(const EWindowInspector&) = delete;
		EWindowInspector(EWindowInspector&&) = delete;
		EWindowInspector& operator=(const EWindowInspector&) = delete;
		EWindowInspector& operator=(EWindowInspector&&) = delete;
	};
}
#endif