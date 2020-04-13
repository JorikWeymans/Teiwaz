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
tyr::TextComp::TextComp(const std::wstring& textPath, const std::wstring& text, const Color& color, const Vector2& offset)
	: tyr::BaseComponent(ComponentType::Text)
	, m_TextPath(textPath)
	, m_Text(text)
	, m_Color(color)
	, m_pFont(nullptr)
	, m_pTransform(nullptr)
	, m_Offset(offset)
{}

tyr::TextComp::~TextComp()
{
}

void tyr::TextComp::Initialize()
{
	m_pTransform = m_pSceneObject->GetTransform();
	m_pFont = CONTENT_MANAGER->LoadFont(m_TextPath);
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
	 
	SDXL_RenderText(m_pFont->SDXL(), m_Text, { pos.x, pos.y }, static_cast<SDXL::SDXLVec4>(m_Color));
}

void tyr::TextComp::Destroy()
{
}

void tyr::TextComp::SetText(const std::wstring& newText)
{
	m_Text = newText;
}
#ifdef USE_IM_GUI
void tyr::TextComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
	writer.Write(m_Type);
}
#endif
