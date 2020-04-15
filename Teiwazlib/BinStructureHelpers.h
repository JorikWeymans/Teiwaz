#pragma once
namespace tyr
{
	enum class ObjectType : unsigned char //BYTE
	{
		SceneObject,
		Component,

		End,
	};

	enum class ComponentType : unsigned int //UINT
	{
		CharacterController,
		Collider,
		FPS,
		RigidBody,
		Text,
		Texture,
		Transform,
		Player1Controller,
		Animator,


	};
}