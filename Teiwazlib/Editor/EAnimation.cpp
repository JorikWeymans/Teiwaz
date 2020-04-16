#include "../tyrpch.h"
#include "EAnimation.h"
#include "../Texture.h"
#include "../ContentManager.h"

tyr::EAnimation::EAnimation(GameContext* pContext)
	: m_pContext(pContext)
{
	m_pTexture = CONTENT_MANAGER->LoadTexture(L"BBSprites/Sprites_Sliced_Combined_Scaled.png");
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

			SDXL_ImGui_Image(m_pTexture->SDXL());

			float size = 48;
			auto WindowPos = SDXL_ImGui_GetWindowPos();
			WindowPos.x += contentRegion.x;
			WindowPos.y += contentRegion.y;


			static int i = 0;
			static int j = 0;

			static int y = 1;
			static int z = 1;


			SDXL_ImGui_DrawRectInWindow(SDXL::Float2(WindowPos.x + i * size, WindowPos.y + j * size),
				SDXL::Float2(WindowPos.x + y * size + i * size, WindowPos.y + z * size + j * size));






			mousePos.x -= WindowPos.x;
			mousePos.y -= WindowPos.y;



			SDXL_ImGui_SameLine();

			SDXL_ImGui_EndChild();


			if (SDXL_ImGui_IsMouseDown(SDXL_ImGuiMouseButton_Left))
			{
				if (SDXL_ImGui_IsMouseDragging(SDXL_ImGuiMouseButton_Left))
				{
					y = static_cast<int>(mousePos.x / 48) + 1 - i;
					z = static_cast<int>(mousePos.y / 48) + 1 - j;
				}
				else
				{
					i = static_cast<int>(mousePos.x / 48);
					j = static_cast<int>(mousePos.y / 48);
					y = 1;
					z = 1;
				}

			}
		}

		mousePos.x /= 48;
		mousePos.y /= 48;

		SDXL_ImGui_DragFloat2("Width##AniTest", &mousePos.x, 16, 0, 16 * 5);
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






		SDXL_ImGui_EndPopup();
	}

}
