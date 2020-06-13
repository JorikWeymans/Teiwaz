#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class MaitaComp final : public BaseComponent
	{
	public:
		MaitaComp();
		~MaitaComp();

		void Initialize() override;
		
		void Update() override;
		void FixedUpdate() override {}
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	public:
		MaitaComp(const MaitaComp&) = delete;
		MaitaComp(MaitaComp&&) = delete;
		MaitaComp& operator=(const MaitaComp&) = delete;
		MaitaComp& operator=(MaitaComp&&) = delete;
	};
}

