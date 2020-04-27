#pragma once
#define GET_CONTEXT m_pSceneObject->GetGameContext()
#define INPUT m_pSceneObject->GetGameContext()->pInput
#define GET_COMPONENT m_pSceneObject->GetComponent

#include "BinStructureHelpers.h"
#include "BinaryReader.h"

namespace tyr
{
	class BinaryWriter;
	class SceneObject;
	class BaseComponent
	{
	public:
		BaseComponent(ComponentType type);
		virtual ~BaseComponent() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		SceneObject* GetSceneObject() const { return m_pSceneObject; }
		
#ifdef USE_IM_GUI
		virtual void Debug() {}
		virtual void RenderEditor() {}; //should be overridden in 90% of the time, the window is opend in sceneobject before this call
		virtual void Save(BinaryWriter& writer) { UNREFERENCED_PARAMETER(writer); };
#endif
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

	protected:
		friend SceneObject;
		SceneObject* m_pSceneObject = nullptr;
		ComponentType m_Type;
#ifdef USE_IM_GUI
		size_t m_UniqueId;
#endif
	public:
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) = delete;
	};

}
