#pragma once
#include "BaseComponent.h"
#include <functional>

namespace tyr
{
	struct RaycastHit;
	class RigidBodyComp;
	class BubbleComp : public BaseComponent
	{
	public:
		explicit BubbleComp(bool goLeft);
		~BubbleComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};

#ifdef EDITOR_MODE
		void Debug() override {};
		void Save(BinaryWriter & writer) override;
	protected:
		void InternalRenderEditor() override;
#endif

	private:
		RigidBodyComp* m_pBody;
		bool m_IsGoingLeft;

		
		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
	public:
		BubbleComp(const BubbleComp&) = delete;
		BubbleComp(BubbleComp&&) = delete;
		BubbleComp& operator=(const BubbleComp&) = delete;
		BubbleComp& operator=(BubbleComp&&) = delete;
	};
}

