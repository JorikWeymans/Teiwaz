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
#include "GameContext.h"
#include "Editor/EUI.h"
#include "Editor/EWindowSouth.h"
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
	static int selectedScene = -1;
	
	ShowScenes(selectedScene);
	
	BtnDeleteScene(selectedScene);
	BtnMoveSceneUp(selectedScene);
	BtnMoveSceneDown(selectedScene);
	
	BtnAddScene();
}

void tyr::CMScenes::Save(BinaryWriter& writer)
{
	writer.Write(ContentType::Scenes);
	writer.Write(static_cast<UINT>(m_pScenes.size()));
	std::for_each(m_pScenes.begin(), m_pScenes.end(), [&writer](Scene* s) { writer.Write(s->GetName()); });
}

void tyr::CMScenes::ShowScenes(int& selectedScene)
{
	SDXL_ImGui_Text("ID\tName");

	for (int i{ 0 }; i < static_cast<int>(m_pScenes.size()); ++i)
	{
		std::string tag = FormatString(" %i\t%s", i, m_pScenes[i]->GetName().c_str());

		if (SDXL_ImGui_Selectable(tag.c_str(), selectedScene == i, SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			selectedScene = i;
		}
		if (SDXL_ImGui_IsItemHovered() && SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left))
		{

			CONTENT_MANAGER->SetCurrentScene(i);
		}
	}
	SDXL_ImGui_Separator();
}

void tyr::CMScenes::BtnDeleteScene(int selectedScene)
{
	SDXL_ImGui_Text("            "); SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Delete Scene##CMScenes"))
	{
		if (selectedScene > -1 && m_pScenes.size() > 1)
		{
			auto deleteThis = m_pScenes[selectedScene];
			m_pScenes[selectedScene] = *(m_pScenes.end() - 1);
			m_pScenes.pop_back();

			if (CONTENT_MANAGER->GetCurrentScene() == deleteThis)
			{
				CONTENT_MANAGER->SetCurrentScene(0);
			}


			SAFE_DELETE(deleteThis);

			CONTENT_MANAGER->Save();

		}
	}
}
void tyr::CMScenes::BtnMoveSceneUp(int& selectedScene)
{
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("UP##CMScenes"))
	{
		if (selectedScene > 0)
		{
			auto temp = m_pScenes[selectedScene - 1];
			m_pScenes[selectedScene - 1] = m_pScenes[selectedScene];
			m_pScenes[selectedScene] = temp;
			selectedScene--;
			CONTENT_MANAGER->Save();

		}
	}
}
void tyr::CMScenes::BtnMoveSceneDown(int& selectedScene)
{
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("DOWN##CMScenes"))
	{
		if (selectedScene >= 0 && selectedScene < static_cast<int>(m_pScenes.size() - 1))
		{
			auto temp = m_pScenes[selectedScene + 1];
			m_pScenes[selectedScene + 1] = m_pScenes[selectedScene];
			m_pScenes[selectedScene] = temp;
			selectedScene++;
			CONTENT_MANAGER->Save();

		}
	}
}

void tyr::CMScenes::BtnAddScene()
{
	static char newScene[40];


	SDXL_ImGui_Text("      "); SDXL_ImGui_SameLine();
	SDXL_ImGui_SetNextItemWidth(200.f);
	SDXL_ImGui_InputTextWithHint("##CMScenesNewScene", "New scene name", newScene, ARRAY_SIZE(newScene));
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Add##ContentManager"))
	{

		Scene* pScene = Scene::GenerateNew(std::string(newScene), ContentManager::GetInstance()->GetAbsoluteSceneFolder());
		m_pScenes.emplace_back(pScene);

		CONTENT_MANAGER->GetContext()->pEditorUI->GetWindow<EWindowSouth>()->GetTabItem<ETabScenes>()->CreateTabItems();
		ContentManager::GetInstance()->Save();

	}
}

#endif

