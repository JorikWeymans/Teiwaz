#pragma once
#include "BaseComponent.h"
#include "Elapser.h"
namespace tyr
{
	class AutoDestroyComp final : public BaseComponent
	{
	public:
		explicit AutoDestroyComp(float lifeTime);
		~AutoDestroyComp() = default;

		void Update() override;
		void FixedUpdate() override {}
		void Initialize() override {}

		void Render() const override {}
#ifdef EDITOR_MODE
		void Save(BinaryWriter& writer) override;
		void InternalRenderEditor() override;
#endif
	private:
		Elapser m_DestroyElapser;

	public:
		AutoDestroyComp(const AutoDestroyComp&) = delete;
		AutoDestroyComp(AutoDestroyComp&&) = delete;
		AutoDestroyComp& operator=(const AutoDestroyComp&) = delete;
		AutoDestroyComp& operator=(AutoDestroyComp&&) = delete;
	};


}
