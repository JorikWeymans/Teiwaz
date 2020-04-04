#include "stdafx.h"
#include "MiniginScene.h"
#include "Transform.h"
#include "SceneObject.h"
#include "TeiwazComps.h"
bub::MiniginScene::~MiniginScene()
{
	SDXL_DestroyFont(&m_pFont);
}

void bub::MiniginScene::Initialize()
{
	
	auto hr  = SDXL_CreateFont(&m_pFont, L"./Data/Fonts/Consolas_32.fnt");
	if(FAILED(hr))
	{
		
	}


	auto pBackground = new tyr::SceneObject(tyr::transform(tyr::Vector2(0.0f, 0.0f)));
	pBackground->AddComponent(new tyr::TextureComp(L"./Data/Textures/Background.png"));
	
	auto pLogo = new tyr::SceneObject(tyr::transform(tyr::Vector2(640.f / 2 -102, 480.f / 2 - 32)));
	pLogo->AddComponent(new tyr::TextureComp(L"./Data/Textures/Logo.png"));

	AddSceneObject(pBackground);
	AddSceneObject(pLogo);
	
}

void bub::MiniginScene::Render() const
{
	tyr::Scene::Render();
	
//	SDXL_RenderImage(m_pLogo, { 640 / 2, 480 / 2 }, { 0.5,0.5 }, { 1,1 }, srcRect, 0);
	SDXL_RenderDebugLine({ 10,10 }, { 620,10 }, { 255,255,255,255 });
	SDXL_RenderText(m_pFont, L"Programming 4 assignment ", { 150.f,10.f });
	
}
