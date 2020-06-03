#pragma once
#include <Vector>
#include <string>
namespace tyr
{
	class BinaryWriter;
	class Scene;
	class CMScenes final
	{
	public:
		CMScenes() = default;
		~CMScenes();

		
		auto Begin()        noexcept { return m_pScenes.begin(); }
		auto End()          noexcept { return m_pScenes.end(); }
		auto CBegin() const noexcept { return m_pScenes.cbegin(); }
		auto CEnd() const   noexcept { return m_pScenes.cend(); }
		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Scene* pData) noexcept;
		
		Scene* GetScene(const std::string& sceneName) const noexcept;
		Scene* GetScene(SceneID id) const noexcept;

#ifdef EDITOR_MODE
		void RenderEditor();
		void SaveScenes(BinaryWriter& writer);
#endif
	private:
		std::vector<Scene*> m_pScenes; // un-initialized Scenes by default
	public:
		CMScenes(const CMScenes&) = delete;
		CMScenes(CMScenes&&) = delete;
		CMScenes& operator=(const CMScenes&) = delete;
		CMScenes& operator=(CMScenes&&) = delete;
	};
}
