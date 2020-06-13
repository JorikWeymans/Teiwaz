#pragma once
#include "BaseComponent.h"
#include "GameContext.h"
#include <functional>

namespace tyr
{
	struct RaycastHit;
	enum class PivotMode;
	class Vector2;
	class ColliderComp final : public BaseComponent
	{
	public:
		explicit ColliderComp(float width, float height, const PivotMode& pivotMode, bool isDynamic = false);
		~ColliderComp() override;

		void Initialize() override;

		void Update() override {}
		void FixedUpdate() override {};
		void Render() const override {};

		Rect GetColliderRect() const;
		_NODISCARD bool IsDynamic() const noexcept { return m_IsDynamic; }

		std::function<void(RaycastHit)> onColliderHitFunction;
		void OnColliderHit(RaycastHit hit);
		
#ifdef EDITOR_MODE
		void Debug() override;
		void Save(BinaryWriter& writer) override;

		
		
	protected:
		void InternalRenderEditor() override;
#endif

	private:
		float m_Width, m_Height;
		PivotMode m_Pivot;
		bool m_IsDynamic;

		void RenderIsDynamicProperty();
		
	public:
		//ColliderComp() = delete;
		ColliderComp(const ColliderComp&) = delete;
		ColliderComp(ColliderComp&&) = delete;
		ColliderComp& operator=(const ColliderComp&) = delete;
		ColliderComp& operator=(ColliderComp&&) = delete;

	};
}
