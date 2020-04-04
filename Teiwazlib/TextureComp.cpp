#include "tyrpch.h"
#include "TextureComp.h"
#include "SceneObject.h"
#include "TransformComp.h"
tyr::TextureComp::TextureComp(const std::wstring& texturePath)
	: m_TexturePath(texturePath)
	, m_pTexture(nullptr)
	, m_pTranform(nullptr)
{
	
}

tyr::TextureComp::~TextureComp()
{
	Destroy();
}

void tyr::TextureComp::Initialize()
{
	m_pTranform = m_pSceneObject->GetTransform();

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
	const auto pos = m_pTranform->GetPosition();
	const auto scale = m_pTranform->GetScale();
	const auto rot = m_pTranform->GetRotation();
	
	SDXL_RenderImage(m_pTexture, { pos.x, pos.y }, { 0,0 }, { scale.x, scale.y }, rot);
	
}

void tyr::TextureComp::Destroy()
{
	m_pTranform = nullptr;
	SDXL_DestroyImage(&m_pTexture);
	m_TexturePath = L"";
}
