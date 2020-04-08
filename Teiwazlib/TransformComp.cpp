#include "tyrpch.h"
#include "TransformComp.h"
#include "TeiwazEngine.h"
#include "SceneObject.h"

tyr::TransformComp::TransformComp(const Transform& transform)
	: m_pTransform(new Transform(transform))
{
	
}
tyr::TransformComp::TransformComp(const Vector2& position)
	: TransformComp(Transform(position))
{
}
tyr::TransformComp::TransformComp(const Vector2& position, const Vector2& scale, float rotation)
	:TransformComp(Transform(position, scale, rotation))
{
}

tyr::TransformComp::~TransformComp()
{
	SAFE_DELETE(m_pTransform);
}

void tyr::TransformComp::Translate(float x, float y)
{
	m_pTransform->position.x += x;
	m_pTransform->position.y += y;
}

void tyr::TransformComp::Initialize()
{
	//TeiwazEngine::GameToEngineSpace(m_pSceneObject->GetGameContext(), &m_pTransform->position);
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

const tyr::Transform& tyr::TransformComp::GetTransform() const
{
	return *m_pTransform;
}

const tyr::Vector2& tyr::TransformComp::GetPosition() const
{
	return m_pTransform->position;
}

const tyr::Vector2& tyr::TransformComp::GetScale() const
{
	return m_pTransform->scale;
}

float tyr::TransformComp::GetRotation() const
{
	return m_pTransform->rotation;
}

tyr::Transform* tyr::TransformComp::GetTr()
{
	return m_pTransform;
}
