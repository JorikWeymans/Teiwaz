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
#ifdef USE_IM_GUI
		virtual void Debug();
		void Save(BinaryWriter& writer);
		void Flush();
#endif
		virtual void Render() const;

		const std::string& GetName() const { return m_Name; }
	protected:
		friend SceneManager;
		GameContext const* m_pContext; //Weak pointer
		
	private:
		std::string m_Name;
		std::vector<SceneObject*> m_pSceneObjects;
	};


}
