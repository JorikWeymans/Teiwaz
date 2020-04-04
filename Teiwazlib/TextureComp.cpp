#include "tyrpch.h"
#include "TextureComp.h"
#include "SceneObject.h"
#include "TransformComp.h"
tyr::TextureComp::TextureComp(const std::wstring& texturePath, const PivotMode& pivotMode)
	: m_TexturePath(texturePath)
	, m_pTexture(nullptr)
	, m_pTransform(nullptr)
	, m_Pivot(Vector2(pivotMode))
{
	
}

tyr::TextureComp::~TextureComp()
{
	//Destroy();
	SDXL_DestroyImage(&m_pTexture);
}

void tyr::TextureComp::Initialize()
{
	m_pTransform = m_pSceneObject->GetTransform();

	SDXL_CreateImage(&m_pTexture, m_TexturePath);
	
}

void tyr::TextureComp::Update()
{
}

void tyr::TextureComp::FixedUpdate()
{
}

void tyr::TextureComp::Render() const
{
	const auto pos = m_pTransform->GetPosition();
	const auto scale = m_pTransform->GetScale();
	const auto rot = m_pTransform->GetRotation();
	
	SDXL_RenderImage(m_pTexture, { pos.x, pos.y }, { m_Pivot.x,m_Pivot.y }, { scale.x, scale.y }, rot);
	
}

void tyr::TextureComp::Destroy()
{
	m_pTransform = nullptr;
	SDXL_DestroyImage(&m_pTexture);
	m_TexturePath = L"";
}
