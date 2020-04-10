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


#ifdef USE_IM_GUI
void tyr::TransformComp::RenderEditor()
{
	SDXL_ImGui_Begin("Components");

	if (SDXL_ImGui_CollapsingHeader("Transform", SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);

		//POSITION
		SDXL_ImGui_Text("Position:\t");
		SDXL_ImGui_SameLine();

		SDXL_ImGui_DragFloat("x", &m_pTransform->position.x, 1, 0, GET_CONTEXT->pGameSpace->width);
		SDXL_ImGui_SameLine();
		SDXL_ImGui_DragFloat("y", &m_pTransform->position.y, 1,0, GET_CONTEXT->pGameSpace->height);
		
		
		//SCALE
		SDXL_ImGui_Text("Scale:   \t");
		SDXL_ImGui_SameLine();

		// \n to prevent having the same label as position;
		SDXL_ImGui_DragFloat("x\n", &m_pTransform->scale.x, 1, 0.1f, 10.f);
		SDXL_ImGui_SameLine();
		SDXL_ImGui_DragFloat("y\n", &m_pTransform->scale.y, 1, 0.1f, 10.f);

		
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
	TeiwazEngine::GameToEngineSpace(m_pSceneObject->GetGameContext(), &pos);

	return pos;
}

const tyr::Vector2& tyr::TransformComp::GetScale() const
{
	return m_pTransform->scale;
}

float tyr::TransformComp::GetRotation() const
{
	return m_pTransform->rotation;
}

tyr::Transform* tyr::TransformComp::GetTr()
{
	return m_pTransform;
}
