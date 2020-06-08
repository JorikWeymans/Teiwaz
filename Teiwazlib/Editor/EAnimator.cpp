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

	
	OnSelectionChanged(0); //Default selection to 0
}

void tyr::EAnimator::RenderEditor()
{
	if (!m_pAnimator) return;
	
	if (SDXL_ImGui_BeginAuto("Animator Editor##EAnimator", &m_WindowIsOpen,
		SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_AlwaysAutoResize | SDXL_ImGuiWindowFlags_NoCollapse))
	{
		static int selected = 0;
		if(SDXL_ImGui_BeginChild("Child##EAnimator", SDXL::Float2{ 200.f, 200.f }, false))
		{
			
			SDXL_ImGui_Text("  CONNECTIONS  ");

			for (int i{ 0 }; i < static_cast<int>(m_pAnimator->m_pConnections.size()); ++i)
			{
				if (SDXL_ImGui_Selectable(FormatString("Connection %i##EAnimator", i).c_str(), selected == i, SDXL_ImGuiSelectableFlags_DontClosePopups))
				{
					selected = i;
					OnSelectionChanged(selected);
				}
				if (SDXL_ImGui_IsItemHovered() && SDXL_ImGui_IsMouseDoubleClicked(SDXL_ImGuiMouseButton_Left))
				{

					//OnItemDoubleClicked(selected);
				}
			}

			//if (selected != -1)

			
			SDXL_ImGui_EndChild();
		}
		SDXL_ImGui_SameLine();

		RenderConnectionProperties(selected);

		
		SDXL_ImGui_End();
	}
	else
	{
		m_pAnimator = nullptr;
	}
}

void tyr::EAnimator::RenderConnectionProperties(int selected)
{
	if (SDXL_ImGui_BeginChild("Child2##EAnimator", SDXL::Float2{ 200.f, 0.f }, false))
	{
		if (selected == -1)
		{
			SDXL_ImGui_EndChild();
			return;
		}
		
		auto con = m_pAnimator->m_pConnections[selected];

		SDXL_ImGui_Text("Name: \t");
		SDXL_ImGui_SameLine();
		SDXL_ImGui_SetNextItemWidth(110.f);
		if (SDXL_ImGui_InputText("##EAnimatorName", m_Temp, ARRAY_SIZE(m_Temp)))
		{
			con->pVariable->m_Name = std::string(m_Temp);
		}

		SDXL_ImGui_Text("LHS:  \t"); SDXL_ImGui_SameLine();
		CONTENT_MANAGER->EditorAnimationDropDown("##EAnimatorLHS", con->lhs);


		SDXL_ImGui_Text("RHS:  \t");  SDXL_ImGui_SameLine();
		CONTENT_MANAGER->EditorAnimationDropDown("##EAnimatorRHS", con->rhs);

		SDXL_ImGui_Text("Equation: ");  SDXL_ImGui_SameLine();
		DROPDOWN_EQUATION("##EAnimatorEquation", con->pVariable->m_Equation, 110);

		SDXL_ImGui_Text("Type: \t");  SDXL_ImGui_SameLine();
		DROPDOWN_VARIABLE_TYPE("##EAnimatorVariableType", con->pVariable->m_Type, 110);

		SDXL_ImGui_Text("Value:\t");  SDXL_ImGui_SameLine();
		switch (con->pVariable->m_Type)
		{
		case VariableType::Bool:
			SDXL_ImGui_Checkbox("##EAnimatorBool", &con->pVariable->bComparatorValue);

			break;
		case VariableType::Float:
			SDXL_ImGui_SetNextItemWidth(110.f);
			SDXL_ImGui_DragFloat("##EAnimatorFloat", &con->pVariable->fComparatorValue);
			break;
		default:;

		}

		SDXL_ImGui_EndChild();
	}

}

void tyr::EAnimator::OnSelectionChanged(int newSelected)
{
	strcpy_s(m_Temp, m_pAnimator->m_pConnections[newSelected]->pVariable->GetName().c_str());
}
