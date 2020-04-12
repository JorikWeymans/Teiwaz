#pragma once
#include "Vectors.h"
namespace tyr
{
	struct Transform_POD
	{
		Vector2_POD position;
		Vector2_POD scale;
		float rotation;

	};
	
	struct Transform
	{
		explicit Transform(const Vector2& pos, const Vector2& scale = Vector2{ 1.f,1.f }, float rot = 0.f);
		explicit Transform(const Transform_POD& pod);

		Transform_POD ToPOD() const;
		
		Vector2 position;
		Vector2 scale;
		float   rotation;
	};


}
