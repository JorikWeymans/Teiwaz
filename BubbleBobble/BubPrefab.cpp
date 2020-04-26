#include "stdafx.h"
#include "BubPrefab.h"
#include "SceneObject.h"
#include "Scene.h"
#include "TyrComps.h"
void bub::BubPrefab::Generate(tyr::Scene* pScene)
{
	auto obj = new tyr::SceneObject(tyr::Transform(tyr::Vector2(378.f, 560), tyr::Vector2(1, 1)), "Player");
	pScene->AddSceneObject(obj);
	auto objs = new tyr::SceneObject(tyr::Transform(tyr::Vector2(378.f, 560), tyr::Vector2(1, 1)), "PlayerChild1");
	obj->AddChild(objs);
	obj->AddChild(new tyr::SceneObject(tyr::Transform(tyr::Vector2(378.f, 560), tyr::Vector2(1, 1)), "PlayerChild2"));

	const auto pivotMode = tyr::PivotMode::Center;
	obj->AddComponent(new tyr::ColliderComp(48, 48, pivotMode, true));
	obj->AddComponent(new tyr::TextureComp("Sprites_Sliced_Combined_Scaled.png", pivotMode, tyr::Rect(0.f, 0.f, 48.f, 48.f)));
	obj->AddComponent(new tyr::CharacterControllerComp());

	obj->AddComponent(new tyr::RigidBodyComp(0.f/*-150*/));
	obj->AddComponent(new tyr::AnimatorComp());
	obj->AddComponent(new tyr::Player1Controller());

}
