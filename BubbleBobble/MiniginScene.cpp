#include "stdafx.h"
#include "MiniginScene.h"
#include "Transform.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include "Color.h"
bub::MiniginScene::~MiniginScene()
{
}

void bub::MiniginScene::Initialize()
{
	
	//auto pBackground = new tyr::SceneObject(tyr::Transform(tyr::Vector2(0.0f, 0.0f)));
	//AddSceneObject(pBackground);
	//pBackground->AddComponent(new tyr::TextureComp("Textures/Background.png"));
	//
	//
	//auto pLogo = new tyr::SceneObject(tyr::Transform(tyr::Vector2(640.f / 2, 480.f / 2)));
	//AddSceneObject(pLogo);
	//pLogo->AddComponent(new tyr::TextureComp("Textures/Logo.png", tyr::PivotMode::Center));
	//
	//
	//auto pText = new tyr::SceneObject(tyr::Transform(tyr::Vector2(640.f / 2 - 154, 10)));
	//AddSceneObject(pText);
	//pText->AddComponent(new tyr::TextComp("Fonts/Arcade_20.fnt", "Programming 4 assignment", ColorWhite, tyr::Vector2(0.f, 0.f)));
	//
	//auto pFPS = new tyr::SceneObject(tyr::Transform(tyr::Vector2(5.0f, 10.0f)));
	//AddSceneObject(pFPS);
	//pFPS->AddComponent(new tyr::TextComp("Fonts/Arcade_20.fnt", "Text", ColorYellow));
	//pFPS->AddComponent(new tyr::TextComp("Fonts/Arcade_20.fnt", "Text 1234.00", ColorRed, tyr::Vector2(0,20)));
	//pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::Update, 0));
	//pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::FixedUpdate, 1));
	
}

void bub::MiniginScene::Render() const
{
	tyr::Scene::Render();
	
//	SDXL_RenderImage(m_pLogo, { 640 / 2, 480 / 2 }, { 0.5,0.5 }, { 1,1 }, srcRect, 0);
	SDXL_RenderDebugLine({ 10,10 }, { 620,10 }, { 255,255,255,255 });

	
}
