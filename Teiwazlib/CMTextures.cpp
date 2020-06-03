#include "tyrpch.h"
#include "CMTextures.h"
#include <algorithm>
#include "TyrException.h"
#include "Texture.h"
#include "StringManipulation.h"
#include "ContentManager.h"
#include "BinStructureHelpers.h"
#include "BinaryWriter.h"
tyr::CMTextures::~CMTextures()
{
	std::for_each(m_pTextures.begin(), m_pTextures.end(), [](auto* p) {SAFE_DELETE(p)});
}

void tyr::CMTextures::Resize(unsigned newSize)
{
	m_pTextures.resize(newSize, nullptr);	
}
void tyr::CMTextures::InsertAt(unsigned index, Texture* pData) noexcept
{
	m_pTextures.at(index) = pData;
}

TextureID tyr::CMTextures::LoadTexture(const std::string& dataFolder, const std::string& name)
{
	auto found = std::find(m_pTextures.begin(), m_pTextures.end(), name);

	if (found != m_pTextures.end())
	{
		return static_cast<TextureID>(std::distance(m_pTextures.begin(), found));
	}

	try
	{
		auto pTemp = new Texture(dataFolder, name);
		m_pTextures.emplace_back(pTemp);
		return static_cast<TextureID>(m_pTextures.size() - 1);
	}
	catch (TyrException& e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
		return 0;
	}
}

tyr::Texture* tyr::CMTextures::GetTexture(TextureID id) const
{
	if (id >= m_pTextures.size()) return nullptr;

	return m_pTextures[id];
}

#ifdef EDITOR_MODE
void tyr::CMTextures::RenderEditor()
{
	SDXL_ImGui_Text("ID\tName");
	static int selected = -1;
	for (int i{ 0 }; i < static_cast<int>(m_pTextures.size()); ++i)
	{
		std::string tag = FormatString(" %i\t%s", i, m_pTextures[i]->GetName().c_str());

		if (SDXL_ImGui_Selectable(tag.c_str(), selected == i, SDXL_ImGuiSelectableFlags_DontClosePopups))
		{
			selected = i;
		}
	}

	if (selected != -1)
	{
		if (SDXL_ImGui_Begin("Texture##", nullptr, SDXL_ImGuiWindowFlags_AlwaysAutoResize))
		{
			auto di = m_pTextures[selected]->GetDimension();

			SDXL_ImGui_Image(m_pTextures[selected]->SDXL(), { di.x, di.y }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f });


		}
		SDXL_ImGui_End();
	}
	SDXL_ImGui_Separator();
	static char newTexture[40];

	BtnRemoveSelectedTexture(selected);

	SDXL_ImGui_SameLine();
	SDXL_ImGui_SetNextItemWidth(200.f);
	SDXL_ImGui_InputTextWithHint("##ContentManagerTextureName", "TEXTURE_NAME.png", newTexture, ARRAY_SIZE(newTexture));
	SDXL_ImGui_SameLine();
	if (SDXL_ImGui_Button("Load##ContentManager"))
	{
		ContentManager::GetInstance()->LoadTexture(std::string(newTexture));
		ContentManager::GetInstance()->Save();
	}
}

void tyr::CMTextures::ETextureSelector(const char* imGuiID, TextureID& textureID)
{
	const char* item_current = m_pTextures[textureID]->GetName().c_str();
	SDXL_ImGui_SetNextItemWidth(219.f);
	if (SDXL_ImGui_BeginCombo(imGuiID, item_current, SDXL_ImGuiComboFlags_HeightLargest)) // The second parameter is the label previewed before opening the combo.
	{
		for (UINT n = 0; n < static_cast<UINT>(m_pTextures.size()); n++)
		{
			bool is_selected = (item_current == m_pTextures[n]->GetName().c_str());

			if (SDXL_ImGui_Selectable(m_pTextures[n]->GetName().c_str(), is_selected))
				textureID = n;
			if (is_selected)
				SDXL_ImGui_SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		SDXL_ImGui_EndCombo();
	}
}

void tyr::CMTextures::SaveTextures(BinaryWriter& writer)
{
	writer.Write(ContentType::Texture);
	writer.Write(static_cast<UINT>(m_pTextures.size()));
	std::for_each(m_pTextures.begin(), m_pTextures.end(), [&writer](Texture* t) { writer.Write(t->GetName()); });
}

void tyr::CMTextures::BtnRemoveSelectedTexture(int& selected)
{
	if (SDXL_ImGui_Button("Remove Selected##TextureContentManager"))
	{

		if (selected == -1) return;
		SDXL_ImGui_OpenPopup("Are you sure?##TextureContentManager");

	}

	SDXL_ImGui_SetNextWindowSize(SDXL::Float2(400.f, 100.f));
	if (SDXL_ImGui_BeginPopupModal("Are you sure?##TextureContentManager", nullptr, SDXL_ImGuiWindowFlags_NoMove | SDXL_ImGuiWindowFlags_NoResize))
	{
		std::string what = "This cannot be undone!";
		std::string whatSecond = "Texture: " + m_pTextures[selected]->GetName() + " will be deleted!";
		SDXL_ImGui_Text(what.c_str());
		SDXL_ImGui_Text(whatSecond.c_str());

		if (SDXL_ImGui_Button("Never Mind##TextureContentManager", SDXL::Float2(180.f, 20.f)))
		{
			SDXL_ImGui_CloseCurrentPopup();
		}
		SDXL_ImGui_SameLine();
		if (SDXL_ImGui_Button("Yes, I understand", SDXL::Float2(180.f, 20.f)))
		{
			const std::string WhatUnloaded = "[UNLOADED] " + m_pTextures[selected]->GetName();
			if (selected != static_cast<int>(m_pTextures.size()) - 1)
			{
				Texture* pToDelete = m_pTextures[selected];
				for (int i = selected; i < static_cast<int>(m_pTextures.size() - 1); i++)
				{
					m_pTextures[i] = m_pTextures[i + 1];
				}

				m_pTextures[m_pTextures.size() - 1] = pToDelete;

			}

			SAFE_DELETE(m_pTextures[selected]);
			m_pTextures.erase(std::remove(m_pTextures.begin(), m_pTextures.end(), m_pTextures[selected]));


			ContentManager::GetInstance()->Save();
			SDXL_ImGui_ConsoleLog(WhatUnloaded.c_str());
			selected = -1;
			SDXL_ImGui_CloseCurrentPopup();
		}

		SDXL_ImGui_EndPopup();
	}
}
#endif
