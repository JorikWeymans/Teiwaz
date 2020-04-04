#include "tyrpch.h"
#include "TransformComp.h"



tyr::TransformComp::TransformComp(const transform& transform)
	: m_Transform(transform)
{
}
tyr::TransformComp::TransformComp(const Vector2& position)
	: TransformComp(transform(position))
{
}
tyr::TransformComp::TransformComp(const Vector2& position, const Vector2& scale, float rotation)
	:TransformComp(transform(position, scale, rotation))
{
}

void tyr::TransformComp::Update()
{
}
void tyr::TransformComp::FixedUpdate()
{
}
void tyr::TransformComp::Render() const
{
}

const tyr::transform& tyr::TransformComp::GetTransform() const
{
	return m_Transform;
}

const tyr::Vector2& tyr::TransformComp::GetPosition() const
{
	return m_Transform.position;
}

const tyr::Vector2& tyr::TransformComp::GetScale() const
{
	return m_Transform.scale;
}

float tyr::TransformComp::GetRotation() const
{
	return m_Transform.rotation;
}
