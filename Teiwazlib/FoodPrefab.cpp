#include "tyrpch.h"
#include "FoodPrefab.h"
#include "SceneObject.h"
#include "Transform.h"
#include "TyrComps.h"
#include "Scene.h"
void tyr::FoodPrefab::Generate(Scene* pScene, const Vector2& pos, FoodType type)
{
	auto obj = new SceneObject(Transform(pos), "Food");
	pScene->BufferSceneObject(obj);

	const auto pivotMode = PivotMode::Center;

	obj->AddComponent(new ColliderComp(53, 47, pivotMode, true));
	switch (type)
	{
		case FoodType::Melon:
			obj->AddComponent(new TextureComp(3, pivotMode, Rect(720.f, 720.f, 48, 48), Vector2(0, -4), true));
		break;
		case FoodType::Fries:
		_FALLTHROUGH
		default:
			obj->AddComponent(new TextureComp(3, pivotMode, Rect(672.f, 720.f, 48, 48), Vector2(0, -4), true));
		; }
	

	obj->AddComponent(new FoodComp(type));
	obj->AddComponent(new CharacterControllerComp(9));
	obj->AddComponent(new RigidBodyComp(-150.f));
	
	
}
