#include "stdafx.h"
#include "MainScene.h"
#include "Transform.h"
#include "TyrComps.h"
#include "SceneObject.h"

void bub::MainScene::Initialize()
{
	auto pBackground = new tyr::SceneObject(tyr::transform(tyr::Vector2(0.0f, 0.0f)));
	AddSceneObject(pBackground);
	pBackground->AddComponent(new tyr::TextureComp(L"Textures/Ref2.png"));

	float scale = 3.f * 8.f; //game scale from original scale;
	
	auto pinkSquare = new tyr::SceneObject(tyr::transform(tyr::Vector2(0.0f, 0.0f), tyr::Vector2(scale, scale)));
	AddSceneObject(pinkSquare);
	pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));
}
