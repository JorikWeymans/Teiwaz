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

	class MaitaState
	{
	public:
		explicit MaitaState(GameContext const* pContext, SceneObject* pSceneObject);
		virtual ~MaitaState() = default;

		virtual void Enter() {}
		virtual void Exit() {}

		_NODISCARD virtual MaitaState* Update() = 0;
		_NODISCARD virtual MaitaState* FixedUpdate() { return nullptr; }


#ifdef EDITOR_MODE
		virtual void Debug() {}
#endif


	protected:
		GameContext const* m_pContext;
		SceneObject* m_pSceneObject;

	public:
		MaitaState(const MaitaState&) = delete;
		MaitaState(MaitaState&&) = delete;
		MaitaState& operator=(const MaitaState&) = delete;
		MaitaState& operator=(MaitaState&&) = delete;
	};
#pragma endregion

	// *----------------*
	// *---- EMPTY -----*
	// *----------------*
#pragma region Empty

	class MaitaEmptyState final : public MaitaState
	{
	public:
		explicit MaitaEmptyState();
		virtual ~MaitaEmptyState() = default;


		_NODISCARD MaitaState* Update() override { return nullptr; }

		MaitaEmptyState(const MaitaEmptyState&) = delete;
		MaitaEmptyState(MaitaEmptyState&&) = delete;
		MaitaEmptyState& operator=(const MaitaEmptyState&) = delete;
		MaitaEmptyState& operator=(MaitaEmptyState&&) = delete;
	};
#pragma endregion

	// *----------------*
	// *-- WANDERING ---*
	// *----------------*
#pragma region Wandering

	class MaitaWanderingState final : public MaitaState
	{
	public:
		explicit MaitaWanderingState(GameContext const* pContext, SceneObject* pSceneObject, float& moveSpeed, float& rayLength, float& playerDetectionRange);
		virtual ~MaitaWanderingState() = default;

		_NODISCARD MaitaState* Update() override;
		_NODISCARD MaitaState* FixedUpdate() override;

		void Enter() override;
		void Exit() override;
#ifdef EDITOR_MODE
		void Debug() override;
#endif
	private:

		float& m_MoveSpeed;
		float& m_RayLength;
		float& m_PlayerDetectionRange;
		
		CharacterControllerComp* m_pCont;
		RigidBodyComp* m_pBody;

		Elapser m_JumpCounter;
		Elapser m_NoDiSwitchTimer;
		bool m_CanSwitchDirection;
		bool m_IsGoingLeft;
		bool m_HasBeenHit;

		Elapser m_ThrowRockElapser;
		bool m_CanThrowRock;
		void UpdateWallHit();
		void UpdateThrowRock();
		
		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
	public:
		MaitaWanderingState(const MaitaWanderingState&) = delete;
		MaitaWanderingState(MaitaWanderingState&&) = delete;
		MaitaWanderingState& operator=(const MaitaWanderingState&) = delete;
		MaitaWanderingState& operator=(MaitaWanderingState&&) = delete;

	};
#pragma endregion

	// *----------------*
	// *--- IN BUBBLE---*
	// *----------------*
#pragma region InBubble

	class MaitaInBubbleState final : public MaitaState
	{
	public:
		explicit MaitaInBubbleState(GameContext const* pContext, SceneObject* pSceneObject, RigidBodyComp* pBody);
		virtual ~MaitaInBubbleState() = default;

		void Enter() override;
		void Exit() override;

		_NODISCARD MaitaState* Update() override;
		_NODISCARD MaitaState* FixedUpdate() override;
	private:
		RigidBodyComp* m_pBody;
		bool m_HasBeenHit;

		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;

	public:
		MaitaInBubbleState(const MaitaInBubbleState&) = delete;
		MaitaInBubbleState(MaitaInBubbleState&&) = delete;
		MaitaInBubbleState& operator=(const MaitaInBubbleState&) = delete;
		MaitaInBubbleState& operator=(MaitaInBubbleState&&) = delete;
	};
#pragma endregion

	// *----------------*
	// *---- POPPED ----*
	// *----------------*
#pragma region Popped

	class MaitaPoppedState final : public MaitaState
	{
	public:
		explicit MaitaPoppedState(GameContext const* pContext, SceneObject* pSceneObject);
		virtual ~MaitaPoppedState() = default;

		void Enter() override;
		void Exit() override;

		_NODISCARD MaitaState* Update() override;
	private:
		AnimatorComp* m_pAni;

		MaitaPoppedState(const MaitaPoppedState&) = delete;
		MaitaPoppedState(MaitaPoppedState&&) = delete;
		MaitaPoppedState& operator=(const MaitaPoppedState&) = delete;
		MaitaPoppedState& operator=(MaitaPoppedState&&) = delete;
	};
#pragma endregion
}



