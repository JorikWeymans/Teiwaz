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
		
	public:
		Physics(const Physics&) = delete;
		Physics(Physics&&) = delete;
		Physics& operator=(const Physics&) = delete;
		Physics& operator=(Physics&&) = delete;
	};

}
