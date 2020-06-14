#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class RockComp final : public BaseComponent
	{
	public:
		explicit RockComp();
		~RockComp() = default;

		void Update() override;
		void FixedUpdate() override {}
		void Initialize() override {}

		void Render() const override {}
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;
		void InternalRenderEditor() override;
#endif
	private:


	public:
		RockComp(const RockComp&) = delete;
		RockComp(RockComp&&) = delete;
		RockComp& operator=(const RockComp&) = delete;
		RockComp& operator=(RockComp&&) = delete;
	};


}
