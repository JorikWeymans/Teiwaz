#pragma once
namespace tyr
{
	class GameContext;
	class GameState final
	{
	public:
		explicit GameState() = default;
		~GameState() = default;

		void ResetScoreP1();
		void AddToScore(UINT amount) noexcept;
		_NODISCARD UINT GetScorePlayer1() const noexcept { return m_ScoreP1; }


		void ResetEnemies() { m_NmrOfEnemies = 0; }
		void AddEnemy();
		void RemoveEnemy(GameContext const* pContext);
	private:
		UINT m_ScoreP1;
		UINT m_NmrOfEnemies;
		

	};
}

