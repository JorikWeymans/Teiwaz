#include "stdafx.h"
#include "ReadScene.h"
#include "ContentManager.h"
#include "BinStructureHelpers.h"
#include "TyrException.h"
#include <sstream>
#include "BinaryReader.h"
#include "Factory.h"
#include "SceneObject.h"
#include "TyrComps.h"

bub::ReadScene::ReadScene()
	: tyr::Scene("Read from file")
{
}

void bub::ReadScene::Initialize()
{
	using namespace  tyr;
	std::stringstream ss;
	ss << tyr::ContentManager::GetInstance()->GetDataFolder();
	ss << "Scenes/" << "Test" << ".tyrScene";
	
	BinaryReader reader(ss.str());
	// rn
	// header
	ULONG64 header = reader.Read<ULONG64>();
	if (header != 0x4A6F72696B576579)
	{
		SDXL_ImGui_ConsoleLogError("This is no a scene");
	}
	// sceneName
	std::string sceneName = reader.ReadString();
	UNREFERENCED_PARAMETER(sceneName);

	try
	{
		while (reader.Read<ObjectType>() == ObjectType::SceneObject)
		{
			auto parent = LoadSceneObject(reader, nullptr);

			const size_t childs = reader.Read<size_t>();
			for (size_t i{ 0 }; i < childs; ++i)
			{
				reader.Read<ObjectType>(); //no need to check, this is always an SeneObject.
				LoadSceneObject(reader, parent);
				reader.Read<size_t>(); //no need to save, only 1 depth child relation allowed
			}
		}
	}
	catch (TyrException & e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
	}
}

tyr::SceneObject* bub::ReadScene::LoadSceneObject(tyr::BinaryReader& reader, tyr::SceneObject* parent)
{
	using namespace  tyr;
	UNREFERENCED_PARAMETER(parent);
	SceneObject* newObject = nullptr;
	const std::string newObjectName = reader.ReadString();
	UINT size = reader.Read<UINT>();
	for (UINT i{ 0 }; i < size; i++)
	{
		const ComponentType type = reader.Read<ComponentType>();

		switch (type)
		{
		case ComponentType::Transform: //should always be the first
			newObject = new SceneObject(Factory::CreateComponent<TransformComp>(reader), newObjectName);

			if (parent) parent->AddChild(newObject);
			else
			 AddSceneObject(newObject);
			break;
		case ComponentType::CharacterController:
			newObject->AddComponent(Factory::CreateComponent<CharacterControllerComp>(reader));
			break;
		case ComponentType::Collider:
			newObject->AddComponent(Factory::CreateComponent<ColliderComp>(reader));
			break;
		case ComponentType::FPS:
			newObject->AddComponent(Factory::CreateComponent<FPSComp>(reader));
			break;
		case ComponentType::RigidBody:
			newObject->AddComponent(Factory::CreateComponent<RigidBodyComp>(reader));
			break;
		case ComponentType::Text:
			newObject->AddComponent(Factory::CreateComponent<TextComp>(reader));
			break;
		case ComponentType::Texture:
			newObject->AddComponent(Factory::CreateComponent<TextureComp>(reader));
			break;
		case ComponentType::Player1Controller:
			newObject->AddComponent(Factory::CreateComponent<Player1Controller>(reader));
			break;

		default:;
		}
		// Object
		//   transformCOm
		// Object
		//   TransformComp
		// Object
		//   TransformComp
		// End

	}
	return newObject;
}
