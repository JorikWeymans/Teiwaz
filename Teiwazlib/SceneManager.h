#pragma once
#include <vector>
namespace  tyr
{
	class BinaryReader;
	class GameContext;
	class Scene;
#ifdef EDITOR_MODE
	class EUI;
#endif
	class SceneManager final
	{
	public:
		SceneManager();
		~SceneManager();
		void Initialize(GameContext* pContext);

		void AddScene(Scene* pScene);
		void SetCurrentScene(const std::string& SceneName);
		void Update();
		void FixedUpdate();

		void Flush() { m_WantFlush = true; }
		Scene* GetCurrentScene() const { return m_pCurrentScene; }
#ifdef EDITOR_MODE
		void SaveCurrentScene();
		void SetCurrentSceneName(const std::string& name);
		const std::string& GetCurrentSceneName() const;
		bool DoesSceneExist(std::string& sceneName);
		void Render();
#else
		void Render() const;
#endif
		
	private:
#ifdef EDITOR_MODE
		void RenderEditor();


		EUI* m_pEditorUI;
#endif
		void FlushCurrentScene();
		
		GameContext* m_pContext; //Weak ptr
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene;
		bool m_WantFlush;


	};


}
