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
#ifdef USE_IM_GUI
		virtual void Debug();
#endif
		virtual void Render() const;
		
	protected:
		friend SceneManager;
		GameContext const* m_pContext; //Weak pointer
	private:

		std::vector<SceneObject*> m_pSceneObjects;
	};


}
