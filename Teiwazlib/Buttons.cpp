#include "tyrpch.h"
#include "Buttons.h"
#include "TeiwazEngine.h"
#include "GameContext.h"
#include "SceneManager.h"
tyr::Button::Button(GameContext const* pContext)
	: m_pContext(pContext)
{
}

tyr::QuitButton::QuitButton(GameContext const* pContext)
	: Button(pContext)
{
}

void tyr::QuitButton::Execute()
{
	TeiwazEngine::WantQuit = true;
}

tyr::LoadScene1Button::LoadScene1Button(GameContext const* pContext)
	: Button(pContext)
{
}

void tyr::LoadScene1Button::Execute()
{
	m_pContext->pSceneManager->SetCurrentScene(1);
}
