#include "tyrpch.h"
#include "GameContext.h"
#include "Time.h"
#include "InputHandler.h"
#include "Vectors.h"
#include "Physics.h"
tyr::GameContext::GameContext(Time* pTime, InputHandler* pInput, Rect* pGameSpace, Physics* pPhysics)
	: pTime(pTime)
	, pInput(pInput)
	, pGameSpace(pGameSpace)
	, pPhysics(pPhysics)
{
}

tyr::GameContext::~GameContext()
{
	SAFE_DELETE(pTime);
	SAFE_DELETE(pInput);
	SAFE_DELETE(pGameSpace);
	SAFE_DELETE(pPhysics);
}
