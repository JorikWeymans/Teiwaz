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
		void SwitchVector(ColliderComp* pCollider); // Go from static to dynamic and visa versa, switch to other type before calling
		void Update();
	private:
		std::vector<ColliderComp*> m_pStaticColliders;
		std::vector<ColliderComp*> m_pDynamicColliders;
		
		static bool LineInterSection(const Vector2& pos1A, const Vector2& pos1B, const Vector2& pos2A, const Vector2& pos2B, RaycastHit& hit);

		static void AddCollider(ColliderComp* pCollider, std::vector<ColliderComp*>& vec);
		static void RemoveCollider(ColliderComp* pCollider, std::vector<ColliderComp*>& vec);

		bool Raycast(const Vector2& pos1, const Vector2& pos2, RaycastHit& hit, ColliderComp* pCaller = nullptr, Tag ignoreTag = Tag::None);
	public:
		Physics(const Physics&) = delete;
		Physics(Physics&&) = delete;
		Physics& operator=(const Physics&) = delete;
		Physics& operator=(Physics&&) = delete;
	};

}
