#pragma once
#include <string>
//When using IM Gui, reserve some extra space for it

#ifdef USE_IM_GUI
#define ENGINE_SPACING_LEFT 400
#define ENGINE_SPACING_RIGHT 400
#define ENGINE_SPACING_TOP 20
#else
#define ENGINE_SPACING_LEFT 0
#define ENGINE_SPACING_RIGHT 0
#define ENGINE_SPACING_TOP 0
#endif



namespace tyr
{
	class GameContext;
	class SceneManager;
	class Vector2;
	class TeiwazEngine
	{
	public:
		explicit TeiwazEngine(float fixedTimeStep);
		virtual ~TeiwazEngine() = default;
		

		static void GameToEngineSpace(GameContext const* pContext, Vector2* pPos);
		void Run();

		static bool WantQuit;
	protected:
		bool ProcessInput();
		virtual void LoadGame() = 0;
		virtual void Cleanup() = 0;

		HRESULT Initialize(HINSTANCE hInstance, const std::string& name, int width, int height);
		
		SceneManager* m_pSceneManager;
		GameContext* m_pContext;
		float m_FixedTimeStep ; 

	public:
		
	};


}
