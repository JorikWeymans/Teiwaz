#include "tyrpch.h"
#include "BaseComponent.h"
#include "TransformComp.h"

tyr::BaseComponent::BaseComponent(ComponentType type)
	: m_Type(type)
{
#ifdef EDITOR_MODE
	m_UniqueId = reinterpret_cast<uint32_t>(this);
#endif
}

