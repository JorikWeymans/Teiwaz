#include "tyrpch.h"
#include "TransformComp.h"
#include "TeiwazEngine.h"
#include "SceneObject.h"
#include "GameContext.h"
#include "BinaryWriter.h"
tyr::TransformComp::TransformComp(const Transform& transform)
	: tyr::BaseComponent(ComponentType::Transform, "Tansform component", false)
	, m_pTransform(new Transform(transform))
{
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

void tyr::TransformComp::Scale(float x, float y)
{
	m_pTransform->scale.x *= x;
	m_pTransform->scale.y *= y;
}

void tyr::TransformComp::SetScale(float x, float y)
{
	m_pTransform->scale.x = x;
	m_pTransform->scale.y = y;
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

void tyr::TransformComp::SetPositionX(float x, bool convert)
{
	if (convert)
	{
		m_pTransform->position.x = x - ENGINE_SPACING_LEFT;
	}
	else
		m_pTransform->position.x = x;
}

void tyr::TransformComp::SetPositionY(float y, bool convert)
{
	if (convert)
	{
		Vector2 newPos(0.f, y);
		TeiwazEngine::GameToEngineSpace(GET_CONTEXT, &newPos);
		m_pTransform->position.y = newPos.y;
	}
	else
		m_pTransform->position.y = y;
}


#ifdef EDITOR_MODE
void tyr::TransformComp::InternalRenderEditor()
{
	const std::string strUniqueId = std::to_string(m_UniqueId);
	std::string name;
	
	//POSITION
	SDXL_ImGui_Text("Position:\t");
	SDXL_ImGui_SameLine();

	name = "x##P" + strUniqueId;
	SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->position.x);
	SDXL_ImGui_SameLine();
	name = "y##P" + strUniqueId;
	SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->position.y);


	//SCALE
	name = "Scale:   \t";
	SDXL_ImGui_Text(name.c_str());
	SDXL_ImGui_SameLine();

	name = "x##S" + strUniqueId;
	SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->scale.x, 1, 0.1f, 10.f);
	SDXL_ImGui_SameLine();
	name = "y##S" + strUniqueId;
	SDXL_ImGui_DragFloat(name.c_str(), &m_pTransform->scale.y, 1, 0.1f, 10.f);
}

void tyr::TransformComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_pTransform->ToPOD());
	
}
#endif
tyr::TransformComp* tyr::TransformComp::CreateComponent(BinaryReader& reader)
{
	return new TransformComp(Transform(reader.Read<Transform_POD>()));

}

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

tyr::Vector2 tyr::TransformComp::GetPositionRaw() const
{
	auto pos = m_pTransform->position;
	const auto pParent = m_pSceneObject->GetParent();

	if (pParent)
	{
		const auto parentPos = pParent->GetTransform()->m_pTransform->position;

		pos += parentPos;

	}
	//TeiwazEngine::GameToEngineSpace(m_pSceneObject->GetGameContext(), &pos);

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

