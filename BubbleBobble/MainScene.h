#pragma once
#include "Scene.h"
#include "Animation.h"
namespace tyr
{
	class TextureComp;
}
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
		tyr::TextureComp* m_pTexture;
		tyr::Animation m_Ani;
		
	public:
		MainScene(const MainScene&) = delete;
		MainScene(MainScene&&) = delete;
		MainScene& operator=(const MainScene&) = delete;
		MainScene& operator=(MainScene&&) = delete;


		
	};
}


