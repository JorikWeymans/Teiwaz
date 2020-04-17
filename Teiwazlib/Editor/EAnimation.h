#pragma once
#include <vector>

namespace tyr
{
	class GameContext;
	class Texture;
	class Rect;
	class EAnimation final
	{
	public:
		explicit EAnimation(GameContext* pContext);
		~EAnimation() = default;

		void RenderEditor();
	private:
		GameContext* m_pContext;
		Texture* m_pTexture;

		std::vector<Rect> m_Rects;
		int m_i = 0, m_j = 0;
		int m_y = 1, m_z = 1;
		float m_GridSize = 48.f;
	public:
		EAnimation(const EAnimation&) = delete;
		EAnimation(EAnimation&&) = delete;
		EAnimation& operator=(const EAnimation&) = delete;
		EAnimation& operator=(EAnimation&&) = delete;

		
	};
}
