#include "pch.h"
#include "TeiwazEngine.h"
#include <SDXLLibrary.h>
#pragma warning(disable : 4091)
#include <SDXLStructs.h>
#include <chrono>
#include <sstream>
#include "GameContext.h"
#include "Time.h"

HRESULT tyr::TeiwazEngine::Initialize(HINSTANCE hInstance)
{
	auto hr =  SDXL_Init(hInstance, "TeiwazEngine", 1280, 720);
	hr = SDXL_InitRenderers(L"./Data/Effects/ImageRenderer.fx",
		L"./Data/Effects/TextRenderer.fx",
		L"./Data/Effects/DebugRenderer.fx");



	OutputDebugStringA("hey");
	return hr;

	
}

bool tyr::TeiwazEngine::ProcessInput()
{
	SDXL::SDXL_EVENT event;
	SDXL_PollEvent(event);
	if (event.type == SDXL::SDXL_EventType::SDXL_QUIT)
		return false;



	return true;
	
}

void tyr::TeiwazEngine::Update()
{
	
	
}

void tyr::TeiwazEngine::FixedUpdate()
{
}

void tyr::TeiwazEngine::Cleanup()
{
	SAFE_DELETE(m_pContext);
}

void tyr::TeiwazEngine::Render() const
{
	SDXL_Clear();

	//Draw images here;
	
	SDXL_Present();
}

void tyr::TeiwazEngine::Run()
{
	using namespace std::chrono;
	
	m_pContext = new GameContext(new Time());

	auto previousTime = high_resolution_clock::now();
	float fixedElapsed = 0.0f;
	
	while(ProcessInput())
	{
		Update();
		if (fixedElapsed >= m_FixedTimeStep)
		{
			m_pContext->pTime->fixedDeltaTime = fixedElapsed;
			FixedUpdate();
			
			fixedElapsed = 0;
		}

		Render();

		// timings for next frame
		const auto thisTime = high_resolution_clock::now();
		const auto elapsed = static_cast<float>(duration_cast<microseconds>(thisTime - previousTime).count()) / 1000000;
		m_pContext->pTime->deltaTime = elapsed;
		fixedElapsed += elapsed;
		
		previousTime = thisTime;
	}

	Cleanup();
}
