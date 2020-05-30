#pragma once
namespace tyr
{
	enum class PivotMode
	{
		TopLeft,
		TopCenter,
		TopRight,
		
		CenterLeft,
		Center,
		CenterRight,
		
		BotLeft,
		BotCenter,
		BotRight,
	};

	enum class Tag : unsigned char
	{
		Default    = 0x1,
		Player     = 0x2,
		Enemy      = 0x4,
		Bubble     = 0x8,
		Background = 0x10,
		
	};
}
