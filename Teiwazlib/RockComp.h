#pragma once
#include "BaseComponent.h"
#include <functional>

namespace tyr
{
	struct RaycastHit;
	class RockComp final : public BaseComponent
	{
	public:
		explicit RockComp();
		~RockComp();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override {}

		void Render() const override {}
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;
		void InternalRenderEditor() override;
#endif
	private:

		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
	public:
		RockComp(const RockComp&) = delete;
		RockComp(RockComp&&) = delete;
		RockComp& operator=(const RockComp&) = delete;
		RockComp& operator=(RockComp&&) = delete;
	};


}
