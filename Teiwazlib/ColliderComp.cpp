#include "tyrpch.h"
#include "ColliderComp.h"
#include "Color.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "TyrEnums.h"
#include "Physics.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include "EnumDropdown.h"

tyr::ColliderComp::ColliderComp(float width, float height, const PivotMode& pivotMode, bool isDynamic)
	: tyr::BaseComponent(ComponentType::Collider, "Collider Component")
	, m_Width(width), m_Height(height)
	, m_Pivot(pivotMode)
	, m_IsDynamic(isDynamic)
{
}

tyr::ColliderComp::~ColliderComp()
{
	GET_CONTEXT->pPhysics->RemoveCollider(this);
}

void tyr::ColliderComp::Initialize()
{
	GET_CONTEXT->pPhysics->AddCollider(this);
}


tyr::Rect tyr::ColliderComp::GetColliderRect() const
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();

	Rect rect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(rect, m_Pivot);
	return rect;
	
}
void tyr::ColliderComp::OnColliderHit(RaycastHit hit)
{
	if (onColliderHitFunction)
		onColliderHitFunction(hit);

}
#ifdef EDITOR_MODE
void tyr::ColliderComp::Debug()
{
	const auto pos = m_pSceneObject->GetTransform()->GetPosition();
	
	Rect drawRect{ pos.x, pos.y, m_Width, m_Height };
	Rect::AdjustRectToPivot(drawRect, m_Pivot);
	
	SDXL_RenderDebugRect({ drawRect.pos.x, drawRect.pos.y }, drawRect.width, drawRect.height, static_cast<SDXL::SDXLVec4>(m_IsDynamic ? ColorGreen : ColorRed));
}

void tyr::ColliderComp::InternalRenderEditor()
{
	std::string name;
	std::string idString = std::to_string(m_UniqueId);
	//POSITION
	SDXL_ImGui_Text("Width:   \t");
	SDXL_ImGui_SameLine();
	name = "##ColliderCompColH" + idString;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Width, 1, 0, GET_CONTEXT->pGameSpace->width);

	SDXL_ImGui_Text("Height:  \t");
	SDXL_ImGui_SameLine();
	name = "##ColliderCompColW" + idString;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Height, 1, 0, GET_CONTEXT->pGameSpace->height);


	SDXL_ImGui_Text("Pivot:   \t");
	SDXL_ImGui_SameLine();
	name = "##ColliderCompPivotMode" + idString;
	EnumDropdown::GetInstance()->PivotModeDropDown(name.c_str(), m_Pivot);

	RenderIsDynamicProperty();
	
}

void tyr::ColliderComp::RenderIsDynamicProperty()
{
	SDXL_ImGui_Text("Dynamic? \t");
	SDXL_ImGui_SameLine();
	const bool prev = m_IsDynamic;
	SDXL_ImGui_Checkbox("##ColliderComp", &m_IsDynamic);

	if(prev != m_IsDynamic)
	{
		GET_CONTEXT->pPhysics->SwitchVector(this);
	}
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

