#pragma once
#include <vector>
namespace  tyr
{
	class BinaryReader;
	class GameContext;
	class Scene;
	class SceneManager final
	{
	public:
		explicit SceneManager(GameContext* pContext);
		~SceneManager();
		
		void AddScene(Scene* pScene);

		void Update();
		void FixedUpdate();void FlushCurrentScene();
		void Flush() { m_WantFlush = true; }
#ifdef USE_IM_GUI
		void Render();
#else
		void Render() const;
#endif
	private:
#ifdef USE_IM_GUI
		void RenderEditor();
		void SaveCurrentScene();


#endif
		GameContext* m_pContext; //Weak ptr
		std::vector<Scene*> m_pScenes;

		bool m_WantFlush;


	};


}
