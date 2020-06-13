#pragma once
#include <vector>

#define SCENE_SUFFIX ".tyrScene"
namespace tyr
{
	class BinaryWriter;
	class SceneManager;
	class GameContext;
	class SceneObject;
	class BinaryReader;
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		explicit Scene(const std::string& name, const std::string& path);
		
		 ~Scene();
		void Load();
		void UnLoad();
		void AddSceneObject(SceneObject* pObj); //only call this when you are not updating the scene
		void BufferSceneObject(SceneObject* pObj); //Call this when you addSceneObject in Update
		void Update();
		void FixedUpdate();

		_NODISCARD SceneObject* GetFirstSceneObjectWithTag(Tag tag) const;
		_NODISCARD SceneObject* GetFirstObjectWithName(const std::string& name) const;
#ifdef EDITOR_MODE
		void RenderEditor();
		void Save();
		_NODISCARD static Scene* GenerateNew(const std::string& name, const std::string& path);
		
#endif
		
		void Flush();
		void Render() const;

		_NODISCARD const std::string& GetName() const noexcept { return m_Name; }
	private:
		friend SceneManager;
		GameContext const* m_pContext; //Weak pointer
		std::string m_Name, m_Path;
		std::vector<SceneObject*> m_pSceneObjects;
		std::vector<SceneObject*> m_pBufferedObjects;
		bool m_IsLoaded;
#ifdef EDITOR_MODE
		bool m_ItemDoubleClicked = false;
		int m_SelectedItem = -1;
#endif
		
		SceneObject* LoadSceneObject(tyr::BinaryReader& reader, tyr::SceneObject* parent = nullptr);
		
	public:
		Scene() = delete;
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = delete;
		
	};


}
