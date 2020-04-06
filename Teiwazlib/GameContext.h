#pragma once
namespace tyr
{
	class Time;
	class InputHandler;
	class GameContext final
	{
	public:
		explicit GameContext(Time* pTime, InputHandler* pInput);
		~GameContext();
		
		Time* pTime;
		InputHandler* pInput;
	public:
		GameContext(const GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		GameContext& operator=(const GameContext&) = delete;
		GameContext& operator=(GameContext&&) = delete;
	};


}
