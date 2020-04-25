#include "tyrpch.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>
#include "BinaryWriter.h"

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


	static int itemPopUP = -1;
	
	for(int i{0}; i < static_cast<int>(m_pSceneObjects.size()); i++)
	{
		if (SDXL_ImGui_Selectable(m_pSceneObjects[i]->GetName().c_str(), m_SelectedItem == i, SDXL_ImGuiSelectableFlags_AllowDoubleClick | SDXL_ImGuiSelectableFlags_DontClosePopups))
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

		if (SDXL_ImGui_IsItemHovered() || itemPopUP == i)
		{

			if (SDXL_ImGui_BeginPopupContextWindow("SceneObjectNameEditor"))
			{
				itemPopUP = i;
				static char objectName[25];
				SDXL_ImGui_InputText("##ObjectName", objectName, 25, nullptr);
				SDXL_ImGui_SameLine();
				if (SDXL_ImGui_Button("Save ObjectName"))
				{
					m_pSceneObjects[i]->m_name = std::string(objectName);
					itemPopUP = -1;
				
				}
				SDXL_ImGui_EndPopup();
			}
			else
			{
				itemPopUP = -1;
			}
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
