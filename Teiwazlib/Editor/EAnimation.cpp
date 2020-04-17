#include "../tyrpch.h"
#include "EAnimation.h"
#include "../Texture.h"
#include "../ContentManager.h"
#include <algorithm>
tyr::EAnimation::EAnimation(GameContext* pContext)
	: m_pContext(pContext)
{
	m_Texture = CONTENT_MANAGER->LoadTexture(L"BBSprites/Sprites_Sliced_Combined_Scaled.png");

	for(int i{0}; i < 4; ++i)
	{
		m_Rects.push_back(Rect(48.f * i, 0, 48, 48));
	}
	
}

void tyr::EAnimation::RenderEditor()
{
	if (SDXL_ImGui_BeginPopupModal("AniEditor", nullptr, SDXL_ImGuiWindowFlags_NoMove | SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_HorizontalScrollbar | SDXL_ImGuiWindowFlags_AlwaysAutoResize))
	{

		if (SDXL_ImGui_BeginMenuBar())
		{
			if (SDXL_ImGui_MenuItem("close")) SDXL_ImGui_CloseCurrentPopup();

			SDXL_ImGui_EndMenuBar();
		}

		auto mousePos = SDXL_ImGui_GetMousePos();
		if (SDXL_ImGui_BeginChild("Child", SDXL::Float2{ 600.f, 600.f }, true, SDXL_ImGuiWindowFlags_HorizontalScrollbar))
		{
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
				
				if(SDXL_ImGui_IsMouseHoveringRectSize(SDXL_ImGui_GetWindowPos(), SDXL_ImGui_GetWindowSize()) && mouseIsDown == false)
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
		SDXL_ImGui_SameLine();

		SDXL_ImGui_BeginGroup();

		
		mousePos.x /= 48;
		mousePos.y /= 48;
		static char name[25];
		SDXL_ImGui_InputText( "Animation name", name, 25);

		static bool thisIsSelected = false;
		
		static int selectedItem = -1;

		for(auto i{0}; i < static_cast<int>(m_Rects.size()); ++i)
		{
			std::string theString = "Frame " + std::to_string(i) + " " + m_Rects[i].ToString();
			
			if(SDXL_ImGui_Selectable(theString.c_str(), selectedItem == i, SDXL_ImGuiSelectableFlags::DontClosePopups))
			{
				if (selectedItem == i) selectedItem = -1;
				else
				{
					selectedItem = i;
					m_i = static_cast<int>(m_Rects[i].pos.x / m_GridSize);
					m_j = static_cast<int>(m_Rects[i].pos.y / m_GridSize);

					m_y = static_cast<int>(m_Rects[i].width / m_GridSize);
					m_z = static_cast<int>(m_Rects[i].height / m_GridSize);
				}
			
			}
		}
		



		if(SDXL_ImGui_Button("Update##EAnimation"))
		{
			if (selectedItem != -1)
			{
				m_Rects[selectedItem].pos = Vector2(m_i * m_GridSize, m_j * m_GridSize);
				
				m_Rects[selectedItem].width = m_y * m_GridSize;
				m_Rects[selectedItem].height = m_z * m_GridSize;
			}
			
			
		}
		SDXL_ImGui_SameLine();
		if(SDXL_ImGui_Button("Add Frame")) 
		{
			
			m_Rects.emplace_back(Rect(m_i* m_GridSize, m_j* m_GridSize, m_y* m_GridSize, m_z* m_GridSize));
			
		} 

		SDXL_ImGui_SameLine();
		if (SDXL_ImGui_Button("Delete Frame"))
		{
			if(selectedItem )
			m_Rects.erase(m_Rects.begin() /*+ selectedItem*/);
			
		}
		
		//SDXL_ImGui_SameLine();

		//auto winPos = SDXL_ImGui_GetWindowPos();
		//
		//float adjPos = MousePos1.x - winPos.x;
		//
		//SDXL_ImGui_DragFloat("Pos##AniTest", &adjPos, 16, 0, 16 * 5);
		////SDXL_ImGui_SameLine();
		///

		//
		//SDXL_ImGui_Text("test");
		SDXL_ImGui_EndGroup();





		SDXL_ImGui_EndPopup();
	}

}
