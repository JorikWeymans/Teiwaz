#include "tyrpch.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComp.h"
#include <algorithm>

tyr::SceneObject::SceneObject(const tyr::Transform& transform)
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
#ifdef USE_IM_GUI
void tyr::SceneObject::Debug()
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
		{
			if (!m_IsDestroyed)
				b->Debug();
		});
}
#endif

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

tyr::Transform* tyr::SceneObject::Transform()
{
	return m_pTransform->GetTr();
	
}

void tyr::SceneObject::SetPositionY(float y)
{
	m_pTransform->GetTr()->position.y = y;
	
}

void tyr::SceneObject::Translate(float x, float y)
{
	m_pTransform->Translate(x, y);
}

const tyr::GameContext* tyr::SceneObject::GetGameContext() const
{
	return m_pContext;
}

void tyr::SceneObject::Initialize()
{
	m_pTransform->m_pSceneObject = this;
	m_pTransform->Initialize();
}
