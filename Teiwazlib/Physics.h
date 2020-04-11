#pragma once
#include <vector>

namespace tyr
{
	class GameContext;
	
	class ColliderComp;
	class Vector2;
	class Physics final
	{
	public:
		Physics() = default;
		bool Raycast(const Vector2& pos, const Vector2& direction, float length);
		void AddCollider(ColliderComp* pCollider);
	private:
		std::vector<ColliderComp*> m_pColliders;
		static bool LineInterSection(const Vector2& pos1A, const Vector2& pos1B, const Vector2& pos2A, const Vector2& pos2B);
	public:
		Physics(const Physics&) = delete;
		Physics(Physics&&) = delete;
		Physics& operator=(const Physics&) = delete;
		Physics& operator=(Physics&&) = delete;
	};

}
