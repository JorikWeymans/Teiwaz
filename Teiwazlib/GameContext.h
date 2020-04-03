#pragma once
namespace tyr
{
	class Time;
	
	class GameContext final
	{
	public:
		explicit GameContext(Time* pTime);
		~GameContext();
		
		Time* pTime;
		
	public:
		GameContext(const GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		GameContext& operator=(const GameContext&) = delete;
		GameContext& operator=(GameContext&&) = delete;
	};


}
