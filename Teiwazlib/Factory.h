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
	class BubbleShootingComp;
	class MaitaComp;
	class ZenChanComp;
	class PlayerHealthComp;
	class HealthDisplayComp;
	class MenuSelectorComp;
	class ButtonComp;
	class Scene;
	//This class helps when loading the scene (prevents functions in components itself which clutter the class
	class Factory final
	{
	public:
		template<typename  T>
		_NODISCARD static T* CreateComponent(BinaryReader& reader)
		{
			UNREFERENCED_PARAMETER(reader);
			THROW_ERROR(L"This component is not implemented yet");
		}
		template<> _NODISCARD static TransformComp*			  CreateComponent(BinaryReader& reader) { return CreateTransformComp(reader); }
		template<> _NODISCARD static CharacterControllerComp* CreateComponent(BinaryReader& reader) { return CreateCharacterControllerComp(reader); }
		template<> _NODISCARD static ColliderComp*			  CreateComponent(BinaryReader& reader) { return CreateColliderComp(reader); }
		template<> _NODISCARD static RigidBodyComp*			  CreateComponent(BinaryReader& reader) { return CreateRigidBodyComp(reader); }
		template<> _NODISCARD static FPSComp*				  CreateComponent(BinaryReader& reader) { return CreateFPSComp(reader); }
		template<> _NODISCARD static TextureComp*             CreateComponent(BinaryReader& reader) { return CreateTextureComp(reader); }
		template<> _NODISCARD static TextComp*                CreateComponent(BinaryReader& reader) { return CreateTextComp(reader); }
		template<> _NODISCARD static Player1Controller*		  CreateComponent(BinaryReader& reader) { return CreatePlayer1Comp(reader); }
		template<> _NODISCARD static AnimatorComp*			  CreateComponent(BinaryReader& reader) { return CreateAnimatorComp(reader); }
		template<> _NODISCARD static BubbleShootingComp*      CreateComponent(BinaryReader& reader) { return CreateBubbleShootingComp(reader); }
		template<> _NODISCARD static MaitaComp*               CreateComponent(BinaryReader& reader) { return CreateMaitaComp(reader); }
		template<> _NODISCARD static ZenChanComp*             CreateComponent(BinaryReader& reader) { return CreateZenChanComp(reader); }
		template<> _NODISCARD static PlayerHealthComp*        CreateComponent(BinaryReader& reader) { return CreatePlayerHealthComp(reader); }
		template<> _NODISCARD static HealthDisplayComp*       CreateComponent(BinaryReader& reader) { return CreateHealthDisplayComp(reader); }
		template<> _NODISCARD static MenuSelectorComp*	      CreateComponent(BinaryReader& reader) { return CreateMenuSelectorComp(reader); }
		template<> _NODISCARD static ButtonComp*			  CreateComponent(BinaryReader& reader) { return CreateButtonComp(reader); }
		
	private:
		_NODISCARD static TransformComp*           CreateTransformComp(BinaryReader& reader);
		_NODISCARD static CharacterControllerComp* CreateCharacterControllerComp(BinaryReader& reader);
		_NODISCARD static ColliderComp*            CreateColliderComp(BinaryReader& reader);
		_NODISCARD static RigidBodyComp*           CreateRigidBodyComp(BinaryReader& reader);
		_NODISCARD static FPSComp*				   CreateFPSComp(BinaryReader& reader);
		_NODISCARD static TextureComp*             CreateTextureComp(BinaryReader& reader);
		_NODISCARD static TextComp*                CreateTextComp(BinaryReader& reader);
		_NODISCARD static Player1Controller*       CreatePlayer1Comp(BinaryReader& reader);
		_NODISCARD static AnimatorComp*            CreateAnimatorComp(BinaryReader& reader);
		_NODISCARD static BubbleShootingComp*      CreateBubbleShootingComp(BinaryReader& reader);
		_NODISCARD static MaitaComp*               CreateMaitaComp(BinaryReader& reader);
		_NODISCARD static ZenChanComp*             CreateZenChanComp(BinaryReader& reader);
		_NODISCARD static PlayerHealthComp*        CreatePlayerHealthComp(BinaryReader& reader);
		_NODISCARD static HealthDisplayComp*	   CreateHealthDisplayComp(BinaryReader& reader);
		_NODISCARD static MenuSelectorComp*		   CreateMenuSelectorComp(BinaryReader& reader);
		_NODISCARD static ButtonComp*		       CreateButtonComp(BinaryReader& reader);
	public:
		Factory() = delete;
		~Factory() = delete;
		Factory(const Factory&) = delete;
		Factory(Factory&&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory& operator=(Factory&&) = delete;
	};


}
