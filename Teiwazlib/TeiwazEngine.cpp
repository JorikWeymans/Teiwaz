#include "tyrpch.h"
#include "TeiwazEngine.h"

#include <chrono>
#include <sstream>
#include "GameContext.h"
#include "Time.h"
#include "InputHandler.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ContentManager.h"
#include "Vectors.h"
#include "Physics.h"
bool tyr::TeiwazEngine::WantQuit = false;
tyr::TeiwazEngine::TeiwazEngine(float fixedTimeStep)
	: m_pSceneManager(nullptr)
	, m_pContext(nullptr)
	, m_FixedTimeStep(fixedTimeStep)  
{
}

HRESULT tyr::TeiwazEngine::Initialize(HINSTANCE hInstance, const std::string& name, int gameWidth, int GameHeight)
{
	auto nameToUse = name;
#ifdef USE_IM_GUI
	nameToUse += " (Editor)";
#endif

	auto hr =  SDXL_Init(hInstance, nameToUse, gameWidth + ENGINE_SPACING_LEFT + ENGINE_SPACING_RIGHT, GameHeight + ENGINE_SPACING_TOP + ENGINE_SPACING_BOT);
	
	hr = SDXL_InitRenderers(L"./Data/Effects/ImageRenderer.fx",
		L"./Data/Effects/TextRenderer.fx",
		L"./Data/Effects/DebugRenderer.fx");

	m_pContext = new GameContext(new Time(), 
								new InputHandler(), 
								new Rect(ENGINE_SPACING_RIGHT, ENGINE_SPACING_BOT, static_cast<float>(gameWidth), static_cast<float>(GameHeight)),
								new Physics());
	m_pSceneManager = new SceneManager(m_pContext);

	ContentManager::GetInstance()->Initialize(L"./Data/");

	return hr;

	
}

void tyr::TeiwazEngine::GameToEngineSpace(GameContext const* pContext, Vector2* pPos)
{
	auto space = pContext->pGameSpace;

	pPos->x += ENGINE_SPACING_LEFT;
	pPos->y = space->height - pPos->y + ENGINE_SPACING_TOP;
}

void tyr::TeiwazEngine::Run()
{
	using namespace std::chrono;

	
	LoadGame();

	m_pContext->pInput->AddAction("QUIT", tyr::ButtonState::Pressed, VK_ESCAPE);
	
	auto previousTime = high_resolution_clock::now();
	float fixedElapsed = 0.0f;
	
	while(ProcessInput())
	{
		m_pSceneManager->Update();
		if (fixedElapsed >= m_FixedTimeStep)
		{
			m_pContext->pTime->fixedDeltaTime = fixedElapsed;
			m_pSceneManager->FixedUpdate();

			m_pSceneManager->Render(); // TODO: enable vsync, otherwise leave it here
			fixedElapsed = 0;
		}

		

		// timings for next frame
		const auto thisTime = high_resolution_clock::now();
		const auto elapsed = static_cast<float>(duration_cast<microseconds>(thisTime - previousTime).count()) / 1000000;
		m_pContext->pTime->deltaTime = elapsed;
		fixedElapsed += elapsed;
		
		previousTime = thisTime;
	}

	ContentManager::Destroy();
	
	Cleanup();
	
	SAFE_DELETE(m_pContext);
	SAFE_DELETE(m_pSceneManager);
}

bool tyr::TeiwazEngine::ProcessInput()
{
	SDXL::SDXL_EVENT event;
	SDXL_PollEvent(event);
	if (event.type == SDXL::SDXL_EventType::SDXL_QUIT)
		return false;
	
	m_pContext->pInput->Update();
	if (WantQuit) return false;
	
	return !m_pContext->pInput->IsActionTriggered("QUIT");
}
