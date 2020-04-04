#pragma once
#include <vector>

namespace tyr
{
	struct transform;
	class BaseComponent;
	class TransformComp;
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
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}
		
	protected:
		std::vector<BaseComponent*> m_pComponents;
		TransformComp* m_pTransform;
		bool m_IsDestroyed;

	public:
		SceneObject(const SceneObject&) = delete;
		SceneObject(SceneObject&&) = delete;
		SceneObject& operator=(const SceneObject&) = delete;
		SceneObject& operator=(SceneObject&&) = delete;

		
	};
}
