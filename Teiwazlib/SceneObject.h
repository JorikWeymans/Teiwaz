#pragma once
#include <vector>
#include <typeinfo>
namespace tyr
{
	class BinaryWriter;
	class Scene;
	struct Transform;
	class BaseComponent;
	class TransformComp;
	class GameContext;
	struct Transform;
	class SceneObject final
	{
	public:
		explicit SceneObject(const Transform& transform, const std::string& name = "new GameObject" + std::to_string(counter), bool AppendCounter = false);
		explicit SceneObject(TransformComp* pTransform, const std::string& name = "new GameObject" + std::to_string(counter), bool AppendCounter = false);
		explicit SceneObject();
		
		~SceneObject();
		
		void Update();
		void FixedUpdate();
#ifdef EDITOR_MODE
		void Debug();
		void RenderEditor(bool showChildren);
		void Save(BinaryWriter& writer);
		void AddComponentButton();
#endif
		void Render() const;

		void AddComponent(BaseComponent* pComp);
		void AddChild(SceneObject* pChild);
		TransformComp* GetTransform() const;

		void Translate(float x, float y);
		template <typename T>
		T* GetComponent(unsigned int index = 0) const  //index used when there are more than one component of the same type on the object.
		{
			unsigned int currIndex = 0;
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == typeid(T))
				{
					if (currIndex == index)
						return static_cast<T*>(component);
					currIndex++;
				}
					
			}
			return nullptr;
		}
		
		const GameContext* GetGameContext() const;
		const std::string& GetName() const { return m_name; }
		const SceneObject* GetParent() const { return m_pParent; }
	private:
		friend Scene;
		void Initialize();
		
		std::vector<BaseComponent*> m_pComponents;
		std::vector<SceneObject*> m_pChilds;
		SceneObject* m_pParent;
		TransformComp* m_pTransform;
		bool m_IsDestroyed;
		std::string m_name;
		GameContext const* m_pContext; // weak pointer
		static int counter;

#ifdef EDITOR_MODE
		int m_SelectedItem;
#endif
	public:
		SceneObject(const SceneObject&) = delete;
		SceneObject(SceneObject&&) = delete;
		SceneObject& operator=(const SceneObject&) = delete;
		SceneObject& operator=(SceneObject&&) = delete;

		
	};
}
