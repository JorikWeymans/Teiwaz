#include "tyrpch.h"

#ifdef USE_IM_GUI
#include "EUI.h"
#include "SceneManager.h"
#include "GameContext.h"
#include "TeiwazEngine.h"
#include "EMenuBar.h"
#include "EWindow.h"
#include <algorithm>
#include "EWindowSceneView.h"
#include "EWindowInspector.h"
#include "EWindowSouth.h"

tyr::EUI::EUI(GameContext* pContext)
	: m_pContext(pContext)
	, m_pMenu(new EMenuBar(pContext))
{
	m_pWindows.emplace_back(new EWindowSceneView(pContext));
	m_pWindows.emplace_back(new EWindowInspector(pContext));
	m_pWindows.emplace_back(new EWindowSouth(pContext));
}

tyr::EUI::~EUI()
{
	SAFE_DELETE(m_pMenu);
	std::for_each(m_pWindows.begin(), m_pWindows.end(), [](EWindow* w) { SAFE_DELETE(w); });
	m_pWindows.clear();
}

void tyr::EUI::RenderEditor()
{
	m_pMenu->RenderEditor();
	std::for_each(m_pWindows.begin(), m_pWindows.end(), [](EWindow* w) {w->RenderEditor(); });
	
}

#endif