#pragma once
#include "BaseComponent.h"
#include "GameContext.h"

namespace tyr
{
	enum class PivotMode;
	class Vector2;
	class ColliderComp final : public BaseComponent
	{
	public:
		explicit ColliderComp(float width, float height, const PivotMode& pivotMode);
		~ColliderComp() override = default;

		void Initialize() override {};

		void Update() override {}
		void FixedUpdate() override {};
		void Render() const override {};

		Rect GetColliderRect() const;
#ifdef USE_IM_GUI
		void Debug() override;
#endif
	private:
		float m_Width, m_Height;
		PivotMode m_Pivot;
	public:
		//ColliderComp() = delete;
		ColliderComp(const ColliderComp&) = delete;
		ColliderComp(ColliderComp&&) = delete;
		ColliderComp& operator=(const ColliderComp&) = delete;
		ColliderComp& operator=(ColliderComp&&) = delete;

	};
}
