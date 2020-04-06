#pragma once
#include "BaseComponent.h"
#include "Vectors.h"
#include "Transform.h"
namespace tyr
{
	class TransformComp final : public BaseComponent
	{
	public:
		explicit TransformComp(const transform& transform);
		explicit TransformComp(const Vector2& position);
		explicit TransformComp(const Vector2& position, const Vector2& scale, float rotation);
		~TransformComp() override = default;

		void Translate(float x, float y);
		
		void Initialize() override {};
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		const transform& GetTransform() const;
		const Vector2& GetPosition() const;
		const Vector2& GetScale() const;
		float GetRotation() const;

		
	private:
		transform m_Transform;

	public:
		TransformComp() = delete;
		TransformComp(const TransformComp&) = delete;
		TransformComp(TransformComp&&) = delete;
		TransformComp& operator=(const TransformComp&) = delete;
		TransformComp& operator=(TransformComp&& ) = delete;
		
	};


}
