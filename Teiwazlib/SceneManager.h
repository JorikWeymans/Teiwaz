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
		GameContext* m_pContext; //Weak ptr
		std::vector<Scene*> m_pScenes;
	};


}
