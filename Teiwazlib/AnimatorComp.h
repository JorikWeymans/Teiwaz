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
		~AnimatorComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override {};
		void Render() const override {};
		
		void SetFloat(const std::string& variable, float amount);
#ifdef USE_IM_GUI
		void Debug() override;
		void RenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif

	private:
		Animator* m_pAnimator;
		TextureComp* m_pTextureComp;
	public:
		//AnimatorComp() = delete;
		AnimatorComp(const AnimatorComp&) = delete;
		AnimatorComp(AnimatorComp&&) = delete;
		AnimatorComp& operator=(const AnimatorComp&) = delete;
		AnimatorComp& operator=(AnimatorComp&&) = delete;

	};
}