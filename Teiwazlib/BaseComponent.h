#pragma once
#define GET_CONTEXT m_pSceneObject->GetGameContext()
#define GET_COMPONENT m_pSceneObject->GetComponent
#define GET_COMPONENT_IN_CHILD m_pSceneObject->GetComponentInChild
#define GET_TRANSFORM m_pSceneObject->GetTransform()
#define GET_OBJECT_WITH_NAME GET_CONTEXT->pSceneManager->GetCurrentScene()->GetFirstObjectWithName
#define RAYCAST(pos, direction, length, refHit) GET_CONTEXT->pPhysics->Raycast(pos, direction, length, refHit, m_pSceneObject)
#define INPUT GET_CONTEXT->pInput
#define TIME  GET_CONTEXT->pTime
#define ADD_COMPONENT m_pSceneObject->AddComponent
#define REMOVE_COMPONENT(CompType) m_pSceneObject->RemoveComponent(GET_COMPONENT<CompType>())

#include "BinStructureHelpers.h"
#include "BinaryReader.h"

namespace tyr
{
	class BinaryWriter;
	class SceneObject;
	class BaseComponent
	{
	public:
		BaseComponent(ComponentType type, const std::string& name, bool canBeRemoved = true);
		virtual ~BaseComponent() = default;

		virtual void Initialize() = 0;
		virtual void PostInitialize(){}
		virtual void Update() = 0;
		SceneObject* GetSceneObject() const { return m_pSceneObject; }
		
#ifdef EDITOR_MODE
		void RenderEditor();
		virtual void Debug() {}
		virtual void Save(BinaryWriter& writer) { UNREFERENCED_PARAMETER(writer); };
#endif
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		void Destroy();
		_NODISCARD bool IsDestroyed() const noexcept { return m_IsDestroyed; }
		
	protected:
		friend SceneObject;
		SceneObject* m_pSceneObject = nullptr;
		ComponentType m_Type;
		bool m_IsDestroyed;
#ifdef EDITOR_MODE
		uint32_t m_UniqueId; //if you don't use a unique id, every comp will change its value, auto generated for ease of use
		std::string m_ImGuiHeaderID;
		bool m_IsComponentOpen, m_CanBeRemoved;

		virtual void InternalRenderEditor() = 0;
#endif
	public:
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) = delete;
	};

}
