#include "tyrpch.h"
#include "Vectors.h"

tyr::Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

tyr::Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{
}

tyr::Vector3::Vector3(const Vector2& vec)
	:x(vec.x) , y(vec.y), z(0.f)
{
}
