#pragma once
#include "BaseComponent.h"
#include "Vectors.h"

namespace tyr
{
	class CharacterControllerComp;
	class RigidBodyComp final : public BaseComponent
	{
	public:
		RigidBodyComp(float gravity, bool useGravity = true);
		~RigidBodyComp() override = default;

		void Initialize() override;

		void AddForce(float x, float y);
		void Update() override {}
		void FixedUpdate() override;
		void Render() const override {};

#ifdef EDITOR_MODE
		void Debug() override;
		void RenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		CharacterControllerComp* m_pController; // weak pointer;
		Vector2 m_Vel, m_Force;
		bool m_UseGravity;
		float m_Gravity;
		
	public:
		//RigidBodyComp() = delete;
		RigidBodyComp(const RigidBodyComp&) = delete;
		RigidBodyComp(RigidBodyComp&&) = delete;
		RigidBodyComp& operator=(const RigidBodyComp&) = delete;
		RigidBodyComp& operator=(RigidBodyComp&&) = delete;

	};
}
