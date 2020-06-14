#pragma once
#include "BaseComponent.h"
#include "Elapser.h"

namespace tyr
{
	class AnimatorComp;
	class BubbleShootingComp final : public BaseComponent
	{
	public:
		BubbleShootingComp();
		~BubbleShootingComp() override = default;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {};

#ifdef EDITOR_MODE
		void Debug() override {};
		void Save(BinaryWriter& writer) override;
	protected:
		void InternalRenderEditor() override;
#endif

	private:
		Elapser m_ShootCDElapser;
		bool m_CanShoot;
		int m_PlayerID;
		bool m_IsShooting;
		SceneObject* CreateBubble() const;
		AnimatorComp* m_pAni;
	public:
		BubbleShootingComp(const BubbleShootingComp&) = delete;
		BubbleShootingComp(BubbleShootingComp&&) = delete;
		BubbleShootingComp& operator=(const BubbleShootingComp&) = delete;
		BubbleShootingComp& operator=(BubbleShootingComp&&) = delete;

	};
}
