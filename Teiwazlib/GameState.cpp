#include "tyrpch.h"
#include "GameState.h"
#include "GameContext.h"
#include "SceneManager.h"

void tyr::GameState::ResetScoreP1()
{
	m_ScoreP1 = 0;
}

void tyr::GameState::AddToScore(UINT amount) noexcept
{
	m_ScoreP1 += amount;
}

void tyr::GameState::AddEnemy()
{
	m_NmrOfEnemies++;
}

void tyr::GameState::RemoveEnemy(GameContext const* pContext)
{
	m_NmrOfEnemies--;
	if(m_NmrOfEnemies == 0)
	{
		auto sceneName = pContext->pSceneManager->GetCurrentSceneName();
		if (sceneName == "GameScene1")
			pContext->pSceneManager->SetCurrentScene("GameScene2");
		
		
	}
}
