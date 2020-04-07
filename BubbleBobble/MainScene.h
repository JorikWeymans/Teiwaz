#pragma once
#include "Scene.h"
namespace tyr
{
	class TextureComp;
	class Animator;
}
namespace bub
{
	
	class MainScene final : public tyr::Scene
	{
	public:
		MainScene() = default;
		~MainScene();
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
#ifdef USE_IM_GUI
		void Debug() override;
#endif
	private:
		void LoadBackground();
		tyr::SceneObject* m_pPlayer = nullptr;
		tyr::TextureComp* m_pTexture = nullptr;
		tyr::Animator* m_Ani = nullptr;
		
	public:
		MainScene(const MainScene&) = delete;
		MainScene(MainScene&&) = delete;
		MainScene& operator=(const MainScene&) = delete;
		MainScene& operator=(MainScene&&) = delete;


		
	};
}


