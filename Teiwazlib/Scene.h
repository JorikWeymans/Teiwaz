#pragma once
#include <vector>

namespace tyr
{
	class SceneManager;
	class GameContext;
	class SceneObject;
	
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize() = 0;
		void AddSceneObject(SceneObject* pObj);

		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render() const;
	private:
		friend SceneManager;
		GameContext* m_pContext;
		std::vector<SceneObject*> m_pSceneObjects;
	};


}
