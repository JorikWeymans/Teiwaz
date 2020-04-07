#include "stdafx.h"
#include "BubbleBobble.h"
#include "SceneManager.h"
#include "MainScene.h"

bub::BubbleBobble::BubbleBobble()
	: TeiwazEngine(0.02f) // 50 frames per second;
{
}

void bub::BubbleBobble::Initialize(HINSTANCE hinstance)
{

	tyr::TeiwazEngine::Initialize(hinstance, "BubbleBobble", 768, 672);
	
}

void bub::BubbleBobble::LoadGame()
{
	//m_pSceneManager->AddScene(new MiniginScene());
	m_pSceneManager->AddScene(new MainScene());
}

void bub::BubbleBobble::Cleanup()
{
	
}
