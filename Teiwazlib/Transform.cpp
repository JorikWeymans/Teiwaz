#include "tyrpch.h"
#include "Transform.h"

tyr::Transform::Transform(const Vector2& pos, const Vector2& scale, float rot)
	: position(pos), scale(scale), rotation(rot) {}

tyr::Transform::Transform(const Transform_POD& pod)
	: Transform(Vector2(pod.position), Vector2(pod.scale), pod.rotation) {}

tyr::Transform_POD tyr::Transform::ToPOD() const
{
	return Transform_POD{ position.ToPOD(), scale.ToPOD(), rotation};
}
