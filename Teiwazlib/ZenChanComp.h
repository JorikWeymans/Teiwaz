#pragma once
#include "BaseComponent.h"
#include "Elapser.h"
#include "Vectors.h"

namespace tyr
{
	struct RaycastHit;
	class CharacterControllerComp;
	class ZenChanComp : public BaseComponent
	{
	public:
		ZenChanComp();
		~ZenChanComp();

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override {}


		void OnColliderHit(RaycastHit hit);
#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		CharacterControllerComp* m_pCont;
		Elapser m_NoDiSwitchTimer;
		bool m_CanSwitchDirection;
		bool m_IsGoingLeft;
		float m_RayLength;
	public:
		ZenChanComp(const ZenChanComp&) = delete;
		ZenChanComp(ZenChanComp&&) = delete;
		ZenChanComp& operator=(const ZenChanComp&) = delete;
		ZenChanComp& operator=(ZenChanComp&&) = delete;
	};
}
