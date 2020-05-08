#pragma once
#include <vector>
#include "../Animation.h"
#ifdef USE_IM_GUI
#define ANIMATION_NAME_MAX_CHAR 25
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
		TextureID m_TempTextureID;
		Animation* m_pAnimation;
		
		int m_i = 0, m_j = 0;
		int m_y = 1, m_z = 1;
		float m_GridSize = 48.f;
		Animation* m_pTemp;
		char m_Name[ANIMATION_NAME_MAX_CHAR];
		
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