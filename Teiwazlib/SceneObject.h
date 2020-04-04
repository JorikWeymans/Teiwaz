#pragma once
#include <vector>
#include <typeinfo>
namespace tyr
{
	class Scene;
	struct transform;
	class BaseComponent;
	class TransformComp;
	class GameContext;
	class SceneObject final
	{
	public:
		explicit SceneObject(const transform& transform);
		~SceneObject();
		
		void Update();
		void FixedUpdate();
		void Render() const;

		void AddComponent(BaseComponent* pComp);
		const TransformComp* GetTransform() const;
		
		template <typename T>
		T* GetComponent(unsigned int index = 0) //index used when there are more than one component of the same type on the object.
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
	protected:
		std::vector<BaseComponent*> m_pComponents;
		TransformComp* m_pTransform;
		bool m_IsDestroyed;

		friend Scene;
		GameContext const* m_pContext; // weak pointer
		
	public:
		SceneObject(const SceneObject&) = delete;
		SceneObject(SceneObject&&) = delete;
		SceneObject& operator=(const SceneObject&) = delete;
		SceneObject& operator=(SceneObject&&) = delete;

		
	};
}
