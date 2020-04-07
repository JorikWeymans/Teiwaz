#pragma once
#include <string>

//When using IM Gui, reserve some extra space for it
#ifdef USE_IM_GUI
#define EXTRA_SCREEN_SIZE 400
#else
#define EXTRA_SCREEN_SIZE 0
#endif


namespace tyr
{
	class GameContext;
	class SceneManager;
	class TeiwazEngine
	{
	public:
		explicit TeiwazEngine(float fixedTimeStep);
		virtual ~TeiwazEngine() = default;
		

		
		void Run();

		
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
