#include "stdafx.h"
#include "MiniginScene.h"

bub::MiniginScene::~MiniginScene()
{
	SDXL_DestroyImage(&m_pBackground);
	SDXL_DestroyImage(&m_pLogo);
	SDXL_DestroyFont(&m_pFont);
}

void bub::MiniginScene::Initialize()
{
	
	auto hr = SDXL_CreateImage(&m_pBackground, L"./Data/Textures/Background.png");
	hr = SDXL_CreateImage(&m_pLogo, L"./Data/Textures/Logo.png");
	hr  = SDXL_CreateFont(&m_pFont, L"./Data/Fonts/Consolas_32.fnt");
	if(FAILED(hr))
	{
		
	}
}

void bub::MiniginScene::Render() const
{
	SDXL::SDXLRect srcRect{ 0,0,640.f,480.f};
	
	SDXL_RenderImage(m_pBackground, { 0,0 }, { 0,0 }, { 1,1}, srcRect, 0);

	srcRect.width = 208.f;
	srcRect.height = 64.f;
	SDXL_RenderImage(m_pLogo, { 640 / 2, 480 / 2 }, { 0.5,0.5 }, { 1,1 }, srcRect, 0);
	SDXL_RenderDebugLine({ 10,10 }, { 620,10 }, { 255,255,255,255 });
	SDXL_RenderText(m_pFont, L"Programming 4 assignment ", { 150.f,10.f });
	
}
