#pragma once
#include <vector>
#include <typeinfo>
#include "BaseComponent.h"
#include "TyrEnums.h"
#define OBJECT_NAME_MAX_CHAR 25
namespace tyr
{
	class BinaryWriter;
	class Scene;
	struct Transform;
	//class BaseComponent;
	class TransformComp;
	class GameContext;
	struct Transform;
	class SceneObject final
	{
	public:
		explicit SceneObject(const Transform& transform, 
							 const std::string& name = "new GameObject" + std::to_string(counter), 
							 Tag tag = Tag::None, bool AppendCounter = false);
		explicit SceneObject(TransformComp* pTransform, 
							 const std::string& name = "new GameObject" + std::to_string(counter), 
							 Tag tag = Tag::None, bool AppendCounter = false);
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

		template <typename T>
		T* AddComponent(T* pComp) //return the comp so you can do T* comp = AddComponent(new T());
		{
			auto savedPointer = static_cast<BaseComponent*>(pComp);
			auto found = std::find(m_pComponents.begin(), m_pComponents.end(), savedPointer);
			if (found == m_pComponents.end())
			{
				savedPointer->m_pSceneObject = this;
				savedPointer->Initialize();

				m_pComponents.emplace_back(savedPointer);
				
			}
			return pComp;
			
		}
		void AddChild(SceneObject* pChild);
		void Translate(float x, float y);
		
		TransformComp* GetTransform() const noexcept { return m_pTransform; }
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
		
		const GameContext* GetGameContext() const noexcept { return m_pContext; };
		const std::string& GetName()        const noexcept { return m_name; }
		const SceneObject* GetParent()      const noexcept { return m_pParent; }
		Tag                GetTag()         const noexcept { return m_Tag; }

#ifdef EDITOR_MODE
		std::string GetEditorName() const { return m_name + m_UniqueId; };
#endif
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
		Tag m_Tag;

		
		static int counter;

#ifdef EDITOR_MODE
		int m_SelectedItem;
		std::string m_UniqueId; //if you don't use a unique id, Only the first object with the same name will be selected
		char m_ChangedObjectName[OBJECT_NAME_MAX_CHAR];

		int m_TagCount, m_SelectedTag;
		std::vector<std::string> m_TagItems;

		void RenderProperties();
		void PropertyChangeName(std::string& id);
		void PropertyTag(std::string& id);

		static int TagToArrayIndex(Tag theTag);
		
#endif
	public:
		SceneObject(const SceneObject&) = delete;
		SceneObject(SceneObject&&) = delete;
		SceneObject& operator=(const SceneObject&) = delete;
		SceneObject& operator=(SceneObject&&) = delete;

		
	};
}
