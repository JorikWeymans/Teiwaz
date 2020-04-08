#include "tyrpch.h"
#include "ColliderComp.h"
#include "Color.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "TyrEnums.h"
tyr::ColliderComp::ColliderComp(float width, float height, const PivotMode& pivotMode)
	: m_Width(width), m_Height(height)
	, m_Pivot(pivotMode)
{
}

#ifdef USE_IM_GUI
tyr::Rect tyr::ColliderComp::GetColliderRect() const
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();

	Rect rect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(rect, m_Pivot);
	return rect;
	
}

void tyr::ColliderComp::Debug()
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();

	Rect drawRect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(drawRect, m_Pivot);
	
	SDXL_RenderDebugRect({ drawRect.pos.x, drawRect.pos.y }, drawRect.width, drawRect.height, static_cast<SDXL::SDXLVec4>(ColorGreen));
}
#endif