#pragma once
#include "Elapser.h"
#include <vector>
#include "Vectors.h"

namespace tyr
{
	class Animation final
	{
	public:
		Animation();
		~Animation() = default;
		void Update(float elapsed);
		const Rectangle& GetCurrentAnimation() const;
		
	private:

		Elapser m_AniElapser;
		unsigned int m_CurrentAnimation;
		std::vector<Rectangle> m_AniSprites;
		
	public:
		Animation(const Animation&) = delete;
		Animation(Animation&&) = delete;
		Animation& operator=(const Animation&) = delete;
		Animation& operator=(Animation&&) = delete;



	};


}
