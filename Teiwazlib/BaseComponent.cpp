#include "tyrpch.h"
#include "BaseComponent.h"
#include <sstream>
tyr::BaseComponent::BaseComponent(ComponentType type, const std::string& name)
	: m_Type(type)
{
#ifdef EDITOR_MODE
	m_UniqueId = reinterpret_cast<uint32_t>(this);

	std::stringstream ss;
	ss << name;
	ss << "##" << std::to_string(m_UniqueId);
	m_ImGuiHeaderID = ss.str();
#else
	UNREFERENCED_PARAMETER(name);
#endif
}

void tyr::BaseComponent::RenderEditor()
{
	if (SDXL_ImGui_CollapsingHeader(m_ImGuiHeaderID.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		InternalRenderEditor();
		
		SDXL_ImGui_PopItemWidth();

	}


	
	
}

