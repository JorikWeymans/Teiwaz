#pragma once
#include "Elapser.h"

namespace tyr
{
	struct RaycastHit;
	class GameContext;
	class SceneObject;
	class CharacterControllerComp;
	class RigidBodyComp;

// *----------------*
// *----- BASE -----*
// *----------------*
	class ZenChanState
	{
	public:
		explicit ZenChanState(GameContext const* pContext, SceneObject* pSceneObject);
		virtual ~ZenChanState() = default;

		virtual void Enter() {}
		virtual void Exit() {}
		
		_NODISCARD virtual ZenChanState* Update() = 0;
		_NODISCARD virtual ZenChanState* FixedUpdate() { return nullptr; }


#ifdef EDITOR_MODE
		virtual void Debug() {}
#endif


	protected:
		GameContext const* m_pContext;
		SceneObject* m_pSceneObject;

	public:
		ZenChanState(const ZenChanState&) = delete;
		ZenChanState(ZenChanState&&) = delete;
		ZenChanState& operator=(const ZenChanState&) = delete;
		ZenChanState& operator=(ZenChanState&&) = delete;
	};

// *----------------*
// *-- WANDERING ---*
// *----------------*
	class ZenChanWanderingState final : public ZenChanState
	{
	public:
		explicit ZenChanWanderingState(GameContext const* pContext, SceneObject* pSceneObject, float& moveSpeed, float& rayLength);
		virtual ~ZenChanWanderingState() = default;

		_NODISCARD ZenChanState* Update() override;
		_NODISCARD ZenChanState* FixedUpdate() override;

		void Enter() override;
		
#ifdef EDITOR_MODE
		void Debug() override;
#endif
	private:
		
		float& m_MoveSpeed;
		float& m_RayLength;
		CharacterControllerComp* m_pCont;
		RigidBodyComp* m_pBody;

		Elapser m_JumpCounter;
		Elapser m_NoDiSwitchTimer;
		bool m_CanSwitchDirection;
		bool m_IsGoingLeft;

		void OnColliderHit(RaycastHit hit);

	public:
		ZenChanWanderingState(const ZenChanWanderingState&) = delete;
		ZenChanWanderingState(ZenChanWanderingState&&) = delete;
		ZenChanWanderingState& operator=(const ZenChanWanderingState&) = delete;
		ZenChanWanderingState& operator=(ZenChanWanderingState&&) = delete;

	};
	class ZenChanBrainDeadState final : public ZenChanState
	{
	public:
		explicit ZenChanBrainDeadState(GameContext const* pContext, SceneObject* pSceneObject);
		virtual ~ZenChanBrainDeadState() = default;

		_NODISCARD ZenChanState* Update() override;
	};
}



