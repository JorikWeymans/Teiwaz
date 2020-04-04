#pragma once
#include "Scene.h"
namespace bub
{
	class MiniginScene final : public tyr::Scene
	{
	public:
		~MiniginScene() override;
		void Initialize() override;

	protected:
		void Render() const override;

	private:
		SDXL::SDXLFont* m_pFont = nullptr;
	};


}
