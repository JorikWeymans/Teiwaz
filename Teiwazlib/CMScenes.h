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
		~CMScenes() = default;

		auto Begin() noexcept { return m_Scenes.begin(); }
		auto End() noexcept { return m_Scenes.end(); }
		auto CBegin() const noexcept { return m_Scenes.cbegin(); }
		auto CEnd() const noexcept { return m_Scenes.cend(); }
	private:
		std::vector<Scene*> m_Scenes;
	public:
		CMScenes(const CMScenes&) = delete;
		CMScenes(CMScenes&&) = delete;
		CMScenes& operator=(const CMScenes&) = delete;
		CMScenes& operator=(CMScenes&&) = delete;
	};
}
