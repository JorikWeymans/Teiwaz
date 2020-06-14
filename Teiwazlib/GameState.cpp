#include "tyrpch.h"
#include "GameState.h"

void tyr::GameState::ResetScoreP1()
{
	m_ScoreP1 = 0;
}

void tyr::GameState::AddToScore(UINT amount) noexcept
{
	m_ScoreP1 += amount;
}
