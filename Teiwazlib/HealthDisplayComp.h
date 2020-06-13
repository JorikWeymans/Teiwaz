#pragma once
#include "BaseComponent.h"
#include <functional>

namespace tyr
{
	class TextureComp;
	
	class HealthDisplayComp final : public BaseComponent
	{
	public:
		explicit HealthDisplayComp();
		~HealthDisplayComp() override = default;


		void Initialize() override;
		void Update() override {}
		void FixedUpdate() override {}
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override {};
		void Save(BinaryWriter& writer) override;
	protected:
		void InternalRenderEditor() override;
		
#endif
	private:
		TextureComp* m_pTexture;
		
		void OnHealthChanged(int amountLeft);
		std::function<void(int)> m_OnHealthChangedFunction;
	public:
		HealthDisplayComp(const HealthDisplayComp&) = delete;
		HealthDisplayComp(HealthDisplayComp&&) = delete;
		HealthDisplayComp& operator=(const HealthDisplayComp&) = delete;
		HealthDisplayComp& operator=(HealthDisplayComp&&) = delete;

	};
}


