#pragma once
#include "BaseComponent.h"
#include "Elapser.h"
#include "Vectors.h"

namespace tyr
{
	struct RaycastHit;
	class CharacterControllerComp;
	class RigidBodyComp;
	class ZenChanComp : public BaseComponent
	{
	public:
		explicit ZenChanComp(float moveSpeed = 150.f);
		~ZenChanComp();

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {}

		void OnColliderHit(RaycastHit hit);
#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		CharacterControllerComp* m_pCont;
		RigidBodyComp* m_pBody;
		Elapser m_JumpCounter;
		Elapser m_NoDiSwitchTimer;
		bool m_CanSwitchDirection;
		bool m_IsGoingLeft;
		float m_RayLength;
		float m_MoveSpeed;
	public:
		ZenChanComp(const ZenChanComp&) = delete;
		ZenChanComp(ZenChanComp&&) = delete;
		ZenChanComp& operator=(const ZenChanComp&) = delete;
		ZenChanComp& operator=(ZenChanComp&&) = delete;
	};
}
