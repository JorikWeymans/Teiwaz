#pragma once
#include <typeinfo>
#include "TransformComp.h"
#include "TyrException.h"
namespace tyr
{
	class BinaryReader;
	class TransformComp;
	class CharacterControllerComp;
	class ColliderComp;
	class RigidBodyComp;
	class FPSComp;
	class TextureComp;
	class TextComp;
	class Player1Controller;
	class AnimatorComp;
	class Scene;
	//This class helps when loading the scene (prevents functions in components itself which clutter the class
	class Factory final
	{
	public:
		template<typename  T>
		static T* CreateComponent(BinaryReader& reader)
		{
			UNREFERENCED_PARAMETER(reader);
			THROW_ERROR(L"This component is not implemented yet");
		}
		template<> static TransformComp*			CreateComponent(BinaryReader& reader) { return CreateTransformComp(reader); }
		template<> static CharacterControllerComp*	CreateComponent(BinaryReader& reader) { return CreateCharacterControllerComp(reader); }
		template<> static ColliderComp*				CreateComponent(BinaryReader& reader) { return CreateColliderComp(reader); }
		template<> static RigidBodyComp*			CreateComponent(BinaryReader& reader) { return CreateRigidBodyComp(reader); }
		template<> static FPSComp*					CreateComponent(BinaryReader& reader) { return CreateFPSComp(reader); }
		template<> static TextureComp*              CreateComponent(BinaryReader& reader) { return CreateTextureComp(reader); }
		template<> static TextComp*                 CreateComponent(BinaryReader& reader) { return CreateTextComp(reader); }
		template<> static Player1Controller*		CreateComponent(BinaryReader& reader) { return CreatePlayer1Comp(reader); }
		template<> static AnimatorComp*				CreateComponent(BinaryReader& reader) { return CreateAnimatorComp(reader); }

		
	private:
		static TransformComp*           CreateTransformComp(BinaryReader& reader);
		static CharacterControllerComp* CreateCharacterControllerComp(BinaryReader& reader);
		static ColliderComp*            CreateColliderComp(BinaryReader& reader);
		static RigidBodyComp*           CreateRigidBodyComp(BinaryReader& reader);
		static FPSComp*					CreateFPSComp(BinaryReader& reader);
		static TextureComp*             CreateTextureComp(BinaryReader& reader);
		static TextComp*                CreateTextComp(BinaryReader& reader);
		static Player1Controller*       CreatePlayer1Comp(BinaryReader& reader);
		static AnimatorComp*            CreateAnimatorComp(BinaryReader& reader);
	public:
		Factory() = delete;
		~Factory() = delete;
		Factory(const Factory&) = delete;
		Factory(Factory&&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory& operator=(Factory&&) = delete;
	};


}
