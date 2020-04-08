#pragma once
#include <vector>
namespace  tyr
{
	class GameContext;
	class Scene;
	class SceneManager final
	{
	public:
		explicit SceneManager(GameContext* pContext);
		~SceneManager();
		
		void AddScene(Scene* pScene);

		void Update();
		void FixedUpdate();


		void Render() const;
		
	private:
#ifdef USE_IM_GUI
		void Debug() const;
		void DebugGameOutline() const;
#endif
		GameContext* m_pContext; //Weak ptr
		std::vector<Scene*> m_pScenes;




	};


}
