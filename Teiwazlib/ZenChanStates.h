#pragma once
#include "Elapser.h"
#include <functional>

namespace tyr
{
	struct RaycastHit;
	class GameContext;
	class SceneObject;
	class CharacterControllerComp;
	class RigidBodyComp;
	class AnimatorComp;
	
// *----------------*
// *----- BASE -----*
// *----------------*
#pragma region Base

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
#pragma endregion
	
// *----------------*
// *---- EMPTY -----*
// *----------------*
#pragma region Empty

	class ZenChanEmptyState final : public ZenChanState
	{
	public:
		explicit ZenChanEmptyState();
		virtual ~ZenChanEmptyState() = default;
		

		_NODISCARD ZenChanState* Update() override { return nullptr; }
		
		ZenChanEmptyState(const ZenChanEmptyState&) = delete;
		ZenChanEmptyState(ZenChanEmptyState&&) = delete;
		ZenChanEmptyState& operator=(const ZenChanEmptyState&) = delete;
		ZenChanEmptyState& operator=(ZenChanEmptyState&&) = delete;
	};
#pragma endregion
	
// *----------------*
// *-- WANDERING ---*
// *----------------*
#pragma region Wandering

	class ZenChanWanderingState final : public ZenChanState
	{
	public:
		explicit ZenChanWanderingState(GameContext const* pContext, SceneObject* pSceneObject, float& moveSpeed, float& rayLength);
		virtual ~ZenChanWanderingState() = default;

		_NODISCARD ZenChanState* Update() override;
		_NODISCARD ZenChanState* FixedUpdate() override;

		void Enter() override;
		void Exit() override;
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
		bool m_HasBeenHit;
		
		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
	public:
		ZenChanWanderingState(const ZenChanWanderingState&) = delete;
		ZenChanWanderingState(ZenChanWanderingState&&) = delete;
		ZenChanWanderingState& operator=(const ZenChanWanderingState&) = delete;
		ZenChanWanderingState& operator=(ZenChanWanderingState&&) = delete;

	};
#pragma endregion
	
// *----------------*
// *--- IN BUBBLE---*
// *----------------*
#pragma region InBubble

	class ZenChanInBubbleState final : public ZenChanState
	{
	public:
		explicit ZenChanInBubbleState(GameContext const* pContext, SceneObject* pSceneObject, RigidBodyComp* pBody);
		virtual ~ZenChanInBubbleState() = default;

		void Enter() override;
		void Exit() override;
		
		_NODISCARD ZenChanState* Update() override;
		_NODISCARD ZenChanState* FixedUpdate() override;
	private:
		RigidBodyComp* m_pBody;
		bool m_HasBeenHit;
		
		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
		
	public:
		ZenChanInBubbleState(const ZenChanInBubbleState&) = delete;
		ZenChanInBubbleState(ZenChanInBubbleState&&) = delete;
		ZenChanInBubbleState& operator=(const ZenChanInBubbleState&) = delete;
		ZenChanInBubbleState& operator=(ZenChanInBubbleState&&) = delete;
	};
#pragma endregion

// *----------------*
// *---- POPPED ----*
// *----------------*
#pragma region Popped

	class ZenChanPoppedState final : public ZenChanState
	{
	public:
		explicit ZenChanPoppedState(GameContext const* pContext, SceneObject* pSceneObject);
		virtual ~ZenChanPoppedState() = default;

		void Enter() override;
		void Exit() override;

		_NODISCARD ZenChanState* Update() override;
	private:
		AnimatorComp* m_pAni;
		
		ZenChanPoppedState(const ZenChanPoppedState&) = delete;
		ZenChanPoppedState(ZenChanPoppedState&&) = delete;
		ZenChanPoppedState& operator=(const ZenChanPoppedState&) = delete;
		ZenChanPoppedState& operator=(ZenChanPoppedState&&) = delete;
	};
#pragma endregion
}



