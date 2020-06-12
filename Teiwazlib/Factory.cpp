#include "tyrpch.h"
#include "Factory.h"
#include "TyrComps.h"


tyr::TransformComp*           tyr::Factory::CreateTransformComp(BinaryReader& reader)
{

	return new TransformComp(Transform(reader.Read<Transform_POD>()));
}

tyr::CharacterControllerComp* tyr::Factory::CreateCharacterControllerComp(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	return new CharacterControllerComp();
}

tyr::ColliderComp*            tyr::Factory::CreateColliderComp(BinaryReader& reader)
{
	const float width    = reader.Read<float>();
	const float height   = reader.Read<float>();
	const PivotMode mode = reader.Read<PivotMode>();
	const bool isDynamic = reader.Read<bool>();

	return new ColliderComp(width, height, mode, isDynamic);
}

tyr::RigidBodyComp*           tyr::Factory::CreateRigidBodyComp(BinaryReader& reader)
{
	return new RigidBodyComp(reader.Read<float>());
}

tyr::FPSComp*                 tyr::Factory::CreateFPSComp(BinaryReader& reader)
{
	const FPSCompType type = reader.Read<FPSCompType>();
	const UINT textIndex = reader.Read<UINT>();

	return new FPSComp(type, textIndex);
}

tyr::TextureComp*             tyr::Factory::CreateTextureComp(BinaryReader& reader)
{
	const TextureID id   = reader.Read<TextureID>();
	const Vector2_POD pivot  = reader.Read<Vector2_POD>();
	const Rect_POD    rect   = reader.Read<Rect_POD>();
	const Vector2_POD offset = reader.Read<Vector2_POD>();
	
	return new TextureComp(id, Vector2(pivot), Rect(rect), Vector2(offset));
	
	
}
tyr::TextComp*                tyr::Factory::CreateTextComp(BinaryReader& reader)
{

	const std::string path   = reader.ReadString();
	const std::string text   = reader.ReadString();

	const float r            = reader.Read<float>();
	const float g            = reader.Read<float>();
	const float b            = reader.Read<float>();
	const float a            = reader.Read<float>();

	const Vector2_POD offset = reader.Read<Vector2_POD>();
	
	return new TextComp(path, text, Color(r, g, b, a), Vector2(offset));

	
}

tyr::Player1Controller*       tyr::Factory::CreatePlayer1Comp(BinaryReader& reader)
{
	const float force = reader.Read<float>();
	return new Player1Controller(force);
}

tyr::AnimatorComp*			  tyr::Factory::CreateAnimatorComp(BinaryReader& reader)
{
	const AnimatorID id = reader.Read<AnimatorID>();
	return new AnimatorComp(id);
}

tyr::BubbleShootingComp*	  tyr::Factory::CreateBubbleShootingComp(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	return new BubbleShootingComp();
}

tyr::ZenChanComp*			  tyr::Factory::CreateZenChanComp(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	return new ZenChanComp();
}

tyr::MaitaComp*			      tyr::Factory::CreateMaitaComp(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	return new MaitaComp();
}
