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
		void Scale(float x, float y);
		void SetScale(float x, float y);
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetPositionX(float x, bool convert = false);
		void SetPositionY(float y, bool convert = false);

		static TransformComp* CreateComponent(BinaryReader& reader);

		const Transform& GetTransform() const;
		Vector2 GetPosition() const;
		Vector2 GetPositionRaw() const;
		Vector2 GetScale() const;
		float GetRotation() const;

		Transform* GetTr();
		
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;

	protected:
		void InternalRenderEditor() override;
#endif

		
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
