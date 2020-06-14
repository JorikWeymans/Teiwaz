#include "tyrpch.h"
#include "Physics.h"
#include "Vectors.h"
#include "TeiwazEngine.h"
#include "Color.h"
#include "ColliderComp.h"
#include "SceneObject.h"
bool tyr::Physics::Raycast(const Vector2& pos, const Vector2& direction, float length, RaycastHit& hit, SceneObject* pCaller, bool ignoreDynamic)
{
	// Vec1
	const auto A = pos;
	const auto B = A + (direction * length);
	if(!ignoreDynamic)
	{
		for (auto pC : m_pDynamicColliders)
		{
			auto tC = pC->GetColliderRect();
			if (pC->GetSceneObject() == pCaller || !pC->GetSceneObject()->IsActive())
			{
				continue;
			}

			if (LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y }, hit) || //Top
				LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y + tC.height }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit) || //Bot
				LineInterSection(A, B, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x, tC.pos.y + tC.height }, hit) || //Left
				LineInterSection(A, B, Vector2{ tC.pos.x + tC.width, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit)) // Right
			{
				hit.other = pC->GetSceneObject();
				return true;
			}
		}
	}

	
	for(auto pC : m_pStaticColliders)
	{
		 auto tC = pC->GetColliderRect();
		 if(pC->GetSceneObject() == pCaller || !pC->GetSceneObject()->IsActive())
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


void tyr::Physics::Update()
{
	//NOTE: Don't use position in this yet, this is not done yet
	std::for_each(m_pDynamicColliders.begin(), m_pDynamicColliders.end(), [&](ColliderComp* pDynamic)
		{
			if (!pDynamic->GetSceneObject()->IsActive())
				return;

			auto tC = pDynamic->GetColliderRect();
			RaycastHit hit;

			const float offset = 0.f;
			auto topLeft = Vector2(tC.pos.x, tC.pos.y + offset);
			auto topRight = Vector2(topLeft.x + tC.width, topLeft.y);

			auto botRight = Vector2(topRight.x, topRight.y + tC.height);
			auto botLeft = Vector2(topRight.x, botRight.y);
		
			if (Raycast(topLeft, topRight, hit, pDynamic, pDynamic->GetSceneObject()->GetTag()))
			{
				pDynamic->OnColliderHit(hit);
			}
			if (Raycast(topRight, botRight, hit, pDynamic, pDynamic->GetSceneObject()->GetTag()))
			{
				pDynamic->OnColliderHit(hit);
			}
			if (Raycast(botRight, botLeft, hit, pDynamic, pDynamic->GetSceneObject()->GetTag()))
			{
				pDynamic->OnColliderHit(hit);
			}
			if (Raycast(botLeft, tC.pos, hit, pDynamic, pDynamic->GetSceneObject()->GetTag()))
			{
				pDynamic->OnColliderHit(hit);
			}
		});
	



	
}
void tyr::Physics::AddCollider(ColliderComp* pCollider)
{
	if (pCollider->IsDynamic())
		AddCollider(pCollider, m_pDynamicColliders);
	else
		AddCollider(pCollider, m_pStaticColliders);

}
void tyr::Physics::RemoveCollider(ColliderComp* pCollider)
{
	if (pCollider->IsDynamic())
		RemoveCollider(pCollider, m_pDynamicColliders);
	else
		RemoveCollider(pCollider, m_pStaticColliders);
}
void tyr::Physics::SwitchVector(ColliderComp* pCollider)
{
	if (pCollider->IsDynamic())
	{
		RemoveCollider(pCollider, m_pStaticColliders);
		AddCollider(pCollider, m_pDynamicColliders);
	}
	else
	{
		RemoveCollider(pCollider, m_pDynamicColliders);
		AddCollider(pCollider, m_pStaticColliders);
	}
}

void tyr::Physics::AddCollider(ColliderComp* pCollider, std::vector<ColliderComp*>& vec)
{
	const auto found = std::find(vec.begin(), vec.end(), pCollider);
	if (found == vec.end())
	{
		vec.emplace_back(pCollider);
	}

}
void tyr::Physics::RemoveCollider(ColliderComp* pCollider, std::vector<ColliderComp*>& vec)
{
	auto found = std::find(vec.begin(), vec.end(), pCollider);
	if (found != vec.end())
	{
		vec.erase(found);
	}
}

bool tyr::Physics::Raycast(const Vector2& pos1, const Vector2& pos2, RaycastHit& hit, ColliderComp* pCaller, Tag ignoreTag)
{
	//no std::for_each because you want to return once you hit, if 1sth out of 1000 is hit, return and ignore the rest
	for (auto pC : m_pStaticColliders)
	{
		auto tC = pC->GetColliderRect();
		if (!pC->GetSceneObject()->IsActive() ||
			pC == pCaller) 
			continue;

		
		if(ignoreTag != Tag::None && pC->GetSceneObject()->GetTag() == ignoreTag)
			continue;

		
		if (LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y }, hit) || //Top
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y + tC.height }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit) || //Bot
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x, tC.pos.y + tC.height }, hit) || //Left
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x + tC.width, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit)) // Right
		{
			hit.other = pC->GetSceneObject();
			return true;
		}
	}
	
	for (auto pC : m_pDynamicColliders)
	{
		auto tC = pC->GetColliderRect();
		if (!pC->GetSceneObject()->IsActive() ||
			pC == pCaller)
			continue;
		if (ignoreTag != Tag::None && pC->GetSceneObject()->GetTag() == ignoreTag)
			continue;

		
		if (LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y }, hit) || //Top
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y + tC.height }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit) || //Bot
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x, tC.pos.y }, Vector2{ tC.pos.x, tC.pos.y + tC.height }, hit) || //Left
			LineInterSection(pos1, pos2, Vector2{ tC.pos.x + tC.width, tC.pos.y }, Vector2{ tC.pos.x + tC.width, tC.pos.y + tC.height }, hit)) // Right
		{
			hit.other = pC->GetSceneObject();
			return true;
		}
	}




	
	return false;
}

bool tyr::Physics::LineInterSection(const Vector2& pos1A, const Vector2& pos1B, const Vector2& pos2A, const Vector2& pos2B, RaycastHit& hit)
{
	const auto ab = pos1B - pos1A;
	const auto cd = pos2B - pos2A;

	const auto rsCross = ab.Cross(cd);


	auto e = (pos2A - pos1A).Cross(cd);
	auto f = (pos2A - pos1A).Cross(ab);
	
	//when cross is 0 (they are on the same line)
	if(std::abs(rsCross) < FLOAT_PRECISION)
	{
		////Overlapping?
		//if(std::abs(e) < FLOAT_PRECISION && std::abs(f) < FLOAT_PRECISION)
		//{
		//	hit.point = pos2B;
		//	return true;
		//}
		return false; //return false for now when on the same line
	}
	e /= rsCross;
	f /= rsCross;

	if (f >= 0 && f <= 1 && e >= 0 && e <= 1)
	{

		hit.point = pos1A + (ab * e);
		
		// a+ tr || c + us
		

		return true;
	}

	return false;
}

