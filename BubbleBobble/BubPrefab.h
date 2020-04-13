#pragma once
namespace tyr
{
	class Scene;
	class CharacterControllerComp;
	class RigidBodyComp;
}
namespace bub
{
	class BubPrefab final
	{
	public:
		BubPrefab() = default;
		~BubPrefab() = default;
		void Generate(tyr::Scene* pScene);
	public:
		BubPrefab(const BubPrefab&) = delete;
		BubPrefab(BubPrefab&&) = delete;
		BubPrefab& operator=(const BubPrefab&) = delete;
		BubPrefab& operator=(BubPrefab&&) = delete;
	};


}
