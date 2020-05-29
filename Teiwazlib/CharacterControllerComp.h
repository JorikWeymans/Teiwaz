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
		bool IsGrounded() const noexcept  { return m_IsOnGround; }

		void Move(const Vector2& vec) noexcept;
		void Move(float x, float y) noexcept;
		
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

		bool m_IsOnGround;


		void DoGroundCheck() noexcept;

		bool CalculateFalling(float y, const Rect& playerColl, const Rect* pPlaySpace) noexcept; //return true when you want to move
		
	public:
		//CharacterControllerComp() = delete;
		CharacterControllerComp(const CharacterControllerComp&) = delete;
		CharacterControllerComp(CharacterControllerComp&&) = delete;
		CharacterControllerComp& operator=(const CharacterControllerComp&) = delete;
		CharacterControllerComp& operator=(CharacterControllerComp&&) = delete;

	};
}
