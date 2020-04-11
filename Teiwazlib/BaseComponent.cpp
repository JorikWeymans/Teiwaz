#include "tyrpch.h"
#include "BaseComponent.h"
#include "TransformComp.h"

tyr::BaseComponent::BaseComponent()
#ifdef USE_IM_GUI
	: m_UniqueId(reinterpret_cast<uint32_t>(this))
#endif
{
}
