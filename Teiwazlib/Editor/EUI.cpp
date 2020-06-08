#include "../tyrpch.h"

#ifdef EDITOR_MODE
#include "EUI.h"
#include "../SceneManager.h"
#include "../GameContext.h"
#include "../TeiwazEngine.h"
#include "EMenuBar.h"
#include "EWindow.h"
#include <algorithm>
#include "EWindowSceneView.h"
#include "EWindowInspector.h"
#include "EWindowSouth.h"
#include "EAnimation.h"
#include "EAnimator.h"
tyr::EUI::EUI(GameContext* pContext)
	: m_pContext(pContext)
	, m_pMenu(new EMenuBar(pContext))
	, m_pEAnimation(new EAnimation(pContext))
	, m_pEAnimator(new EAnimator())
{
	m_pContext->pEditorUI = this;
	
	m_pWindows.emplace_back(new EWindowSceneView(pContext));
	m_pWindows.emplace_back(new EWindowInspector(pContext));
	m_pWindows.emplace_back(new EWindowSouth(pContext));
}

tyr::EUI::~EUI()
{
	SAFE_DELETE(m_pMenu);
	SAFE_DELETE(m_pEAnimation);
	SAFE_DELETE(m_pEAnimator);
	
	std::for_each(m_pWindows.begin(), m_pWindows.end(), [](EWindow* w) { SAFE_DELETE(w); });
	m_pWindows.clear();
}

void tyr::EUI::RenderEditor()
{
	m_pMenu->RenderEditor();
	m_pEAnimation->RenderEditor();
	m_pEAnimator->RenderEditor();
	
	std::for_each(m_pWindows.begin(), m_pWindows.end(), [](EWindow* w) {w->RenderEditor(); });
	
}

#endif