#include "tyrpch.h"
#include "Vectors.h"
#include "TyrEnums.h"
tyr::Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

tyr::Vector2::Vector2(const PivotMode& pMode)
	: x(0.f), y(0.f)
{
	switch (pMode)
	{
	case PivotMode::TopLeft: // no need to do this (by default it its 0 0
		break;
	case PivotMode::TopRight:
		x = 1.f;
		y = 0.f;
		break;
	case PivotMode::BotLeft:
		x = 0.f;
		y = 1.f;
		break;
	case PivotMode::BotRight:
		x = 1.f;
		y = 1.f;
		break;
	case PivotMode::Center:
		x = .5f;
		y = .5f;
		break;
	default:
		;
	}
	
	
}

tyr::Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{
}

tyr::Vector3::Vector3(const Vector2& vec)
	:x(vec.x) , y(vec.y), z(0.f)
{
}
