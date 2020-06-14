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
	enum class ColliderDirection : UINT
	{
		Top,
		Left,
		Bot,
		Right
	};
	enum class Tag : BYTE
	{
		None       = 0 << 0,
		Default    = 1 << 0,
		Player     = 1 << 1,
		Enemy      = 1 << 2,
		Bubble     = 1 << 3,
		Background = 1 << 4,
		All        = 0xFF,

	};
	enum class ButtonType : UINT
	{
		QuitGame,
		Start,
	};
	enum class FoodType : UINT
	{
		Melon,
		Fries
	};
	
	Tag operator<<(const Tag& tag, const int& rhs);
	Tag operator++(tyr::Tag& tag, int);
	Tag operator>>(const Tag& tag, const int& rhs);
	Tag operator--(tyr::Tag& tag, int);


}
