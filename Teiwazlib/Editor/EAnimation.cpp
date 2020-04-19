#include "../tyrpch.h"
#include "EAnimation.h"
#include "../Texture.h"
#include "../ContentManager.h"
#include "../Animation.h"
#include <algorithm>
#include <sstream>

tyr::EAnimation::EAnimation(GameContext* pContext)
	: m_pContext(pContext)
	, m_pAnimation(nullptr)
	, m_WindowIsOpen(false)
{
	m_Texture = CONTENT_MANAGER->LoadTexture("BBSprites/Sprites_Sliced_Combined_Scaled.png");

	
}

void tyr::EAnimation::SetCurrentAnimation(Animation* pAnimation)
{
	m_pAnimation = pAnimation;
	m_tempPos.resize(m_pAnimation->m_AniSprites.size());
	std::copy(m_pAnimation->m_AniSprites.begin(), m_pAnimation->m_AniSprites.end(), m_tempPos.begin());
	
	m_WindowIsOpen = true;
}

void tyr::EAnimation::RenderEditor()
{
	if (!m_pAnimation) return;



	if(SDXL_ImGui_BeginAuto("AniEditor", &m_WindowIsOpen,
		SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_AlwaysAutoResize /*| SDXL_ImGuiWindowFlags*/))
	
	{
		Menu();
		SpriteWindow();

		SDXL_ImGui_SameLine();

		SDXL_ImGui_BeginGroup();
		AnimationEditor();
		SDXL_ImGui_EndGroup();

		SDXL_ImGui_End();
	}



}

void tyr::EAnimation::Menu()
{

	if (SDXL_ImGui_BeginMenuBar())
	{
		//if (SDXL_ImGui_MenuItem("close"))

		if(SDXL_ImGui_MenuItem("Save##EAnimation"))
		{
			SDXL_ImGui_ConsoleLog("Animation is saved");
			
		}

		SDXL_ImGui_EndMenuBar();
	}


}

void tyr::EAnimation::SpriteWindow()
{
	if (SDXL_ImGui_BeginChild("Child", SDXL::Float2{ 600.f, 600.f }, true, SDXL_ImGuiWindowFlags_HorizontalScrollbar))
	{
		auto mousePos = SDXL_ImGui_GetMousePos();
		auto contentRegion = SDXL_ImGui_GetWindowContentRegionMin();

		SDXL_ImGui_Image(CONTENT_MANAGER->GetTexture(m_Texture)->SDXL());

		auto WindowPos = SDXL_ImGui_GetWindowPos();
		WindowPos.x += contentRegion.x;
		WindowPos.y += contentRegion.y;



		SDXL_ImGui_DrawRectInWindow(SDXL::Float2(WindowPos.x + m_i * m_GridSize, WindowPos.y + m_j * m_GridSize),
			SDXL::Float2(WindowPos.x + m_y * m_GridSize + m_i * m_GridSize, WindowPos.y + m_z * m_GridSize + m_j * m_GridSize));


		



		mousePos.x -= WindowPos.x;
		mousePos.y -= WindowPos.y;





		static bool mouseIsDown = false; //makes down to pressed



		if (SDXL_ImGui_IsMouseDown(SDXL_ImGuiMouseButton_Left))
		{

			if (SDXL_ImGui_IsMouseHoveringRectSize(SDXL_ImGui_GetWindowPos(), SDXL_ImGui_GetWindowSize()) && mouseIsDown == false)
			{
				if (SDXL_ImGui_IsMouseDragging(SDXL_ImGuiMouseButton_Left))
				{
					m_y = static_cast<int>(mousePos.x / m_GridSize) + 1 - m_i;
					m_z = static_cast<int>(mousePos.y / m_GridSize) + 1 - m_j;
				}
				else
				{
					m_i = static_cast<int>(mousePos.x / m_GridSize);
					m_j = static_cast<int>(mousePos.y / m_GridSize);
					m_y = 1;
					m_z = 1;
				}
			}
			else
			{
				mouseIsDown = true;
			}



		}
		else
		{
			mouseIsDown = false;
		}




		SDXL_ImGui_EndChild();
	}
}

void tyr::EAnimation::AnimationEditor()
{
	static char name[25];
	SDXL_ImGui_Text(m_pAnimation->m_AnimationName.c_str());;


	static int selectedItem = -1;

	for (auto i{ 0 }; i < static_cast<int>(m_tempPos.size()); ++i)
	{
		std::string theString = "Frame " + std::to_string(i) + " " + m_tempPos[i].ToString();

		if (SDXL_ImGui_Selectable(theString.c_str(), selectedItem == i, SDXL_ImGuiSelectableFlags_DontClosePopups | SDXL_ImGuiSelectableFlags_AllowDoubleClick))
		{
			if(SDXL_ImGui_IsMouseDoubleClicked(0))
			{
				
				m_i = static_cast<int>(m_tempPos[selectedItem].pos.x / m_GridSize);
				m_j = static_cast<int>(m_tempPos[selectedItem].pos.y / m_GridSize);

				m_y = static_cast<int>(m_tempPos[selectedItem].width / m_GridSize);
				m_z = static_cast<int>(m_tempPos[selectedItem].height / m_GridSize);

			}
			else if (selectedItem == i) selectedItem = -1;
			else
			{
				selectedItem = i;

			}

		}
	}

	if (SDXL_ImGui_Button("Update##EAnimation"))
	{
		if (selectedItem != -1)
		{
			m_tempPos[selectedItem].pos = Vector2(m_i * m_GridSize, m_j * m_GridSize);

			m_tempPos[selectedItem].width = m_y * m_GridSize;
			m_tempPos[selectedItem].height = m_z * m_GridSize;
		}


	} 	SDXL_ImGui_SameLine();

	if (SDXL_ImGui_Button("Add Frame"))
	{

		m_tempPos.emplace_back(Rect(m_i * m_GridSize, m_j * m_GridSize, m_y * m_GridSize, m_z * m_GridSize));
		 
	} 	SDXL_ImGui_SameLine();


	if (SDXL_ImGui_Button("Delete Frame"))
	{
		if (selectedItem != -1)
		{
			m_tempPos.erase(m_tempPos.begin() + selectedItem);
			selectedItem--;
		}

		 
	}	SDXL_ImGui_SameLine();
	
}
