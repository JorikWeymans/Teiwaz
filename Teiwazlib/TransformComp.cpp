#include "tyrpch.h"
#include "TransformComp.h"
#include "TeiwazEngine.h"
#include "SceneObject.h"
#include "GameContext.h"
tyr::TransformComp::TransformComp(const Transform& transform)
	: m_pTransform(new Transform(transform))
{
#ifdef USE_IM_GUI
	SDXL_ImGui_ConsoleLog("Transform added");
#endif
}
tyr::TransformComp::TransformComp(const Vector2& position)
	: TransformComp(Transform(position))
{
}
tyr::TransformComp::TransformComp(const Vector2& position, const Vector2& scale, float rotation)
	:TransformComp(Transform(position, scale, rotation))
{
}

tyr::TransformComp::~TransformComp()
{
	SAFE_DELETE(m_pTransform);
}

void tyr::TransformComp::Translate(float x, float y)
{
	m_pTransform->position.x += x;
	m_pTransform->position.y += y;
	
}

void tyr::TransformComp::Initialize()
{
	//TeiwazEngine::GameToEngineSpace(m_pSceneObject->GetGameContext(), &m_pTransform->position);
}

void tyr::TransformComp::Update()
{
}
void tyr::TransformComp::FixedUpdate()
{
}
void tyr::TransformComp::Render() const
{
}

void tyr::TransformComp::SetPositionY(float y)
{
	m_pTransform->position.y = y;
}


#ifdef USE_IM_GUI
void tyr::TransformComp::RenderEditor()
{
	SDXL_ImGui_Begin("Inspector");

	const std::string strUniqueId = std::to_string(m_UniqueId);
	std::string name = "Tansform##" + strUniqueId;
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);
		//POSITION
		SDXL_ImGui_Text("Position:\t");
		SDXL_ImGui_SameLine();

		name = "x##P" + strUniqueId;
		SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->position.x, 1, 0, GET_CONTEXT->pGameSpace->width);
		SDXL_ImGui_SameLine();
		name = "y##P" + strUniqueId;
		SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->position.y, 1,0, GET_CONTEXT->pGameSpace->height);
		
		
		//SCALE
		name = "Scale:   \t";
		SDXL_ImGui_Text(name.c_str());
		SDXL_ImGui_SameLine();

		name = "x##S" + strUniqueId;
		SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->scale.x, 1, 0.1f, 10.f);
		SDXL_ImGui_SameLine();
		name = "y##S" + strUniqueId;
		SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->scale.y, 1, 0.1f, 10.f);

		
		SDXL_ImGui_PopItemWidth();
	}
	SDXL_ImGui_End();
	
	
}
#endif
const tyr::Transform& tyr::TransformComp::GetTransform() const
{
	return *m_pTransform;
}

tyr::Vector2 tyr::TransformComp::GetPosition() const
{

	auto pos = m_pTransform->position;
	

	
	const auto pParent = m_pSceneObject->GetParent();
	
	if(pParent)
	{
		const auto parentPos = pParent->GetTransform()->m_pTransform->position;
		
		pos += parentPos;
		
	}
	TeiwazEngine::GameToEngineSpace(m_pSceneObject->GetGameContext(), &pos);
	
	return pos;
}

tyr::Vector2 tyr::TransformComp::GetScale() const
{
	auto thisScale = m_pTransform->scale;

	const auto pParent = m_pSceneObject->GetParent();

	if (pParent)
	{

		thisScale *= pParent->GetTransform()->m_pTransform->scale;

	}
	return thisScale;
}

float tyr::TransformComp::GetRotation() const
{
	return m_pTransform->rotation;
}

tyr::Transform* tyr::TransformComp::GetTr()
{
	return m_pTransform;
}
