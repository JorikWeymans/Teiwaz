#pragma once
#include <vector>
#include <typeinfo>
namespace tyr
{
	class Scene;
	struct Transform;
	class BaseComponent;
	class TransformComp;
	class GameContext;
	struct Transform;
	class SceneObject final
	{
	public:
		explicit SceneObject(const Transform& transform, const std::string& name = "new GameObject" + std::to_string(counter));
		~SceneObject();
		
		void Update();
		void FixedUpdate();
#ifdef USE_IM_GUI
		void Debug();
		void RenderEditor();
#endif
		void Render() const;

		void AddComponent(BaseComponent* pComp);
		const TransformComp* GetTransform() const;
		Transform* Transform();

		void SetPositionY(float y);
		
		void Translate(float x, float y);
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
		const std::string& GetName() const { return m_name; }
	private:
		void Initialize();
		std::vector<BaseComponent*> m_pComponents;
		TransformComp* m_pTransform;
		bool m_IsDestroyed;
		std::string m_name;
		friend Scene;
		GameContext const* m_pContext; // weak pointer
		static int counter;
	public:
		SceneObject(const SceneObject&) = delete;
		SceneObject(SceneObject&&) = delete;
		SceneObject& operator=(const SceneObject&) = delete;
		SceneObject& operator=(SceneObject&&) = delete;

		
	};
}
