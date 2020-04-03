#include "pch.h"
#include "GameContext.h"
#include "Time.h"

tyr::GameContext::GameContext(Time* pTime)
	:pTime(pTime)
{
}

tyr::GameContext::~GameContext()
{
	SAFE_DELETE(pTime);
}
