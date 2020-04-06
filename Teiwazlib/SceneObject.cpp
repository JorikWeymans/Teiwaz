#include "tyrpch.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComp.h"
#include <algorithm>

tyr::SceneObject::SceneObject(const transform& transform)
	: m_pComponents(std::vector<BaseComponent*>())
	, m_pTransform(new TransformComp(transform))
	, m_IsDestroyed(false)
	, m_pContext(nullptr)
{
}

tyr::SceneObject::~SceneObject()
{
	SAFE_DELETE(m_pTransform);
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](BaseComponent* b) {SAFE_DELETE(b)});
	
}

void tyr::SceneObject::Update()
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
			b->Update();
	});
}

void tyr::SceneObject::FixedUpdate()
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
		b->FixedUpdate();
	});
}

void tyr::SceneObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{if
		(!m_IsDestroyed)
		b->Render();
	});
}

void tyr::SceneObject::AddComponent(BaseComponent* pComp)
{
	auto found = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if(found == m_pComponents.end())
	{
		pComp->m_pSceneObject = this;
		pComp->Initialize();
		
		m_pComponents.emplace_back(pComp);
		
	}
}

const tyr::TransformComp* tyr::SceneObject::GetTransform() const
{
	return m_pTransform;
}

void tyr::SceneObject::Translate(float x, float y)
{
	m_pTransform->Translate(x, y);
}

const tyr::GameContext* tyr::SceneObject::GetGameContext() const
{
	return m_pContext;
}
