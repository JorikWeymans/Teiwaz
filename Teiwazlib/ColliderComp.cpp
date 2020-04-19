#include "tyrpch.h"
#include "ColliderComp.h"
#include "Color.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "TyrEnums.h"
#include "Physics.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
tyr::ColliderComp::ColliderComp(float width, float height, const PivotMode& pivotMode, bool isDynamic)
	: tyr::BaseComponent(ComponentType::Collider)
	, m_Width(width), m_Height(height)
	, m_Pivot(pivotMode)
	, m_IsDynamic(isDynamic)
{
}

void tyr::ColliderComp::Initialize()
{
	if(!m_IsDynamic)
		GET_CONTEXT->pPhysics->AddCollider(this);
}


tyr::Rect tyr::ColliderComp::GetColliderRect() const
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();

	Rect rect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(rect, m_Pivot);
	return rect;
	
}
#ifdef USE_IM_GUI
void tyr::ColliderComp::Debug()
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();

	Rect drawRect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(drawRect, m_Pivot);
	
	SDXL_RenderDebugRect({ drawRect.pos.x, drawRect.pos.y }, drawRect.width, drawRect.height, static_cast<SDXL::SDXLVec4>(m_IsDynamic ? ColorGreen : ColorRed));
}

void tyr::ColliderComp::RenderEditor()
{
	if (!SDXL_ImGui_Begin("Inspector")) return;

	std::string name = "Collider Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//POSITION
		SDXL_ImGui_Text("Width:   \t");
		SDXL_ImGui_SameLine();
		name = "##ColH" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Width, 1, 0, GET_CONTEXT->pGameSpace->width);

		SDXL_ImGui_Text("Height:  \t");
		SDXL_ImGui_SameLine();
		name = "##ColW" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Height, 1, 0, GET_CONTEXT->pGameSpace->height);


		SDXL_ImGui_PopItemWidth();
	}
	SDXL_ImGui_End();


}

void tyr::ColliderComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	
	writer.Write(m_Width);
	writer.Write(m_Height);
	
	writer.Write(m_Pivot);
	writer.Write(m_IsDynamic);
}

#endif

