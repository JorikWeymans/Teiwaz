#pragma once
#include "BaseComponent.h"

namespace tyr
{
	class ColliderComp;
	class TransformComp;
	class Vector2;
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
#ifdef USE_IM_GUI
		void Debug() override;
		void RenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		TransformComp* m_pTransform;
		ColliderComp* m_pCollider; //weak pointer
		float m_RayCastOffset;
		bool m_IsOnGround;
	public:
		//CharacterControllerComp() = delete;
		CharacterControllerComp(const CharacterControllerComp&) = delete;
		CharacterControllerComp(CharacterControllerComp&&) = delete;
		CharacterControllerComp& operator=(const CharacterControllerComp&) = delete;
		CharacterControllerComp& operator=(CharacterControllerComp&&) = delete;

	};
}
