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
	enum class Tag : BYTE
	{
		None       = 0x00,
		Default    = 0x01,
		Player     = 0x02,
		Enemy      = 0x04,
		Bubble     = 0x08,
		Background = 0x10,
		All        = 0xFF,

	};

	Tag operator<<(const Tag& tag, const int& rhs);
	Tag operator++(tyr::Tag& tag, int);
	Tag operator>>(const Tag& tag, const int& rhs);
	Tag operator--(tyr::Tag& tag, int);


}
