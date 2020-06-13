#include "tyrpch.h"
#include "Textcomp.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "GameContext.h"
#include "Time.h"
#include "ContentManager.h"
#include "Font.h"
#include "TeiwazEngine.h"
#include "BinaryWriter.h"

tyr::TextComp::TextComp(FontID id, const std::string& text, const Color& color, const Vector2& offset)
	: tyr::BaseComponent(ComponentType::Text, "Text Component")
	, m_TextPath("None")
	, m_Text(text)
	, m_Color(color)
	, m_FontID(id)
	, m_pTransform(nullptr)
	, m_Offset(offset)
{}

tyr::TextComp::~TextComp()
{
}

void tyr::TextComp::Initialize()
{
	m_pTransform = m_pSceneObject->GetTransform();
#ifdef EDITOR_MODE
	strcpy_s(m_TempText, m_Text.c_str());
#endif
}

void tyr::TextComp::Update()
{	
}

void tyr::TextComp::FixedUpdate()
{
}

void tyr::TextComp::Render() const
{
	auto pos = m_pTransform->GetPosition();
	pos.x += m_Offset.x;
	pos.y += m_Offset.y;
	 
	SDXL_RenderText(CONTENT_MANAGER->GetFont(m_FontID)->SDXL(), std::wstring(m_Text.begin(), m_Text.end()), { pos.x, pos.y }, static_cast<SDXL::SDXLVec4>(m_Color));
}

void tyr::TextComp::Destroy()
{
}

void tyr::TextComp::SetText(const std::string& newText)
{
	m_Text = newText;
}

void tyr::TextComp::SetColor(const Color& newColor)
{
	m_Color = newColor;
}
void tyr::TextComp::SetColor(float r, float g, float b, float a)
{
	SetColor(Color(r, g, b, a));
}

#ifdef EDITOR_MODE
void tyr::TextComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
	writer.Write(m_Type);

	writer.Write(m_FontID);
	writer.WriteString(m_Text);

	writer.Write(m_Color.r);
	writer.Write(m_Color.g);
	writer.Write(m_Color.b);
	writer.Write(m_Color.a);

	writer.Write(m_Offset.ToPOD());
	
	
}

void tyr::TextComp::InternalRenderEditor()
{
	std::string name;
	std::string stringedID = std::to_string(m_UniqueId);


	
	SDXL_ImGui_Text("Text:   \t");
	SDXL_ImGui_SameLine();

	name = "##TextCompText" + stringedID;
	SDXL_ImGui_InputText(name.c_str(), m_TempText, ARRAY_SIZE(m_TempText));


	name = "Save##TextCompTextSave" + stringedID;
	SDXL_ImGui_SameLine();
	if(SDXL_ImGui_Button(name.c_str()))
	{
		m_Text = std::string(m_TempText);

		for(int i{0}; i < ARRAY_SIZE(m_TempText); i++)
		{
			m_TempText[i] = static_cast<char>('\0');
		}
		strcpy_s(m_TempText, m_Text.c_str());
	}

	SDXL_ImGui_Text("Color:  \t");
	SDXL_ImGui_SameLine(); SDXL_ImGui_SetNextItemWidth(250.f);
	name = "##TextCompColorSelector" + stringedID;
	SDXL_ImGui_ColorEdit4(name.c_str(), &m_Color.r);

	
	SDXL_ImGui_Text("Offset: \t");
	SDXL_ImGui_SameLine();
	
	name = "x##TextCompO" + stringedID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.x);
	SDXL_ImGui_SameLine();

	name = "y##TextCompO" + stringedID;
	SDXL_ImGui_DragFloat(name.c_str(), &m_Offset.y);
	
}
#endif
