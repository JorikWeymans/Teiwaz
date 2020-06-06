#pragma once
#include "Scene.h"
#include "Vectors.h"

namespace tyr
{
	class TextureComp;
	class CharacterControllerComp;
	class Animator;
}
namespace bub
{
	class BubPrefab;
	class MainScene final : public tyr::Scene
	{
	public:
		MainScene();
		~MainScene();
		void Load() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() const override;
#ifdef EDITOR_MODE
		void Debug() override;
#endif
	private:
		void LoadBackground();
		
		tyr::Animator* m_Ani = nullptr;
	public:
		MainScene(const MainScene&) = delete;
		MainScene(MainScene&&) = delete;
		MainScene& operator=(const MainScene&) = delete;
		MainScene& operator=(MainScene&&) = delete;


		
	};
}


