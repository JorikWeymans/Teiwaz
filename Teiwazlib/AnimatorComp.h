#pragma once
#include "BaseComponent.h"
namespace tyr
{
	enum class PivotMode;
	class Animator;
	class Vector2;
	class TextureComp;
	class AnimatorComp final : public BaseComponent
	{
	public:
		explicit AnimatorComp();
		explicit AnimatorComp(AnimatorID id);
		~AnimatorComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override {};
		void Render() const override {};
		
		void SetFloat(const std::string& variable, float value);
		void SetBool(const std::string& variable, bool value);
		_NODISCARD bool IsAtEnd() const noexcept;
#ifdef EDITOR_MODE
		void Debug() override;
		void Save(BinaryWriter& writer) override;
	protected:
		void InternalRenderEditor() override;
#endif

	private:
		Animator* m_pAnimator;
		AnimatorID m_AnimatorID;
		TextureComp* m_pTextureComp;
		
	public:
		//AnimatorComp() = delete;
		AnimatorComp(const AnimatorComp&) = delete;
		AnimatorComp(AnimatorComp&&) = delete;
		AnimatorComp& operator=(const AnimatorComp&) = delete;
		AnimatorComp& operator=(AnimatorComp&&) = delete;

	};
}