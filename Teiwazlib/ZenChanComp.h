#pragma once
#include "BaseComponent.h"
namespace tyr
{
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

#ifdef EDITOR_MODE
		void Debug() override;
		void InternalRenderEditor() override;
		void Save(BinaryWriter& writer) override;
#endif
	private:
		CharacterControllerComp* m_pCont;
		bool m_IsGoingLeft;
		float m_RayLength;
	public:
		ZenChanComp(const ZenChanComp&) = delete;
		ZenChanComp(ZenChanComp&&) = delete;
		ZenChanComp& operator=(const ZenChanComp&) = delete;
		ZenChanComp& operator=(ZenChanComp&&) = delete;
	};
}
