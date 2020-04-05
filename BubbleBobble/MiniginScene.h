#pragma once
#include "Scene.h"
namespace bub
{
	class MiniginScene final : public tyr::Scene
	{
	public:
		MiniginScene() = default;
		~MiniginScene() override;
		void Initialize() override;

	protected:
		void Render() const override;

	public:
		MiniginScene(const MiniginScene&) = delete;
		MiniginScene(MiniginScene&&) = delete;
		MiniginScene& operator=(const MiniginScene&) = delete;
		MiniginScene& operator=(MiniginScene&&) = delete;

	};


}
