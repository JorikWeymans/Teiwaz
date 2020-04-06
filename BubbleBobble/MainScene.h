#pragma once
#include "Scene.h"
namespace bub
{
	class MainScene final : public tyr::Scene
	{
	public:
		MainScene() = default;
		~MainScene() = default;
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
	private:
		void LoadBackground();
		tyr::SceneObject* m_pPlayer;
	public:
		MainScene(const MainScene&) = delete;
		MainScene(MainScene&&) = delete;
		MainScene& operator=(const MainScene&) = delete;
		MainScene& operator=(MainScene&&) = delete;


		
	};
}


