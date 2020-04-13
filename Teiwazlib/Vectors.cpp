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

tyr::Vector2::Vector2(const Vector2_POD& pod)
	: Vector2(pod.x, pod.y)
{
}

tyr::Vector2::operator SDXL::SDXLVec2() const
{
	return SDXL::SDXLVec2{ x,y };
}

float tyr::Vector2::Cross(const Vector2& rhs) const
{
	return (x * rhs.y) - (y * rhs.x);
}

tyr::Vector2_POD tyr::Vector2::ToPOD() const
{
	return Vector2_POD{ x, y };
}

tyr::Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{
}
tyr::Vector3::Vector3(const Vector2& vec)
	:x(vec.x) , y(vec.y), z(0.f)
{
}

tyr::Rect::Rect()
	: m_Pos(0.f, 0.f), m_Width(0.f), m_Height(0.f)
	, m_IsSet(false)
{
}

tyr::Rect::Rect(float x, float y, float width, float height)
	: Rect( Vector2(x,y), width, height)

{
}
tyr::Rect::Rect(const Vector2& pos, float width, float height)
	: m_Pos(pos), m_Width(width), m_Height(height)
	, m_IsSet(true)
{
}
tyr::Rect::Rect(const Vector2& pos, const Vector2& dimension)
	: Rect(pos.x, pos.y, dimension.x, dimension.y)
{
}

tyr::Rect::Rect(const Rect_POD& pod)
	: Rect(pod.v.x, pod.v.y, pod.width, pod.height)
{
}

tyr::Rect::operator SDXL::SDXLRect() const
{
	return SDXL::SDXLRect{ m_Pos.x, m_Pos.y,m_Width, m_Height };
}

void tyr::Rect::Set(float x, float y, float width, float height)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Width = width;
	m_Height = height;
	
	m_IsSet = true;
}

void tyr::Rect::AdjustRectToPivot(Rect& theRect, PivotMode pivot)
{
	Vector2 temp = theRect.pos;
	switch (pivot)
	{
	case PivotMode::TopLeft:

		break;
	case PivotMode::TopCenter:
		temp.x -= theRect.width / 2;
		break;
	case PivotMode::TopRight:
		temp.x -= theRect.width;
		break;
	case PivotMode::CenterLeft:
		temp.y -= theRect.height / 2;
		break;
	case PivotMode::Center:
		temp.x -= theRect.width / 2;
		temp.y -= theRect.height / 2;
		break;
	case PivotMode::CenterRight:
		temp.x -= theRect.width;
		temp.y -= theRect.height / 2;
		break;
	case PivotMode::BotLeft:
		temp.y -= theRect.height;
		break;
	case PivotMode::BotCenter:
		temp.x -= theRect.width / 2;
		temp.y -= theRect.height;
		break;
	case PivotMode::BotRight:
		temp.x -= theRect.width;
		temp.y -= theRect.height;
		break;
	default:;
	}

	theRect.pos = temp;
}

tyr::Rect::operator bool() const
{
	return m_IsSet;
}

tyr::Rect_POD tyr::Rect::ToPOD() const
{

	return Rect_POD{ {m_Pos.x, m_Pos.y}, m_Width, m_Height };
}
