#pragma once
namespace tyr
{
	class Vector2
	{
	public:
		explicit Vector2(float x, float y);
		float x, y;
		
	};

	class Vector3
	{
	public:
		explicit Vector3(float x, float y, float z);
		explicit Vector3(const Vector2& vec);
		float x, y, z;
	};



	
	


















	
}