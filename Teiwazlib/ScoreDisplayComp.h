#pragma once
#include "BaseComponent.h"
namespace tyr
{
	class TextComp;
	class ScoreDisplayComp final : public BaseComponent
	{
	public:
		explicit ScoreDisplayComp(int playerNumber = 1);
		~ScoreDisplayComp();

		void Initialize() override;

		void Update() override {}
		void FixedUpdate() override;
		void Render() const override {}

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		int m_PlayerNmbr;
		TextComp* m_pText;
	public:
		ScoreDisplayComp(const ScoreDisplayComp&) = delete;
		ScoreDisplayComp(ScoreDisplayComp&&) = delete;
		ScoreDisplayComp& operator=(const ScoreDisplayComp&) = delete;
		ScoreDisplayComp& operator=(ScoreDisplayComp&&) = delete;
	};
}

