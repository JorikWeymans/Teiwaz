#pragma once
#define GET_CONTEXT m_pSceneObject->GetGameContext()
namespace tyr
{
	class SceneObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
#ifdef USE_IM_GUI
		virtual void Debug() {}
#endif
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

	protected:
		friend SceneObject;
		SceneObject* m_pSceneObject = nullptr;

	public:
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) = delete;
	};


}
