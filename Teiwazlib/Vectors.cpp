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
	case PivotMode::TopLeft:     x = 0.0f; y = 0.0f; break;
	case PivotMode::TopCenter:   x = 0.5f; y = 0.0f; break;
	case PivotMode::TopRight:    x = 1.0f; y = 0.0f; break;
		
	case PivotMode::CenterLeft:  x = 0.0f; y = 0.5f; break;
	case PivotMode::Center:      x = 0.5f; y = 0.5f; break;
	case PivotMode::CenterRight: x = 1.0f; y = 0.5f; break;

	case PivotMode::BotLeft:     x = 0.0f; y = 1.0f; break;
	case PivotMode::BotCenter:   x = 0.5f; y = 1.0f; break;
	case PivotMode::BotRight:    x = 1.0f; y = 1.0f; break;
		
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
