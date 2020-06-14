#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class FoodComp final : public BaseComponent
	{
	public:
		FoodComp();
		~FoodComp();

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	public:
		FoodComp(const FoodComp&) = delete;
		FoodComp(FoodComp&&) = delete;
		FoodComp& operator=(const FoodComp&) = delete;
		FoodComp& operator=(FoodComp&&) = delete;
	};
}

