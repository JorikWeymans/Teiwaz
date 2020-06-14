#include "tyrpch.h"
#include "GameState.h"

void tyr::GameState::ResetScoreP1()
{
	m_ScoreP1 = 0;
}

void tyr::GameState::IncreaseScoreP1() noexcept
{
	m_ScoreP1++;
}
