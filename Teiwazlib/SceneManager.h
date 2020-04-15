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
		void SetCurrentScene(const std::string& SceneName);
		void Update();
		void FixedUpdate();

		
		void Flush() { m_WantFlush = true; }
#ifdef USE_IM_GUI
		void Render();
#else
		void Render() const;
#endif
	private:
#ifdef USE_IM_GUI
		void RenderEditor();
		void MainMenu();
		void SceneView(SDXL_ImGuiWindowFlags flags);
		void Inspector(SDXL_ImGuiWindowFlags flags);
		void Bottom(SDXL_ImGuiWindowFlags flags);
		
		void SaveCurrentScene();
#endif
		void FlushCurrentScene();
		
		GameContext* m_pContext; //Weak ptr
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene;
		bool m_WantFlush;


	};


}
