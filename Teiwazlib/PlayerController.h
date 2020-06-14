#pragma once
#include "BaseComponent.h"
#include "Vectors.h"
#include <functional>

namespace tyr
{
	class CharacterControllerComp;
	class RigidBodyComp;
	class AnimatorComp;
	
	class PlayerController final : public BaseComponent
	{
	public:
		explicit PlayerController(float m_JumpForce = 500.f, int playerID = 1);
		~PlayerController() = default;

		void Initialize() override;
		void PostInitialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};

		_NODISCARD int GetPlayerID() const noexcept { return m_PlayerID; }
		_NODISCARD bool IsGoingLeft() const noexcept { return m_IsGoningLeft; }
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;
	protected:
		void InternalRenderEditor() override;
#endif
	private:
		CharacterControllerComp* m_pCont;
		RigidBodyComp* m_pBody;
		AnimatorComp* m_pAni;
		bool m_IsGoningLeft;
		float m_JumpForce;

		Vector2 m_StartPos{};

		int m_PlayerID;
		void OnHealthChanged(int amountLeft);
		std::function<void(int)> m_OnHealthChangedFunction; //save it so we can delete it if needed

		void MoveLeft();
		void MoveRight();
	public:
		PlayerController(const PlayerController&) = delete;
		PlayerController(PlayerController&&) = delete;
		PlayerController& operator=(const PlayerController&) = delete;
		PlayerController& operator=(PlayerController&&) = delete;
	};


}
