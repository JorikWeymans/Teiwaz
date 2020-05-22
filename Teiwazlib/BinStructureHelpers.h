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
		CharacterController,
		Collider,
		FPS,
		RigidBody,
		Text,
		Texture,
		Transform,
		Player1Controller,
		Animator,
		BubbleShootingComp,
		//Append here


	};

	enum class ContentType : unsigned char //BYTE (don't Expect to go over 256 values)
	{
		Texture,
		Font,
		Animation,
		//Append here
		End = 255,
		
	};
}