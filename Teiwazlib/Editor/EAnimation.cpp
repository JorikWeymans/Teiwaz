#include "../tyrpch.h"
#include "EAnimation.h"
#include "../Texture.h"
#include "../ContentManager.h"
#include "../Animation.h"
#include <algorithm>
#include <sstream>
#include "../GameContext.h"
#include "../Time.h"
tyr::EAnimation::EAnimation(GameContext* pContext)
	: m_pContext(pContext)
	, m_pAnimation(nullptr)
	, m_WindowIsOpen(false)
	, m_ShowAnimation(true)
	, m_pTemp(nullptr)
{
	m_Texture = CONTENT_MANAGER->LoadTexture("BBSprites/Sprites_Sliced_Combined_Scaled.png");

	
}

tyr::EAnimation::~EAnimation()
{
	SAFE_DELETE(m_pTemp); //Only happens when the porgram is closed without closing the Animation Window
}

void tyr::EAnimation::SetCurrentAnimation(Animation* pAnimation)
{
	m_pAnimation = pAnimation;

	//Creating a temporary animation in this class, when animation is saved, copy everything over to the selected animation
	m_pTemp = new Animation(m_pAnimation->m_AniElapser.GetMax());
	m_pTemp->m_AniSprites.resize(m_pAnimation->m_AniSprites.size());
	
	

	std::copy(m_pAnimation->m_AniSprites.begin(), m_pAnimation->m_AniSprites.end(), m_pTemp->m_AniSprites.begin());





	
	m_WindowIsOpen = true;
}

void tyr::EAnimation::RenderEditor()
{
	if (!m_pAnimation) return;



	if(SDXL_ImGui_BeginAuto("AniEditor", &m_WindowIsOpen,
		SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_AlwaysAutoResize | SDXL_ImGuiWindowFlags_NoMove/*| SDXL_ImGuiWindowFlags*/))
	
	{
		Menu();
		SpriteWindow();

		SDXL_ImGui_SameLine();

		SDXL_ImGui_BeginGroup();
		AnimationEditor();

		
		
		
		SDXL_ImGui_EndGroup();
		SDXL_ImGui_End();


		if (SDXL_ImGui_Begin("Animation Preview##EAnimation", nullptr, SDXL_ImGuiWindowFlags_AlwaysAutoResize))
		{
			if(SDXL_ImGui_Checkbox("Animate", &m_ShowAnimation))
			{
				//m_pTemp->m_AniElapser.Reset();
				//m_pTemp->m_CurrentAnimation = 0;
			}
			if (!m_pTemp->m_AniSprites.empty())
			{
				if (m_ShowAnimation)
					m_pTemp->Update(m_pContext->pTime->fixedDeltaTime);

				auto texture = CONTENT_MANAGER->GetTexture(m_Texture);
				auto drawRect = m_pTemp->GetCurrentAnimation();

				SDXL_ImGui_Image(texture->SDXL(), static_cast<SDXL::SDXLRect>(drawRect), 3.0f);
			}
		
			SDXL_ImGui_End();
		}
	}
	else
	{
		SAFE_DELETE(m_pTemp);
		m_pAnimation = nullptr;
	}



}

void tyr::EAnimation::Menu()
{

	if (SDXL_ImGui_BeginMenuBar())
	{
		//if (SDXL_ImGui_MenuItem("close"))

		if(SDXL_ImGui_MenuItem("Save##EAnimation"))
		{

			if(m_pTemp->m_AniSprites.empty())
			{
				SDXL_ImGui_ConsoleLogError("Cannot Save animation without any elements");
			}
			else
			{
				m_pAnimation->m_AniSprites.clear();
				m_pAnimation->m_AniSprites.resize(m_pTemp->m_AniSprites.size());
				std::copy(m_pTemp->m_AniSprites.begin(), m_pTemp->m_AniSprites.end(), m_pAnimation->m_AniSprites.begin());
				m_pAnimation->m_AniElapser.Reset(m_pTemp->m_AniElapser.GetMax());
				
				m_pAnimation->Save();
				SDXL_ImGui_ConsoleLog("Animation is saved");

			}
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

	float tpf = m_pTemp->m_AniElapser.GetMax();
	
	if(SDXL_ImGui_DragFloat("Time per frame", &tpf, 0.001f))
		m_pTemp->m_AniElapser.SetMax(tpf);
	

	static int selectedItem = -1;

	for (auto i{ 0 }; i < static_cast<int>(m_pTemp->m_AniSprites.size()); ++i)
	{
		std::string theString = "Frame " + std::to_string(i) + " " + m_pTemp->m_AniSprites[i].ToString();

		if (SDXL_ImGui_Selectable(theString.c_str(), selectedItem == i, SDXL_ImGuiSelectableFlags_DontClosePopups | SDXL_ImGuiSelectableFlags_AllowDoubleClick))
		{
			if(SDXL_ImGui_IsMouseDoubleClicked(0))
			{
				selectedItem = i;
				m_i = static_cast<int>(m_pTemp->m_AniSprites[selectedItem].pos.x / m_GridSize);
				m_j = static_cast<int>(m_pTemp->m_AniSprites[selectedItem].pos.y / m_GridSize);
									   
				m_y = static_cast<int>(m_pTemp->m_AniSprites[selectedItem].width / m_GridSize);
				m_z = static_cast<int>(m_pTemp->m_AniSprites[selectedItem].height / m_GridSize);

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
			m_pTemp->m_AniSprites[selectedItem].pos = Vector2(m_i * m_GridSize, m_j * m_GridSize);

			m_pTemp->m_AniSprites[selectedItem].width = m_y * m_GridSize;
			m_pTemp->m_AniSprites[selectedItem].height = m_z * m_GridSize;
		}


	} 	SDXL_ImGui_SameLine();

	if (SDXL_ImGui_Button("Add##EAnimation"))
	{

		m_pTemp->m_AniSprites.emplace_back(Rect(m_i * m_GridSize, m_j * m_GridSize, m_y * m_GridSize, m_z * m_GridSize));
		 
	} 	SDXL_ImGui_SameLine();
	
	if (SDXL_ImGui_Button("Add (Batch)##EAnimation"))
	{
		for (int j{ m_j }; j < m_z; j++)
		{
			for(int i {m_i}; i < m_y; i++)
			{
			
					m_pTemp->m_AniSprites.emplace_back(Rect(i * m_GridSize, j * m_GridSize, m_GridSize, m_GridSize));
				
				
			}
		}
		
	}

	if(SDXL_ImGui_IsItemHovered())
	{
		SDXL_ImGui_BeginTooltip();
		SDXL_ImGui_Text("Add selection but");
		SDXL_ImGui_Text(" split every cell");
		SDXL_ImGui_EndTooltip();
	}

	
	if (SDXL_ImGui_Button("Delete##EAnimation"))
	{
		if (selectedItem != -1)
		{
			m_pTemp->m_AniElapser.Reset();
			m_pTemp->m_CurrentAnimation = 0;
			
			m_pTemp->m_AniSprites.erase(m_pTemp->m_AniSprites.begin() + selectedItem);
			selectedItem--;
		}

		 
	} SDXL_ImGui_SameLine();
	
	if(SDXL_ImGui_Button("Delete All##EAnimation"))
	{
		m_pTemp->m_AniElapser.Reset();
		m_pTemp->m_CurrentAnimation = 0;
		
		selectedItem = -1;
		m_pTemp->m_AniSprites.clear();
		
	}

	
}
