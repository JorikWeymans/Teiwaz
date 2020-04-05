#include "tyrpch.h"
#include "TeiwazEngine.h"

#include <chrono>
#include <sstream>
#include "GameContext.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ContentManager.h"

tyr::TeiwazEngine::TeiwazEngine(float fixedTimeStep)
	: m_pSceneManager(nullptr)
	, m_pContext(nullptr)
	, m_FixedTimeStep(fixedTimeStep)  
{
}

HRESULT tyr::TeiwazEngine::Initialize(HINSTANCE hInstance, const std::string& name, int width, int height)
{
	auto hr =  SDXL_Init(hInstance, name, width, height);
	hr = SDXL_InitRenderers(L"./Data/Effects/ImageRenderer.fx",
		L"./Data/Effects/TextRenderer.fx",
		L"./Data/Effects/DebugRenderer.fx");

	m_pContext = new GameContext(new Time());
	m_pSceneManager = new SceneManager(m_pContext);

	ContentManager::GetInstance()->Initialize(L"./Data/");
	

	
	return hr;

	
}

void tyr::TeiwazEngine::Run()
{
	using namespace std::chrono;

	
	LoadGame();
	
	auto previousTime = high_resolution_clock::now();
	float fixedElapsed = 0.0f;
	
	while(ProcessInput())
	{
		m_pSceneManager->Update();
		if (fixedElapsed >= m_FixedTimeStep)
		{
			m_pContext->pTime->fixedDeltaTime = fixedElapsed;
			m_pSceneManager->FixedUpdate();
			
			fixedElapsed = 0;
		}

		m_pSceneManager->Render();

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
