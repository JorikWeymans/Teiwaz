#pragma once
#include "BaseComponent.h"
#include <functional>
namespace tyr
{
	struct RaycastHit;
	class FoodComp final : public BaseComponent
	{
	public:
		explicit FoodComp(FoodType type = FoodType::Melon);
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

	private:
		FoodType m_FoodType;

		void OnColliderHit(RaycastHit hit);
		std::function<void(RaycastHit)> m_OnColliderHitFunction;
	public:
		FoodComp(const FoodComp&) = delete;
		FoodComp(FoodComp&&) = delete;
		FoodComp& operator=(const FoodComp&) = delete;
		FoodComp& operator=(FoodComp&&) = delete;
	};
}

