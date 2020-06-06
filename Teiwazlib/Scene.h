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
	class Scene
	{
	public:
		explicit Scene(const std::string& name);
		explicit Scene(const std::string& name, const std::string& path);
		
		virtual ~Scene();
		virtual void Load();
		void AddSceneObject(SceneObject* pObj); //only call this when you are not updating the scene
		void BufferSceneObject(SceneObject* pObj); //Call this when you addSceneObject in Update
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Debug() {};

		
#ifdef EDITOR_MODE
		void RenderEditor();
		void Save();
		_NODISCARD static Scene* GenerateNewScene(const std::string& name, const std::string& path);
		
#endif
		void Flush();
		virtual void Render() const;

		const std::string& GetName() const { return m_Name; }
	protected:
		friend SceneManager;
		GameContext const* m_pContext; //Weak pointer
		
	private:
		std::string m_Name, m_Path;
		std::vector<SceneObject*> m_pSceneObjects;
		std::vector<SceneObject*> m_pBufferedObjects;
		SceneObject* LoadSceneObject(tyr::BinaryReader& reader, tyr::SceneObject* parent = nullptr);

#ifdef EDITOR_MODE
		bool m_ItemDoubleClicked = false;
		int m_SelectedItem = -1;
#endif
	};


}
