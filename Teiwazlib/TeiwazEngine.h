#pragma once
namespace tyr
{
	class GameContext;
	class TeiwazEngine
	{
	public:
		HRESULT Initialize(HINSTANCE hInstance);
		bool ProcessInput();
		void Update();
		void FixedUpdate();
		
		void Render() const;
		void Run();

		void Cleanup();

	protected:
		GameContext* m_pContext = nullptr;
		float m_FixedTimeStep = 0.02f; // 50 frames per second;
		
	};


}
