#include "tyrpch.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>

tyr::Scene::Scene(const std::string& name)
	: m_pContext(nullptr)
	, m_Name(name)
	, m_pSceneObjects(std::vector<SceneObject*>())
{
}

tyr::Scene::~Scene()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {SAFE_DELETE(s)});
}

void tyr::Scene::AddSceneObject(SceneObject* pObj)
{
	pObj->m_pContext = m_pContext;
	pObj->Initialize();
	
	m_pSceneObjects.emplace_back(pObj);
}

void tyr::Scene::Update()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Update(); });
}

void tyr::Scene::FixedUpdate()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->FixedUpdate(); });
}

#ifdef USE_IM_GUI
void tyr::Scene::Debug()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Debug(); });

	SDXL_ImGui_Begin(m_Name.c_str(), nullptr);
	
	static int selected = -1;
	
	for(int i{0}; i < static_cast<int>(m_pSceneObjects.size()); i++)
	{
		if (SDXL_ImGui_Selectable(m_pSceneObjects[i]->GetName().c_str(), selected == i))
		{
			selected = i;
			m_pSceneObjects.at(selected)->m_SelectedItem = -1;
			
		}
		if (i == selected)
		{
			m_pSceneObjects.at(selected)->RenderEditor();
		}
	}


		
	
	SDXL_ImGui_End();
}

void tyr::Scene::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
	
}
#endif
void tyr::Scene::Render() const
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Render(); });
}
