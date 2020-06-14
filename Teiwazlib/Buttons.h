#pragma once
namespace tyr
{
	class GameContext;
	class Button
	{
	public:
		explicit Button(GameContext const* pContext);
		virtual ~Button() = default;
		virtual void Execute() = 0;
	protected:
		GameContext const* m_pContext;
	};

	class QuitButton : public Button
	{
	public:
		explicit QuitButton(GameContext const* pContext);
		void Execute() override;
	};

	class LoadScene1Button : public Button
	{
	public:
		explicit LoadScene1Button(GameContext const* pContext);
		void Execute() override;
	};

}

