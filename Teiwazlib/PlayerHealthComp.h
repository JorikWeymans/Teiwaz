#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class PlayerHealthComp : public BaseComponent
	{
	public:
		explicit PlayerHealthComp();
		~PlayerHealthComp() override = default;

		
		void Initialize() override;
		void Update() override {}
		void FixedUpdate() override {}
		void Render() const override {}

		_NODISCARD UINT GetAmount() const noexcept { return m_NmbrLives; }
		void RemoveHealth();
		
#ifdef EDITOR_MODE
		void Debug() override {};
		void Save(BinaryWriter& writer) override;
	protected:
		void InternalRenderEditor() override;
#endif
	private:
		UINT m_NmbrLives;
	public:
		PlayerHealthComp(const PlayerHealthComp&) = delete;
		PlayerHealthComp(PlayerHealthComp&&) = delete;
		PlayerHealthComp& operator=(const PlayerHealthComp&) = delete;
		PlayerHealthComp& operator=(PlayerHealthComp&&) = delete;

	};
}


