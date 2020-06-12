#pragma once
#include <vector>
#include "Vectors.h"
namespace tyr
{
	class SceneObject;
	struct RaycastHit
	{
		Vector2 point;
		SceneObject* other = nullptr;
	};

	class GameContext;
	
	class ColliderComp;

	class Physics final
	{
	public:
		Physics() = default;
		bool Raycast(const Vector2& pos, const Vector2& direction, float length, RaycastHit& hit, SceneObject* pCaller);
		void AddCollider(ColliderComp* pCollider); 
		void RemoveCollider(ColliderComp* pCollider);
	private:
		std::vector<ColliderComp*> m_pColliders;
		static bool LineInterSection(const Vector2& pos1A, const Vector2& pos1B, const Vector2& pos2A, const Vector2& pos2B, RaycastHit& hit);
	public:
		Physics(const Physics&) = delete;
		Physics(Physics&&) = delete;
		Physics& operator=(const Physics&) = delete;
		Physics& operator=(Physics&&) = delete;
	};

}
