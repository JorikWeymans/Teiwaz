#include "tyrpch.h"
#include "TextureComp.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "ContentManager.h"
#include "Texture.h"
#include <iostream>
#include "TeiwazEngine.h"
#include "BinaryWriter.h"
tyr::TextureComp::TextureComp(TextureID id, const PivotMode& pivotMode,
								const Rect& rect, const Vector2& offset)
	: TextureComp(id, Vector2(pivotMode), rect, offset)
{}

tyr::TextureComp::TextureComp(TextureID id, const Vector2& pivot, const Rect& rect, const Vector2& offset)
	: tyr::BaseComponent(ComponentType::Texture)
	, m_TextureID(id)
	, m_pTransform(nullptr)
	, m_Pivot(pivot)
	, m_SrcRect(rect)
	, m_Offset(offset)
{
}

tyr::TextureComp::~TextureComp()
{
}

void tyr::TextureComp::Initialize()
{

	m_pTransform = m_pSceneObject->GetTransform();


	if(!m_SrcRect)
	{
		const Texture* pTexture = CONTENT_MANAGER->GetTexture(m_TextureID);
		if(pTexture)
		{
			const auto di = pTexture->GetDimension();
			m_SrcRect.Set(0.f, 0.f, di.x, di.y);
		}

	}


	
}

void tyr::TextureComp::Update()
{
}

void tyr::TextureComp::FixedUpdate()
{
}

void tyr::TextureComp::Render() const
{

	auto pTexture = CONTENT_MANAGER->GetTexture(m_TextureID);
	if(pTexture)
	{
		auto pos = m_pTransform->GetPosition();
		const auto scale = m_pTransform->GetScale();
		const auto rot = m_pTransform->GetRotation();

		pos += m_Offset;

		SDXL_RenderImage(pTexture->SDXL(), { pos.x, pos.y }, { m_Pivot.x,m_Pivot.y }, { scale.x, scale.y },
			static_cast<SDXL::SDXLRect>(m_SrcRect), rot);
	}


	
}

void tyr::TextureComp::Destroy()
{
	m_pTransform = nullptr;
}

void tyr::TextureComp::SetSourceRect(const Rect& rect)
{
	m_SrcRect = rect;
}
#ifdef EDITOR_MODE

void tyr::TextureComp::RenderEditor()
{
	std::string name = "Texture Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{

		SDXL_ImGui_PushItemWidth(100.f);
		EditorTexture(name);

		SDXL_ImGui_Text("Text map:\t");
		SDXL_ImGui_SameLine();
		static bool b = false;
		SDXL_ImGui_Checkbox("##Box", &b);
		
		EditorPosition(name);
		EditorOffset(name);
		


		SDXL_ImGui_PopItemWidth();

		
	}
}

void tyr::TextureComp::EditorTexture(std::string& name)
{

	SDXL_ImGui_Text("Texture: \t");
	SDXL_ImGui_SameLine();

	name = "##TextureString" + std::to_string(m_UniqueId);

	ContentManager::GetInstance()->EditorTextureDropDown(name.c_str(), m_TextureID);



}

void tyr::TextureComp::EditorPosition(std::string& name)
{
	SDXL_ImGui_Text("Pivot:   \t");
	SDXL_ImGui_SameLine();

	name = "x##" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.x, 1, 0, 1);
	SDXL_ImGui_SameLine();

	name = "y##" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.y, 1, 0, 1);
}
void tyr::TextureComp::EditorOffset(std::string& name)
{
	SDXL_ImGui_Text("Offset:  \t");
	SDXL_ImGui_SameLine();

	name = "x##O" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.x, 1, 0, 100);
	SDXL_ImGui_SameLine();

	name = "y##O" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.y, 1, 0, 100);
}

void tyr::TextureComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	
	writer.Write(m_TextureID);
	writer.Write(m_Pivot.ToPOD());
	writer.Write(m_SrcRect.ToPOD());
	writer.Write(m_Offset.ToPOD());
}
#endif
