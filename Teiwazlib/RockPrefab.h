#pragma once
namespace tyr
{
	class Scene;
	class Vector2;
	class RockPrefab
	{
	public:
		static void Generate(Scene* pScene, const Vector2& pos, bool isGoingLeft);
	public:
		RockPrefab() = delete;
		~RockPrefab() = delete;
		RockPrefab(const RockPrefab&) = delete;
		RockPrefab(RockPrefab&&) = delete;
		RockPrefab& operator=(const RockPrefab&) = delete;
		RockPrefab& operator=(RockPrefab&&) = delete;
	};


}
