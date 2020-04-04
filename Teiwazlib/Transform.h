#pragma once
#include "Vectors.h"
namespace tyr
{
	struct transform
	{
		explicit transform(const Vector2& pos, const Vector2& scale = Vector2{1.f,1.f}, float rot = 0.f)
			: position(pos), scale(scale), rotation(rot) {}
		
		Vector2 position;
		Vector2 scale;
		float   rotation;
	};
}
