#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class CharacterControllerComp;
	class RigidBodyComp;
	class AnimatorComp;
	
	class Player1Controller final : public BaseComponent
	{
	public:
		explicit Player1Controller(float m_JumpForce = 500.f);
		~Player1Controller() = default;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};
		
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
	public:
		Player1Controller(const Player1Controller&) = delete;
		Player1Controller(Player1Controller&&) = delete;
		Player1Controller& operator=(const Player1Controller&) = delete;
		Player1Controller& operator=(Player1Controller&&) = delete;
	};


}
