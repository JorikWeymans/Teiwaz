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
		tyr::CharacterControllerComp* GetController() const { return m_pController; }
		tyr::RigidBodyComp* GetBody() const { return m_pBody; }
	private:
		tyr::CharacterControllerComp* m_pController = nullptr;
		tyr::RigidBodyComp* m_pBody = nullptr;
	public:
		BubPrefab(const BubPrefab&) = delete;
		BubPrefab(BubPrefab&&) = delete;
		BubPrefab& operator=(const BubPrefab&) = delete;
		BubPrefab& operator=(BubPrefab&&) = delete;
	};


}
