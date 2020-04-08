#include "tyrpch.h"
#include "TextureComp.h"
#include "SceneObject.h"
#include "TransformComp.h"
#include "ContentManager.h"
#include "Texture.h"
#include <iostream>
#include "TeiwazEngine.h"

tyr::TextureComp::TextureComp(const std::wstring& texturePath, const PivotMode& pivotMode, const Rect& rect)
	: m_TexturePath(texturePath)
	, m_pTexture(nullptr)
	, m_pTransform(nullptr)
	, m_Pivot(Vector2(pivotMode))
	, m_SrcRect(rect)
{
	
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
