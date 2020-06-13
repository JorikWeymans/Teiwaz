#pragma once
namespace tyr
{
	enum class ObjectType : unsigned char //BYTE
	{
		SceneObject,
		Component,
		//Append here
		End = 255,
	};

	enum class ComponentType : unsigned int //UINT
	{
		//Not in alphabetical order because when the first ones are added, the order cannot change
		CharacterController,
		Collider,
		FPS,
		RigidBody,
		Text,
		Texture,
		Transform,
		Player1Controller,
		Animator,
		BubbleShooting,
		Bubble,
		ZenChan,
		Maita,

		PlayerHealth,
		HealthDisplay,
		MenuSelector,
		
		//Append here


	};

	enum class ContentType : unsigned char //BYTE (I don't Expect to go over 256 values)
	{
		Texture,
		Font,
		Animation,
		Scenes,
		Animators,
		//Append here
		End = 255,
		
	};
}