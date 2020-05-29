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
		Player1Controller();
		~Player1Controller() = default;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};
		
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;
		void RenderEditor() override;
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
