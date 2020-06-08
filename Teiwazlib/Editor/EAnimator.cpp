#include "../tyrpch.h"
#include "EAnimator.h"
#include "../ContentManager.h"

#ifdef  EDITOR_MODE
#include "../Animator.h"
#include "../Connection.h"
#include "../StringManipulation.h"
#include "../EnumDropdown.h"
#endif
tyr::EAnimator::EAnimator()
	: m_pAnimator(nullptr)
	, m_WindowIsOpen(false)
{
}

tyr::EAnimator::~EAnimator()
{
}

void tyr::EAnimator::OpenAnimatorEditorWindow(Animator* pAnimator)
{
	m_pAnimator = pAnimator;
	m_WindowIsOpen = true;
	SDXL_ImGui_OpenPopup("Animator Editor##EAnimator");
}

void tyr::EAnimator::RenderEditor()
{
	if (!m_pAnimator) return;
	
	if (SDXL_ImGui_BeginAuto("Animator Editor##EAnimator", &m_WindowIsOpen,
		SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_AlwaysAutoResize | SDXL_ImGuiWindowFlags_NoCollapse))

	{
		SDXL_ImGui_Text("LHS\t\tRHS\t\tEquation\t\tType\t\tvalue");

		auto con = m_pAnimator->m_pConnections[0];

		SDXL_ImGui_Text(FormatString("  %o\t\t  %o       \t\t%i\t\t     %i", 
							con->lhs, con->rhs, static_cast<int>(con->pVariable->m_Equation), static_cast<int>(con->pVariable->m_Type)).c_str());
		
		UNREFERENCED_PARAMETER(con);
		static AnimatorID id = 0;
		static AnimatorID id2 = 0;
		CONTENT_MANAGER->EditorAnimationDropDown("##EAnimatorLHS", id);
		SDXL_ImGui_SameLine();
		CONTENT_MANAGER->EditorAnimationDropDown("##EAnimatorRHS", id2);

		static Equation e = Equation::BiggerThan;
		SDXL_ImGui_SameLine();
		DROPDOWN_EQUATION("##EAnimatorEquation", e);

		static VariableType v = VariableType::Bool;
		SDXL_ImGui_SameLine();
		DROPDOWN_VARIABLE_TYPE("##EAnimatorVariableType", v);






		
		SDXL_ImGui_End();
	}
	else
	{
		m_pAnimator = nullptr;
	}
}
