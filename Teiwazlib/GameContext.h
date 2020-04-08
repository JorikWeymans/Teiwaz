#pragma once
namespace tyr
{
	class Time;
	class InputHandler;
	class Rect;
	class GameContext final
	{
	public:
		explicit GameContext(Time* pTime, InputHandler* pInput, Rect* pGameSpace);
		~GameContext();
		
		Time* pTime;
		InputHandler* pInput;
		Rect* pGameSpace;
	public:
		GameContext(const GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		GameContext& operator=(const GameContext&) = delete;
		GameContext& operator=(GameContext&&) = delete;
	};


}
