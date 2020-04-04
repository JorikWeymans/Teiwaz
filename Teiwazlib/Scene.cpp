#include "tyrpch.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>

tyr::Scene::Scene()
	: m_pContext(nullptr)
	, m_pSceneObjects(std::vector<SceneObject*>())
{
}

tyr::Scene::~Scene()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {SAFE_DELETE(s)});
}

void tyr::Scene::AddSceneObject(SceneObject* pObj)
{
	m_pSceneObjects.emplace_back(pObj);
}

void tyr::Scene::Update()
{
	//OutputDebugStringA("Update Scene\n");
}

void tyr::Scene::FixedUpdate()
{
	//OutputDebugStringA("FixedUpdate Scene\n");
}

void tyr::Scene::Render() const
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Render(); });
	//OutputDebugStringA("Render Scene\n");
}
