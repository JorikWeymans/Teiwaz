#include "tyrpch.h"
#include "Factory.h"
#include "TyrComps.h"


tyr::TransformComp* tyr::Factory::CreateTransformComp(BinaryReader& reader)
{

	return new TransformComp(Transform(reader.Read<Transform_POD>()));
}

tyr::CharacterControllerComp* tyr::Factory::CreateCharacterControllerComp(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	return new CharacterControllerComp();
}

tyr::ColliderComp* tyr::Factory::CreateColliderComp(BinaryReader& reader)
{
	const float width = reader.Read<float>();
	const float height = reader.Read<float>();
	const PivotMode mode = reader.Read<PivotMode>();
	const bool isDynamic = reader.Read<bool>();

	return new ColliderComp(width, height, mode, isDynamic);
}

tyr::RigidBodyComp* tyr::Factory::CreateRigidBodyComp(BinaryReader& reader)
{
	return new RigidBodyComp(reader.Read<float>());
}
