#include "tyrpch.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
tyr::SceneManager::SceneManager(GameContext* pContext)
	: m_pContext(pContext)
	, m_pScenes(std::vector<Scene*>())
{
}

tyr::SceneManager::~SceneManager()
{
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [](Scene* s) {SAFE_DELETE(s)});
}

void tyr::SceneManager::AddScene(Scene* pScene)
{
	pScene->m_pContext = m_pContext;
	pScene->Initialize();

	m_pScenes.emplace_back(pScene);
	
}

void tyr::SceneManager::Update()
{
	m_pScenes[0]->Update();
}

void tyr::SceneManager::FixedUpdate()
{
	m_pScenes[0]->FixedUpdate();
}

void tyr::SceneManager::Render() const
{
	SDXL_Clear();
	
	m_pScenes[0]->Render();

	SDXL_Present();
	
}
