#include "tyrpch.h"
#include "GameContext.h"
#include "Time.h"
#include "InputHandler.h"
tyr::GameContext::GameContext(Time* pTime, InputHandler* pInput)
	: pTime(pTime)
	, pInput(pInput)
{
}

tyr::GameContext::~GameContext()
{
	SAFE_DELETE(pTime);
	SAFE_DELETE(pInput);
}
