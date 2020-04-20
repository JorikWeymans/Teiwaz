#include "tyrpch.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>
#include "BinaryWriter.h"
#include "BinStructureHelpers.h"
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
void tyr::Scene::RenderEditor()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Debug(); });

	if (!SDXL_ImGui_Begin(m_Name.c_str(), nullptr)) return;

	
	for(int i{0}; i < static_cast<int>(m_pSceneObjects.size()); i++)
	{
		if (SDXL_ImGui_Selectable(m_pSceneObjects[i]->GetName().c_str(), m_SelectedItem == i, SDXL_ImGuiSelectableFlags_AllowDoubleClick))
		{
			m_SelectedItem = i;
			m_pSceneObjects.at(m_SelectedItem)->m_SelectedItem = -1;
			if(SDXL_ImGui_IsItemHovered() && SDXL_ImGui_IsMouseDoubleClicked(0))
			{
				m_ItemDoubleClicked = !m_ItemDoubleClicked;
			}
		}
		if (i == m_SelectedItem)
		{
			m_pSceneObjects.at(m_SelectedItem)->RenderEditor(m_ItemDoubleClicked);
		}
	}

	SDXL_ImGui_Separator();
	
	if(SDXL_ImGui_Button("Add SceneObject"))
	{
		AddSceneObject(new SceneObject());
	}
	
	SDXL_ImGui_End();
}

void tyr::Scene::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);

	//Save name
	//Save Objects
	writer.WriteString(m_Name);
	
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [&writer](SceneObject* s) {s->Save(writer); });
	
	
}


#endif
void tyr::Scene::Flush()
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {SAFE_DELETE(s)});
	m_pSceneObjects.clear();
}
void tyr::Scene::Render() const
{
	std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* s) {s->Render(); });
}
