#pragma once
#include "Elapser.h"
#include <vector>
#include "Vectors.h"
#include <map>

namespace tyr
{
	typedef std::map<unsigned int, Rect> SpritePositions;
	
	class Animation final
	{
	public:
		explicit Animation(float tpf, SpritePositions&& sp);
		~Animation() = default;
		void Update(float elapsed);
		const Rect& GetCurrentAnimation() const;
		void Reset();
	private:

		Elapser m_AniElapser;
		unsigned int m_CurrentAnimation;
		SpritePositions m_AniSprites;
		
	public:
		Animation(const Animation&) = delete;
		Animation(Animation&&) = delete;
		Animation& operator=(const Animation&) = delete;
		Animation& operator=(Animation&&) = delete;



	};


}
