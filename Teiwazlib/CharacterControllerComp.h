#pragma once
#include "Vectors.h"
#include "BaseComponent.h"

namespace tyr
{
	class ColliderComp;
	class TransformComp;
	class CharacterControllerComp final : public BaseComponent
	{
	public:
		CharacterControllerComp();
		~CharacterControllerComp() override = default;

		void Initialize() override;

		void Update() override {};
		void FixedUpdate() override;
		void Render() const override {};
		bool IsGrounded() const { return m_IsOnGround; }
		void Move(float x, float y);
		void AddForce(float x, float y);
		
#ifdef EDITOR_MODE
		void Debug() override;
		void RenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		TransformComp* m_pTransform;
		ColliderComp* m_pCollider; //weak pointer
		Vector2 m_Force;
		float m_RayCastOffset;
		float m_ForceMultiplier;
		bool m_IsOnGround;


		void DoGroundCheck();
	public:
		//CharacterControllerComp() = delete;
		CharacterControllerComp(const CharacterControllerComp&) = delete;
		CharacterControllerComp(CharacterControllerComp&&) = delete;
		CharacterControllerComp& operator=(const CharacterControllerComp&) = delete;
		CharacterControllerComp& operator=(CharacterControllerComp&&) = delete;

	};
}
