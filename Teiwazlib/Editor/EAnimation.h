#pragma once
#include <vector>
#include "../Animation.h"
#ifdef USE_IM_GUI
namespace tyr
{
	class Animation;
	class GameContext;
	class Rect;
	class EAnimation final
	{
	public:
		explicit EAnimation(GameContext* pContext);
		~EAnimation();

		void SetCurrentAnimation(Animation* pAnimation);
		void RenderEditor();
	private:
		void Menu();
		void SpriteWindow();
		void AnimationEditor();
		
		GameContext* m_pContext;
		TextureID m_Texture;
		Animation* m_pAnimation;
		
		int m_i = 0, m_j = 0;
		int m_y = 1, m_z = 1;
		float m_GridSize = 48.f;
		Animation* m_pTemp;
		
		bool m_ShowAnimation;
		bool m_WindowIsOpen;
		
	public:
		EAnimation(const EAnimation&) = delete;
		EAnimation(EAnimation&&) = delete;
		EAnimation& operator=(const EAnimation&) = delete;
		EAnimation& operator=(EAnimation&&) = delete;

		
	};
}
#endif