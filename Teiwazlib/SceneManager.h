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
		void SetCurrentScene(SceneID id);
		void Update();
		void FixedUpdate();

		void Flush() { m_WantFlush = true; }
		_NODISCARD Scene* GetCurrentScene() const noexcept { return m_pCurrentScene; }
		const std::string& GetCurrentSceneName() const;
#ifdef EDITOR_MODE
		void SaveCurrentScene();
		void SetCurrentSceneName(const std::string& name);
		
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
		Scene* m_pCurrentScene;
		bool m_WantFlush;


	};


}
