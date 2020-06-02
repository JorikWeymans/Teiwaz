#pragma once
#include <Vector>
#include <string>
namespace tyr
{
	class Scene;
	class CMScenes final
	{
	public:
		explicit CMScenes(const std::string& absoluteSceneFolder);
		~CMScenes();

		
		auto Begin() noexcept        { return m_pScenes.begin(); }
		auto End() noexcept          { return m_pScenes.end(); }
		auto CBegin() const noexcept { return m_pScenes.cbegin(); }
		auto CEnd() const noexcept   { return m_pScenes.cend(); }

		
		Scene* GetScene(const std::string& sceneName) const noexcept;
		Scene* GetScene(SceneID id) const noexcept;
		
		void RenderEditor();
	private:
		std::vector<Scene*> m_pScenes; // un-initialized Scenes by default
	public:
		CMScenes(const CMScenes&) = delete;
		CMScenes(CMScenes&&) = delete;
		CMScenes& operator=(const CMScenes&) = delete;
		CMScenes& operator=(CMScenes&&) = delete;
	};
}
