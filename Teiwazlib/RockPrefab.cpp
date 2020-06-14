#include "tyrpch.h"
#include "RockPrefab.h"
#include "SceneObject.h"
#include "Scene.h"
#include "Vectors.h"
#include "Transform.h"
#include "TyrComps.h"
void tyr::RockPrefab::Generate(Scene* pScene, const Vector2& pos, bool isGoingLeft)
{
	auto obj = new SceneObject(Transform(pos), "Rock");
	pScene->BufferSceneObject(obj);
	obj->AddComponent(new ColliderComp(43.f, 48.f, PivotMode::Center, true));
	obj->AddComponent(new CharacterControllerComp(5.f));
	auto pBody = obj->AddComponent(new RigidBodyComp(0.f, false));
	obj->AddComponent(new TextureComp(3, PivotMode::Center, Rect(528, 384, 48, 48), Vector2(0.5f, 0.5f), true));
	obj->AddComponent(new AnimatorComp(5));

	if(isGoingLeft)
		pBody->AddForce(-300.f, 0);
	else
		pBody->AddForce(300.f, 0);
}
