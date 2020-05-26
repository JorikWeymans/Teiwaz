#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class BubbleShootingComp final : public BaseComponent
	{
	public:
		BubbleShootingComp();
		~BubbleShootingComp() override = default;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override {};
		void Render() const override {};

#ifdef EDITOR_MODE
		void Debug() override {};
		void RenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif

	private:
		SceneObject* CreateBubble() const;
	public:
		BubbleShootingComp(const BubbleShootingComp&) = delete;
		BubbleShootingComp(BubbleShootingComp&&) = delete;
		BubbleShootingComp& operator=(const BubbleShootingComp&) = delete;
		BubbleShootingComp& operator=(BubbleShootingComp&&) = delete;

	};
}
