#pragma once
#include <typeinfo>
#include "TransformComp.h"
namespace tyr
{
	class BinaryReader;
	class TransformComp;
	class CharacterControllerComp;
	class ColliderComp;
	class RigidBodyComp;
	
	
	//This class helps when loading the scene (prevents functions in components itself which clutter the class
	class Factory final
	{
	public:
		template<typename  T>
		static  T* CreateComponent(BinaryReader& reader)
		{
			return nullptr;
		}
		template<> static  TransformComp*           CreateComponent(BinaryReader& reader) { return CreateTransformComp(reader); }
		template<> static  CharacterControllerComp* CreateComponent(BinaryReader& reader) { return CreateCharacterControllerComp(reader); }
		template<> static  ColliderComp*            CreateComponent(BinaryReader& reader) { return CreateColliderComp(reader); }
		template<> static  RigidBodyComp*           CreateComponent(BinaryReader& reader) { return CreateRigidBodyComp(reader); }
		


	private:
		static TransformComp*           CreateTransformComp(BinaryReader& reader);
		static CharacterControllerComp* CreateCharacterControllerComp(BinaryReader& reader);
		static ColliderComp*            CreateColliderComp(BinaryReader& reader);
		static RigidBodyComp*           CreateRigidBodyComp(BinaryReader& reader);

	public:
		Factory() = delete;
		~Factory() = delete;
		Factory(const Factory&) = delete;
		Factory(Factory&&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory& operator=(Factory&&) = delete;
	};


}
