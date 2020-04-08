#include "tyrpch.h"
#include "GameContext.h"
#include "Time.h"
#include "InputHandler.h"
#include "Vectors.h"
tyr::GameContext::GameContext(Time* pTime, InputHandler* pInput, Rect* pGameSpace)
	: pTime(pTime)
	, pInput(pInput)
	, pGameSpace(pGameSpace)
{
}

tyr::GameContext::~GameContext()
{
	SAFE_DELETE(pTime);
	SAFE_DELETE(pInput);
	SAFE_DELETE(pGameSpace);
}
