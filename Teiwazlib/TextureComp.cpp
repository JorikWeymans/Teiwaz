#include "tyrpch.h"
#include "TextureComp.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "ContentManager.h"
#include "Texture.h"
#include <iostream>
#include "TeiwazEngine.h"

tyr::TextureComp::TextureComp(const std::wstring& texturePath, const PivotMode& pivotMode, 
								const Rect& rect, const Vector2& offset)
	: m_TexturePath(texturePath)
	, m_pTexture(nullptr)
	, m_pTransform(nullptr)
	, m_Pivot(Vector2(pivotMode))
	, m_SrcRect(rect)
	, m_Offset(offset)
{
#ifdef USE_IM_GUI
	SDXL_ImGui_ConsoleLog("Texture component added");
#endif
}

tyr::TextureComp::~TextureComp()
{
}

void tyr::TextureComp::Initialize()
{

	m_pTransform = m_pSceneObject->GetTransform();
	
	m_pTexture = CONTENT_MANAGER->LoadTexture(m_TexturePath);

	if(!m_SrcRect)
	{
		const auto di = m_pTexture->GetDimension();
		m_SrcRect.Set(0.f, 0.f, di.x, di.y);
	}


	
}

void tyr::TextureComp::Update()
{
	std::cout << "ok";
}

void tyr::TextureComp::FixedUpdate()
{
}

void tyr::TextureComp::Render() const
{
	auto pos = m_pTransform->GetPosition();
	const auto scale = m_pTransform->GetScale();
	const auto rot = m_pTransform->GetRotation();

	pos += m_Offset;
	
	SDXL_RenderImage(m_pTexture->SDXL(), { pos.x, pos.y }, { m_Pivot.x,m_Pivot.y },{ scale.x, scale.y },
									static_cast<SDXL::SDXLRect>(m_SrcRect), rot);

	
}

void tyr::TextureComp::Destroy()
{
	m_pTransform = nullptr;
	m_TexturePath = L"";
}

void tyr::TextureComp::SetSourceRect(const Rect& rect)
{
	m_SrcRect = rect;
}
#ifdef USE_IM_GUI

void tyr::TextureComp::RenderEditor()
{
	SDXL_ImGui_Begin("Components");

	std::string name = "Texture Component##" + std::to_string(m_UniqueId);
	if (SDXL_ImGui_CollapsingHeader(name.c_str(), SDXL_ImGuiTreeNodeFlags_DefaultOpen))
	{
		SDXL_ImGui_PushItemWidth(100.f);
		//POSITION
		SDXL_ImGui_Text("Pivot:   \t");
		SDXL_ImGui_SameLine();

		name = "x##" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.x, 1, 0, 1);
		SDXL_ImGui_SameLine();

		name = "y##" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.y, 1, 0, 1);
		
		//POSITION
		SDXL_ImGui_Text("Offset:  \t");
		SDXL_ImGui_SameLine();

		name = "x##O" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.x, 1, 0, 100);
		SDXL_ImGui_SameLine();

		name = "y##O" + std::to_string(m_UniqueId);
		SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.y, 1, 0, 100);

		SDXL_ImGui_PopItemWidth();
	}






	SDXL_ImGui_End();


}
#endif