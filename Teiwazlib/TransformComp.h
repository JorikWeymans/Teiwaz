#pragma once
#include "BaseComponent.h"
#include "Vectors.h"
#include "Transform.h"
namespace tyr
{
	class TransformComp final : public BaseComponent
	{
	public:
		explicit TransformComp(const Transform& transform);
		explicit TransformComp(const Vector2& position);
		explicit TransformComp(const Vector2& position, const Vector2& scale, float rotation);
		~TransformComp() override;

		void Translate(float x, float y);
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetPositionY(float y);
		
#ifdef USE_IM_GUI
		void RenderEditor() override;
#endif
		const Transform& GetTransform() const;
		Vector2 GetPosition() const;
		Vector2 GetScale() const;
		float GetRotation() const;

		Transform* GetTr();
	private:
		Transform* m_pTransform;

	public:
		TransformComp() = delete;
		TransformComp(const TransformComp&) = delete;
		TransformComp(TransformComp&&) = delete;
		TransformComp& operator=(const TransformComp&) = delete;
		TransformComp& operator=(TransformComp&& ) = delete;
		
	};


}
