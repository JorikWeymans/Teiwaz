#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class MaitaState;
	class MaitaComp final : public BaseComponent
	{
	public:
		explicit MaitaComp(float moveSpeed = 150.f, float playerDetectionRange = 300.f);
		~MaitaComp();

		void Initialize() override;
		  
		void Update() override;
		void FixedUpdate() override;
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif

	private:
		MaitaState* m_pState;

		float m_RayLength;
		float m_MoveSpeed;
		float m_PlayerDetectionRange;
	public:
		MaitaComp(const MaitaComp&) = delete;
		MaitaComp(MaitaComp&&) = delete;
		MaitaComp& operator=(const MaitaComp&) = delete;
		MaitaComp& operator=(MaitaComp&&) = delete;
	};
}

