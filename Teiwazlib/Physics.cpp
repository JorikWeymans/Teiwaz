#include "tyrpch.h"
#include "Physics.h"
#include "Vectors.h"
#include "TeiwazEngine.h"
#include "Color.h"
#include "ColliderComp.h"
bool tyr::Physics::Raycast(const Vector2& pos, const Vector2& direction, float length)
{
	// Vec1
	auto A = pos;
	auto B = A + (direction * length);

	// Vec2
	//const float yPos = 450;
	//auto C = Vector2(300, yPos); TeiwazEngine::GameToEngineSpace(pContext, &C);
	//auto D = Vector2(400, yPos); TeiwazEngine::GameToEngineSpace(pContext, &D);
	//SDXL_RenderDebugLine(static_cast<SDXL::SDXLVec2>(C), static_cast<SDXL::SDXLVec2>(D), static_cast<SDXL::SDXLVec4>(ColorWhite));

	
	for(auto pC : m_pColliders)
	{
		auto thisCollider = pC->GetColliderRect();

		auto C = Vector2{ thisCollider.pos.x, thisCollider.pos.y };
		auto D = Vector2{ thisCollider.pos.x + thisCollider.width, thisCollider.pos.y };
		auto ab = B - A;
		auto cd = D - C;

		auto rsCross = ab.Cross(cd);

		auto e = (C - A).Cross(cd) / rsCross;
		auto f = (C - A).Cross(ab) / rsCross;

		if (f >= 0 && f <= 1 && e >= 0 && e <= 1)
		{

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
