#pragma once
namespace tyr
{
	class Time final
	{
	public:
		Time() = default;
		~Time() = default;
		
		float deltaTime = 0.016f; //first frame gets time equal to 60 fps 
		float fixedDeltaTime = 0.02f; //first frame gets time equal to 50 fps;
		
	public:
		Time(const Time&) = delete;
		Time(Time&&) = delete;
		Time& operator=(const Time&) = delete;
		Time& operator=(Time&&) = delete;
	};


}
