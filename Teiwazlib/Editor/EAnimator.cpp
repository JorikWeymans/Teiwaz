#include "../tyrpch.h"
#include "EAnimator.h"


#ifdef  EDITOR_MODE
#include "../Animator.h"
#include "../Connection.h"
#include "../StringManipulation.h"
#include "../EnumDropdown.h"
#include "../ContentManager.h"
#include "../GameContext.h"

#include "EUI.h"
#include "ETabAnimators.h"
#include "EWindowSouth.h"

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

	strcpy_s(m_TempName, m_pAnimator->GetName().c_str());
	
	OnSelectionChanged(0); //Default selection to 0
}

void tyr::EAnimator::RenderEditor()
{
	if (!m_pAnimator) return;
	
	if (SDXL_ImGui_BeginAuto("Animator Editor##EAnimator", &m_WindowIsOpen,
		SDXL_ImGuiWindowFlags_MenuBar | SDXL_ImGuiWindowFlags_AlwaysAutoResize | SDXL_ImGuiWindowFlags_NoCollapse))
	{
		Menu();
		
		static int selected = 0;
		if(SDXL_ImGui_BeginChild("Child##EAnimator", SDXL::Float2{ 200.f, 200.f }, false))
		{
			
			SDXL_ImGui_Text("Name:"); SDXL_ImGui_SameLine();
			if(SDXL_ImGui_InputText("##AnimatorNameEAnimator", m_TempName, ARRAY_SIZE(m_TempName)))
			{
				m_pAnimator->m_Name = std::string(m_TempName);
			}

			
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

			if(SDXL_ImGui_Button("ADD##EAnimatorConnection"))
			{
				m_pAnimator->m_pConnections.emplace_back(Connection::CreateNew());
				
			} SDXL_ImGui_SameLine();
			if (SDXL_ImGui_Button("REMOVE##EAnimatorConnection"))
			{
				if (selected > -1 && m_pAnimator->m_pConnections.size() > 1)
				{
					auto deleteThis = m_pAnimator->m_pConnections[selected];
					m_pAnimator->m_pConnections[selected] = *(m_pAnimator->m_pConnections.end() - 1);

					//When deleting the last one, -- selected to avoid "array out of range"
					if (m_pAnimator->m_pConnections.size() - 1 == static_cast<UINT>(selected))
						selected--;

					OnSelectionChanged(selected);
					m_pAnimator->m_pConnections.pop_back();
					SAFE_DELETE(deleteThis);
				}
			}
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
	if (SDXL_ImGui_BeginChild("Child2##EAnimator", SDXL::Float2{ 200.f, 0.f }, true))
	{
		if (selected == -1)
		{
			SDXL_ImGui_EndChild();
			return;
		}
		
		auto con = m_pAnimator->m_pConnections[selected];

		SDXL_ImGui_Text("Var name: ");
		SDXL_ImGui_SameLine();
		SDXL_ImGui_SetNextItemWidth(110.f);
		if (SDXL_ImGui_InputText("##EAnimatorName", m_TempConnectionName, ARRAY_SIZE(m_TempConnectionName)))
		{
			con->pVariable->m_Name = std::string(m_TempConnectionName);
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
	strcpy_s(m_TempConnectionName, m_pAnimator->m_pConnections[newSelected]->pVariable->GetName().c_str());
}

void tyr::EAnimator::Menu()
{
	if (SDXL_ImGui_BeginMenuBar())
	{
		if (SDXL_ImGui_MenuItem("Save##EAnimation"))
		{
			m_pAnimator->Save();
			CONTENT_MANAGER->Save();
			CONTENT_MANAGER->GetContext()->pEditorUI->GetWindow<EWindowSouth>()->
				GetTabItem<ETabAnimators>()->CreateTabItems();
			
			SDXL_ImGui_ConsoleLog("Animator is Saved");
		}
		SDXL_ImGui_EndMenuBar();
	}
}

#endif