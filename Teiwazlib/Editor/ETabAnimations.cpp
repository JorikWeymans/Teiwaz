#include "../tyrpch.h"
#include <direct.h>

#ifdef USE_IM_GUI
#include <filesystem>
#include "../StringManipulation.h"
#include "../ContentManager.h"
#include "../Color.h"
#include "../Texture.h"
#include "../SceneManager.h"
#include "../GameContext.h"
#include "EAnimation.h"
#include "ETabAnimations.h"

tyr::ETabAnimations::ETabAnimations(GameContext* pContext)
	: tyr::ETabItem("Animations", pContext)
	, m_SceneFolder(ContentManager::GetInstance()->GetDataFolder() + "Animations/")
{
	m_Files = CONTENT_MANAGER->GetAnimationsInFolder();
	m_Texture = CONTENT_MANAGER->LoadTexture("Editor/AnimationIcon.png");

	m_pEditorAni = new EAnimation(pContext);
}

tyr::ETabAnimations::~ETabAnimations()
{
	SAFE_DELETE(m_pEditorAni);
}

void tyr::ETabAnimations::PreRender()
{
}

void tyr::ETabAnimations::InternalRenderEditor()
{

	for (auto& s : m_Files)
	{

		SDXL_ImGui_BeginGroup();
		SDXL_ImGui_Image(CONTENT_MANAGER->GetTexture(m_Texture)->SDXL(), { 50.f, 50.f }, SDXL::Float2{ 0.f, 0.f }, SDXL::Float2{ 1.f, 1.f },
			static_cast<SDXL::Float4>(s.isHovered ? ColorGray : ColorWhite));
		SDXL_ImGui_PushTextWrapPos(SDXL_ImGui_GetCursorPos().x + 50.f);
		SDXL_ImGui_TextWrapped(s.name.c_str());
		SDXL_ImGui_PopTextWrapPos();
		SDXL_ImGui_EndGroup();

		s.isHovered = SDXL_ImGui_IsItemHovered();
		if (SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left) && s.isHovered)
		{
			SDXL_ImGui_ConsoleLog("count or something");


			m_pEditorAni->SetCurrentAnimation(CONTENT_MANAGER->GetAnimation(s.name));
			
			SDXL_ImGui_OpenPopup("AniEditor");

			

			
		}

		SDXL_ImGui_SameLine();
	}

	m_pEditorAni->RenderEditor();
}

#endif
