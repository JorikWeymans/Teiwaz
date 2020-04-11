#pragma once
#include "BaseComponent.h"

namespace tyr
{
	class CharacterControllerComp;
	class RigidBodyComp final : public BaseComponent
	{
	public:
		RigidBodyComp(float gravity);
		~RigidBodyComp() override = default;

		void Initialize() override;

		void Update() override {};
		void FixedUpdate() override;
		void Render() const override {};

#ifdef USE_IM_GUI
		void Debug() override;
		void RenderEditor() override;

#endif

	private:
		CharacterControllerComp* m_pController; // weak pointer;
		float m_Gravity;
	public:
		//RigidBodyComp() = delete;
		RigidBodyComp(const RigidBodyComp&) = delete;
		RigidBodyComp(RigidBodyComp&&) = delete;
		RigidBodyComp& operator=(const RigidBodyComp&) = delete;
		RigidBodyComp& operator=(RigidBodyComp&&) = delete;

	};
}