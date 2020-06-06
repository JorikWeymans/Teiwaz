#pragma once
#include <Vector>
#include <string>
namespace tyr
{
	class BinaryWriter;
	class Scene;
	class ETabScenes;
	class CMScenes final
	{
	public:
		CMScenes() = default;
		~CMScenes();
		
		_NODISCARD auto Begin()        noexcept { return m_pScenes.begin();  }
		_NODISCARD auto End()          noexcept { return m_pScenes.end();    }
		_NODISCARD auto CBegin() const noexcept { return m_pScenes.cbegin(); }
		_NODISCARD auto CEnd()   const noexcept { return m_pScenes.cend();   }
		
		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Scene* pData) noexcept;
		
		_NODISCARD Scene* GetScene(const std::string& sceneName) const noexcept;
		_NODISCARD Scene* GetScene(SceneID id) const noexcept;

#ifdef EDITOR_MODE
		void RenderEditor();
		void Save(BinaryWriter& writer);
		
#endif
	private:
		std::vector<Scene*> m_pScenes; // un-initialized Scenes by default
#ifdef EDITOR_MODE
		
#endif
	public:
		CMScenes(const CMScenes&) = delete;
		CMScenes(CMScenes&&) = delete;
		CMScenes& operator=(const CMScenes&) = delete;
		CMScenes& operator=(CMScenes&&) = delete;
	};
}
