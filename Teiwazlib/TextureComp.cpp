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
								const Rect& rect, const Vector2& offset, bool isTextureMap,
								bool isRepeating, int repeatX, int repeatY)
	: TextureComp(id, Vector2(pivotMode), rect, offset, isTextureMap, isRepeating, repeatX, repeatY)
{}

tyr::TextureComp::TextureComp(TextureID id, const Vector2& pivot, const Rect& rect, const Vector2& offset, bool isTextureMap,
	bool isRepeating, int repeatX, int repeatY)
	: tyr::BaseComponent(ComponentType::Texture, "Texture Component")
	, m_TextureID(id)
	, m_pTransform(nullptr)
	, m_Pivot(pivot)
	, m_IsTextureMap(isTextureMap)
	, m_SrcRect(rect)
	, m_Offset(offset)
	, m_RepeatTexture(isRepeating)
	, m_RepeatX(repeatX), m_RepeatY(repeatY)
{
}

tyr::TextureComp::~TextureComp()
{
}

void tyr::TextureComp::Initialize()
{
	m_pTransform = m_pSceneObject->GetTransform();

	if(!m_SrcRect || !m_IsTextureMap)
	{
		ResetRenderParameters();
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
	if(pTexture && !m_RepeatTexture)
	{
		auto pos = m_pTransform->GetPosition();
		const auto scale = m_pTransform->GetScale();
		const auto rot = m_pTransform->GetRotation();

		pos += m_Offset;

		SDXL_RenderImage(pTexture->SDXL(), { pos.x, pos.y }, { m_Pivot.x,m_Pivot.y }, { scale.x, scale.y },
			static_cast<SDXL::SDXLRect>(m_SrcRect), rot);
	}
	else if(pTexture)
	{
		auto pos = m_pTransform->GetPosition();
		const auto scale = m_pTransform->GetScale();
		const auto rot = m_pTransform->GetRotation();
		
		for(int x{0}; x < m_RepeatX; x++)
		{
			for (int y{ 0 }; y < m_RepeatY; y++)
			{
				auto theDrawPos = pos;
				theDrawPos.x += static_cast<float>(m_SrcRect.GetWidth() * x * scale.x);
				theDrawPos.y += static_cast<float>(m_SrcRect.GetWidth() * y * scale.x);
				
				SDXL_RenderImage(pTexture->SDXL(), { theDrawPos.x, theDrawPos.y }, { m_Pivot.x,m_Pivot.y }, { scale.x, scale.y },
					static_cast<SDXL::SDXLRect>(m_SrcRect), rot);
			}
		}
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
void tyr::TextureComp::ResetRenderParameters()
{
	const Texture* pTexture = CONTENT_MANAGER->GetTexture(m_TextureID);
	if (pTexture)
	{
		const auto di = pTexture->GetDimension();
		m_SrcRect.Set(0.f, 0.f, di.x, di.y);
	}
}
#ifdef EDITOR_MODE

void tyr::TextureComp::InternalRenderEditor()
{
	std::string name;
	std::string stringedID = std::to_string(m_UniqueId);
	
	EditorTexture(name, stringedID);

	EditorIsTextureMap(name, stringedID);

	if(m_IsTextureMap)
	{
		EditorRenderParameters(name, stringedID);
		EditorIsRepeatedTexture(name, stringedID);
		if(m_RepeatTexture)
		{
			EditorRepeatParameters(name, stringedID);
		}
		SDXL_ImGui_Text("");
	}



	
	EditorPosition(name, stringedID);
	EditorOffset(name, stringedID);




	
}




void tyr::TextureComp::EditorTexture(std::string& name, const std::string& uID)
{

	SDXL_ImGui_Text("Texture: \t");
	SDXL_ImGui_SameLine();

	name = "##TextureString" + uID;

	ContentManager::GetInstance()->EditorTextureDropDown(name.c_str(), m_TextureID);



}
void tyr::TextureComp::EditorPosition(std::string& name, const std::string& uID)
{
	SDXL_ImGui_Text("Pivot:   \t");
	SDXL_ImGui_SameLine();

	name = "x##" + uID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.x, 1, 0, 1);
	SDXL_ImGui_SameLine();

	name = "y##" + uID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Pivot.y, 1, 0, 1);
}
void tyr::TextureComp::EditorOffset(std::string& name, const std::string& uID)
{
	SDXL_ImGui_Text("Offset:  \t");
	SDXL_ImGui_SameLine();

	name = "x##O" + uID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.x, 1, 0, 100);
	SDXL_ImGui_SameLine();

	name = "y##O" + uID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.y, 1, 0, 100);


	
}
void tyr::TextureComp::EditorIsTextureMap(std::string& name, const std::string uID)
{

	SDXL_ImGui_Text("Text map:\t");
	SDXL_ImGui_SameLine();
	name = "##TextureCompIsmap" + uID;
	if(SDXL_ImGui_Checkbox(name.c_str(), &m_IsTextureMap))
	{
		if (!m_IsTextureMap)
			ResetRenderParameters();
	}
}
void tyr::TextureComp::EditorRenderParameters(std::string& name, const std::string& uID)
{


	SDXL_ImGui_Text(" Pos:    \t");
	SDXL_ImGui_SameLine();
	

	Vector2 prevPos = m_SrcRect.pos;
	name = "x##TextureCompPos" + uID;
	if (SDXL_ImGui_DragFloat(name.c_str(), &prevPos.x))
	{
		m_SrcRect.pos = prevPos;
	} SDXL_ImGui_SameLine();
	name = "y##TextureCompPos" + uID;
	if (SDXL_ImGui_DragFloat(name.c_str(), &prevPos.y))
	{
		m_SrcRect.pos = prevPos;
	}

	SDXL_ImGui_Text(" Width:  \t");
	SDXL_ImGui_SameLine();
	name = "##TextureCompWidth" + uID;

	float prevWidth = m_SrcRect.width;

	if (SDXL_ImGui_DragFloat(name.c_str(), &prevWidth))
	{
		m_SrcRect.width = prevWidth;
	}

	SDXL_ImGui_Text(" Height: \t");
	SDXL_ImGui_SameLine();
	name = "##TextureCompHeight" + uID;

	float prevHeight = m_SrcRect.height;

	if (SDXL_ImGui_DragFloat(name.c_str(), &prevHeight))
	{
		m_SrcRect.height = prevHeight;
	}

}

void tyr::TextureComp::EditorIsRepeatedTexture(std::string& name, const std::string& uID)
{
	SDXL_ImGui_Text(" Rep Tex:\t");
	SDXL_ImGui_SameLine();
	name = "##TextureCompRepeatedTexture" + uID;
	SDXL_ImGui_Checkbox(name.c_str(), &m_RepeatTexture);
}
void tyr::TextureComp::EditorRepeatParameters(std::string& name, const std::string& uID)
{
	SDXL_ImGui_Text("  Repeats\t");
	SDXL_ImGui_SameLine();

	name = "x##TextureCompRepeatedX" + uID;
	SDXL_ImGui_DragInt(name.c_str(), &m_RepeatX,1,1,50);
	SDXL_ImGui_SameLine();
	name = "y##TextureCompRepeatedX" + uID;
	SDXL_ImGui_DragInt(name.c_str(), &m_RepeatY, 1, 1, 50);


}


void tyr::TextureComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	
	writer.Write(m_TextureID);
	writer.Write(m_Pivot.ToPOD());

	writer.Write(m_IsTextureMap);
	writer.Write(m_SrcRect.ToPOD());

	writer.Write(m_Offset.ToPOD());

	writer.Write(m_RepeatTexture);
	writer.Write(m_RepeatX);
	writer.Write(m_RepeatY);
}
#endif
