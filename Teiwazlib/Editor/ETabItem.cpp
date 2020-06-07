#include "../tyrpch.h"
#include "ETabItem.h"
#ifdef EDITOR_MODE

#include "../ContentManager.h"
#include "../Color.h"
#include "../Texture.h"



tyr::ETabItem::ETabItem(const char* name, GameContext* pContext, TextureID textureID)
	: m_Name(name)
	, m_pContext(pContext)
	, m_TextureID(textureID)
{}

void tyr::ETabItem::RenderTabItems()
{
	for (auto& s : m_TabItems)
	{

		SDXL_ImGui_BeginGroup();
		SDXL_ImGui_Image(CONTENT_MANAGER->GetTexture(m_TextureID)->SDXL(), { 50.f, 50.f }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f },
			static_cast<SDXL::Float4>(s.isHovered ? ColorGray : ColorWhite));
		SDXL_ImGui_PushTextWrapPos(SDXL_ImGui_GetCursorPos().x + 50.f);
		SDXL_ImGui_TextWrapped(s.name.c_str());
		SDXL_ImGui_PopTextWrapPos();
		SDXL_ImGui_EndGroup();

		s.isHovered = SDXL_ImGui_IsItemHovered();
		if (SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left) && s.isHovered)
		{
			OnItemDoubleClick(s);		
		}

		SDXL_ImGui_SameLine();
	}




	
}

void tyr::ETabItem::RenderEditor()
{
	PreTabRender();

	if(	SDXL_ImGui_BeginTabItem(m_Name))
	{
		RenderTabItems();
		PostTabRender();
		SDXL_ImGui_EndTabItem();
	}
	
	
}
#endif
