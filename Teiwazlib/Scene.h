#pragma once
#include <vector>

namespace tyr
{
	class BinaryWriter;
	class SceneManager;
	class GameContext;
	class SceneObject;
	
	class Scene
	{
	public:
		Scene(const std::string& name);
		virtual ~Scene();
		virtual void Initialize() = 0;
		void AddSceneObject(SceneObject* pObj);

		virtual void Update();
		virtual void FixedUpdate();
		virtual void Debug() {};
#ifdef USE_IM_GUI
		void RenderEditor();
		void Save(BinaryWriter& writer);

		
#endif
		void Flush();
		virtual void Render() const;

		const std::string& GetName() const { return m_Name; }
	protected:
		friend SceneManager;
		GameContext const* m_pContext; //Weak pointer
		
	private:
		std::string m_Name;
		std::vector<SceneObject*> m_pSceneObjects;
#ifdef USE_IM_GUI
		bool m_ItemDoubleClicked = false;
		int m_SelectedItem = -1;
#endif
	};


}
