#pragma once
#include "BaseComponent.h"

namespace tyr
{
	enum class FPSCompType {Update, FixedUpdate};
	class TextComp;
	class FPSComp final : public BaseComponent
	{
	public:
		explicit FPSComp(const FPSCompType& type, unsigned int textIndex = 0);
		~FPSComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

	private:
		FPSCompType m_Type;
		TextComp* m_pTextComp;
		unsigned int m_TextIndex;
	public:
		FPSComp() = delete;
		FPSComp(const FPSComp&) = delete;
		FPSComp(FPSComp&&) = delete;
		FPSComp& operator=(const FPSComp&) = delete;
		FPSComp& operator=(FPSComp&&) = delete;

	};
}