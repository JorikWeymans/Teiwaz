#include "tyrpch.h"
#include "Physics.h"
#include "Vectors.h"
#include "TeiwazEngine.h"
#include "Color.h"
#include "ColliderComp.h"
bool tyr::Physics::Raycast(const Vector2& pos, const Vector2& direction, float length, RaycastHit& hit, SceneObject* pCaller)
{
	// Vec1
	const auto A = pos;
	const auto B = A + (direction * length);
	
	for(auto pC : m_pColliders)
	{
		 auto tC = pC->GetColliderRect();
		 if(pC->GetSceneObject() == pCaller)
		 {
			 continue;
		 }
		
		 if (LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y },hit) || //Top
			LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y + tC.height }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit) || //Bot
			LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x, tC.pos.y + tC.height }, hit) || //Left
			LineInterSection(A, B, Vector2{ tC.pos.x + tC.width, tC.pos.y}, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit)) // Right
		{
			 hit.other = pC->GetSceneObject();
			return true;
		}
	}

	
	return false;

	
}

void tyr::Physics::AddCollider(ColliderComp* pCollider)
{

	const auto found = std::find(m_pColliders.begin(), m_pColliders.end(), pCollider);
	if (found == m_pColliders.end())
	{
		m_pColliders.emplace_back(pCollider);
	}
}

bool tyr::Physics::LineInterSection(const Vector2& pos1A, const Vector2& pos1B, const Vector2& pos2A, const Vector2& pos2B, RaycastHit& hit)
{
	auto ab = pos1B - pos1A;
	auto cd = pos2B - pos2A;

	auto rsCross = ab.Cross(cd);

	auto e = (pos2A - pos1A).Cross(cd) / rsCross;
	auto f = (pos2A - pos1A).Cross(ab) / rsCross;

	if (f >= 0 && f <= 1 && e >= 0 && e <= 1)
	{

		hit.point = pos1A + (ab * e);
		
		// a+ tr || c + us
		

		return true;
	}

	return false;
}
