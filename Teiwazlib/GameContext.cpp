#include "tyrpch.h"
#include "GameContext.h"
#include "Time.h"
#include "InputHandler.h"
#include "Vectors.h"
#include "Physics.h"
#include "GameState.h"
#include "SceneManager.h"

tyr::GameContext::GameContext(Time* pTime, InputHandler* pInput, Rect* pGameSpace, Physics* pPhysics, SceneManager* pSceneManager)
	: pTime(pTime)
	, pInput(pInput)
	, pGameSpace(pGameSpace)
	, pPhysics(pPhysics)
	, pSceneManager(pSceneManager)
	, pGameState(new GameState())
	, paused(false)
#ifdef EDITOR_MODE
	, pEditorUI(nullptr)
#endif
{
}

tyr::GameContext::~GameContext()
{
	SAFE_DELETE(pTime);
	SAFE_DELETE(pInput);
	SAFE_DELETE(pGameSpace);
	SAFE_DELETE(pPhysics);
	SAFE_DELETE(pGameState);
}
