#include "tyrpch.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComp.h"
#include <algorithm>

int tyr::SceneObject::counter = 0;
tyr::SceneObject::SceneObject(const tyr::Transform& transform, const std::string& name)
	: m_pComponents(std::vector<BaseComponent*>())
	, m_pChilds(std::vector<SceneObject*>())
	, m_pParent(nullptr)
	, m_pTransform(new TransformComp(transform))
	, m_IsDestroyed(false)
	, m_name(name)
	, m_pContext(nullptr)
{
	counter++;
}

tyr::SceneObject::~SceneObject()
{
	SAFE_DELETE(m_pTransform);
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](BaseComponent* b) {SAFE_DELETE(b)});
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [](SceneObject* s) {SAFE_DELETE(s)});
}

void tyr::SceneObject::Update()
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->Update();
		});

	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
			b->Update();
	});
}

void tyr::SceneObject::FixedUpdate()
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->FixedUpdate();
		});

	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
	{
		if(!m_IsDestroyed)
		b->FixedUpdate();
	});
}
#ifdef USE_IM_GUI
void tyr::SceneObject::Debug()
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->Debug();
		});

	
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
		{
			if (!m_IsDestroyed)
				b->Debug();
		});
}

void tyr::SceneObject::RenderEditor()
{

	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
			if (!m_IsDestroyed)
				s->RenderEditor();
		});


	
	m_pTransform->RenderEditor();
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](BaseComponent* b)
		{
			if (!m_IsDestroyed)
				b->RenderEditor();
		});
}
#endif

void tyr::SceneObject::Render() const
{
	std::for_each(m_pChilds.begin(), m_pChilds.end(), [&](SceneObject* s)
		{
		if (!m_IsDestroyed)
			s->Render();
		});
	
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

void tyr::SceneObject::AddChild(SceneObject* pChild)
{
	auto found = std::find(m_pChilds.begin(), m_pChilds.end(), pChild);
	if (found == m_pChilds.end())
	{
		pChild->m_pContext = m_pContext;
		pChild->Initialize();
		pChild->m_pParent = this;
		m_pChilds.emplace_back(pChild);

	}
	
}

tyr::TransformComp* tyr::SceneObject::GetTransform() const
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

void tyr::SceneObject::Initialize()
{
	m_pTransform->m_pSceneObject = this;
	m_pTransform->Initialize();
}
