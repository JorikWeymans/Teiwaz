#include "tyrpch.h"
#include "CMScenes.h"
#include <direct.h>
#include "StringManipulation.h"
#include <filesystem>
#include "Scene.h"
#include "BinaryWriter.h"
#include "BinStructureHelpers.h"
#include "ContentManager.h"
#include "Editor/ETabScenes.h"
tyr::CMScenes::~CMScenes()
{
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [](Scene* s) {SAFE_DELETE(s)});
	m_pScenes.clear();
}

void tyr::CMScenes::Resize(unsigned newSize)
{
	m_pScenes.resize(newSize, nullptr);
}

void tyr::CMScenes::InsertAt(unsigned index, Scene* pData) noexcept
{
	m_pScenes.at(index) = pData;
}

tyr::Scene* tyr::CMScenes::GetScene(const std::string& sceneName) const noexcept
{
	auto found = std::find_if(m_pScenes.begin(), m_pScenes.end(), [&sceneName](Scene* s) { return s->GetName() == sceneName; });
	if (found != m_pScenes.end())
	{
		return *found;
	}
	return nullptr;
}

tyr::Scene* tyr::CMScenes::GetScene(SceneID id) const noexcept
{
	if(id < m_pScenes.size())
	{
		return m_pScenes.at(id);
	}
	return nullptr;
}
#ifdef EDITOR_MODE
void tyr::CMScenes::RenderEditor()
{
	SDXL_ImGui_Text("ID\tName");
	static int selected = -1;
	for (int i{ 0 }; i < static_cast<int>(m_pScenes.size()); ++i)
	{
		std::string tag = FormatString(" %i\t%s", i, m_pScenes[i]->GetName().c_str());

		if (SDXL_ImGui_Selectable(tag.c_str(), selected == i, SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			selected = i;
		}
	}

	SDXL_ImGui_Separator();
	SDXL_ImGui_Text("            "); SDXL_ImGui_SameLine();
	if(SDXL_ImGui_Button("Delete Scene##CMScenes"))
	{
		if(selected > -1 && m_pScenes.size() > 1)
		{
			auto deleteThis = m_pScenes[selected];
			m_pScenes[selected] = *(m_pScenes.end() -1);
			m_pScenes.pop_back();

			if(ContentManager::GetInstance()->GetCurrentScene() == deleteThis)
			{
				ContentManager::GetInstance()->SetCurrentScene(0);
			}


			SAFE_DELETE(deleteThis);
			
			ContentManager::GetInstance()->Save();
			
		}
	}
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("UP##CMScenes"))
	{
		if(selected > 0)
		{
			auto temp = m_pScenes[selected - 1];
			m_pScenes[selected - 1] = m_pScenes[selected];
			m_pScenes[selected] = temp;
			selected--;
			ContentManager::GetInstance()->Save();
			
		}
	}
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("DOWN##CMScenes"))
	{
		if (selected >= 0 && selected < static_cast<int>(m_pScenes.size()-1))
		{
			auto temp = m_pScenes[selected + 1];
			m_pScenes[selected + 1] = m_pScenes[selected];
			m_pScenes[selected] = temp;
			selected++;
			ContentManager::GetInstance()->Save();

		}
	}

	
	static char newScene[40];

	
	///BtnRemoveSelectedTexture(selected);
	
	SDXL_ImGui_SetNextItemWidth(200.f);
	SDXL_ImGui_InputTextWithHint("##CMScenesNewScene", "New scene name", newScene, ARRAY_SIZE(newScene));
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add##ContentManager"))
	{

		Scene* pScene = Scene::GenerateNewScene(std::string(newScene), ContentManager::GetInstance()->GetAbsoluteSceneFolder());
		m_pScenes.emplace_back(pScene);
		ContentManager::GetInstance()->Save();
		m_pTabScenes->CreateTabItems();
		
		//ContentManager::GetInstance()->LoadTexture(std::string(newTexture));
		//ContentManager::GetInstance()->Save();
	}
}

void tyr::CMScenes::SaveScenes(BinaryWriter& writer)
{
	writer.Write(ContentType::Scenes);
	writer.Write(static_cast<UINT>(m_pScenes.size()));
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [&writer](Scene* s) { writer.Write(s->GetName()); });
}
#endif

