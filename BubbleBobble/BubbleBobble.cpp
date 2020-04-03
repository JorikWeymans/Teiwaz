#include "stdafx.h"
#include "BubbleBobble.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MiniginScene.h"

bub::BubbleBobble::BubbleBobble()
	: TeiwazEngine(0.02f) // 50 frames per second;
{
}

void bub::BubbleBobble::Initialize(HINSTANCE hinstance)
{

	UNREFERENCED_PARAMETER(hinstance);
	tyr::TeiwazEngine::Initialize(hinstance, "BubbleBobble", 640, 480);
	
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
	m_pSceneManager->AddScene(new MiniginScene());
}

void bub::BubbleBobble::Cleanup()
{
	
}
