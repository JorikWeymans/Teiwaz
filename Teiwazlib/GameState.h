#pragma once
namespace tyr
{
	class GameState final
	{
	public:
		explicit GameState() = default;
		~GameState() = default;

		void ResetScoreP1();
		void AddToScore(UINT amount) noexcept;
		_NODISCARD UINT GetScorePlayer1() const noexcept { return m_ScoreP1; }
	private:
		UINT m_ScoreP1;
		

	};
}

