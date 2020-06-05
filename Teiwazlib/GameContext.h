#pragma once
namespace tyr
{
	class SceneManager;
	class Time;
	class InputHandler;
	class Rect;
	class Physics;
	class EUI;
	class GameContext final
	{
	public:
		explicit GameContext(Time* pTime, InputHandler* pInput, Rect* pGameSpace, Physics* pPhysics, SceneManager* pSceneManager);
		~GameContext();
		
		Time* pTime;
		InputHandler* pInput;
		Rect* pGameSpace;
		Physics* pPhysics;
		SceneManager* const pSceneManager; //weak ptr
		bool paused;
#ifdef EDITOR_MODE
		EUI* pEditorUI;
#endif

	public:
		GameContext(const GameContext&) = delete;
		GameContext(GameContext&&) = delete;
		GameContext& operator=(const GameContext&) = delete;
		GameContext& operator=(GameContext&&) = delete;
	};


}
