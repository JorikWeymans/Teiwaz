#pragma once
#ifdef USE_IM_GUI
#include "EWindow.h"
namespace tyr
{
	class EWindowSceneView final : public EWindow
	{
	public:
		explicit EWindowSceneView(GameContext* pContext);
		~EWindowSceneView() = default;
	protected:
		void PreRender() override;
		void InternalRenderEditor() override;

	private:
		SDXL::Float2 m_Pos, m_Size;
	public:

		EWindowSceneView(const EWindowSceneView&) = delete;
		EWindowSceneView(EWindowSceneView&&) = delete;
		EWindowSceneView& operator=(const EWindowSceneView&) = delete;
		EWindowSceneView& operator=(EWindowSceneView&&) = delete;

	
	};

	
}
#endif