#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class RigidBodyComp;
	class BubbleComp : public BaseComponent
	{
	public:
		BubbleComp();
		~BubbleComp() override = default;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};

#ifdef EDITOR_MODE
		void Debug() override {};
		void RenderEditor() override;
		void Save(BinaryWriter & writer) override;
#endif

	private:
		RigidBodyComp* m_pBody;
	public:
		BubbleComp(const BubbleComp&) = delete;
		BubbleComp(BubbleComp&&) = delete;
		BubbleComp& operator=(const BubbleComp&) = delete;
		BubbleComp& operator=(BubbleComp&&) = delete;
	};
}

