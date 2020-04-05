#include "stdafx.h"
#include "BubbleBobble.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MiniginScene.h"
#include "MainScene.h"

bub::BubbleBobble::BubbleBobble()
	: TeiwazEngine(0.02f) // 50 frames per second;
{
}

void bub::BubbleBobble::Initialize(HINSTANCE hinstance)
{

	UNREFERENCED_PARAMETER(hinstance);
	tyr::TeiwazEngine::Initialize(hinstance, "BubbleBobble", 768, 672);
	
}

bool bub::BubbleBobble::ProcessInput()
{
	SDXL::SDXL_EVENT event;
	SDXL_PollEvent(event);
	if (event.type == SDXL::SDXL_EventType::SDXL_QUIT)
		return false;


	return true;
}

void bub::BubbleBobble::LoadGame()
{
	//m_pSceneManager->AddScene(new MiniginScene());
	m_pSceneManager->AddScene(new MainScene());
}

void bub::BubbleBobble::Cleanup()
{
	
}
