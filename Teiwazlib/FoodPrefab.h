#pragma once
namespace tyr
{
	class Scene;
	class Vector2;
	class FoodPrefab final
	{
	public:
		static void Generate(Scene* pScene, const Vector2& pos, FoodType type);
		
	public:
		FoodPrefab() = delete;
		~FoodPrefab() = delete;
		FoodPrefab(const FoodPrefab&) = delete;
		FoodPrefab(FoodPrefab&&) = delete;
		FoodPrefab& operator=(const FoodPrefab&) = delete;
		FoodPrefab& operator=(FoodPrefab&&) = delete;
	};


}
