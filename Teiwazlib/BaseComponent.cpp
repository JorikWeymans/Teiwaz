#include "tyrpch.h"
#include "BaseComponent.h"
#include "SceneObject.h"
#include "GameContext.h"
#include <sstream>
tyr::BaseComponent::BaseComponent(ComponentType type, const std::string& name, bool canBeRemoved)
	: m_Type(type)
{
#ifdef EDITOR_MODE
	m_UniqueId = reinterpret_cast<uint32_t>(this);
	m_IsComponentOpen = true;
	m_CanBeRemoved = canBeRemoved;
	std::stringstream ss;
	ss << name;
	ss << "##" << std::to_string(m_UniqueId);
	m_ImGuiHeaderID = ss.str();
#else
	UNREFERENCED_PARAMETER(name);
	UNREFERENCED_PARAMETER(canBeRemoved);
#endif
}
#ifdef EDITOR_MODE
void tyr::BaseComponent::RenderEditor()
{
	if(m_CanBeRemoved && GET_CONTEXT->paused)
	{
		if (SDXL_ImGui_CollapsingHeader(m_ImGuiHeaderID.c_str(),&m_IsComponentOpen, SDXL_ImGuiTreeNodeFlags_DefaultOpen | SDXL_ImGuiTreeNodeFlags_Framed))
		{
			SDXL_ImGui_PushItemWidth(100.f);

			InternalRenderEditor();

			SDXL_ImGui_PopItemWidth();

		}
	}
	else
	{
		if (SDXL_ImGui_CollapsingHeader(m_ImGuiHeaderID.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen | SDXL_ImGuiTreeNodeFlags_Framed))
		{
			SDXL_ImGui_PushItemWidth(100.f);

			InternalRenderEditor();

			SDXL_ImGui_PopItemWidth();

		}
	}
	
	
	if(!m_IsComponentOpen)
	{
		m_pSceneObject->RemoveComponent(this);
	}
	
}
#endif

