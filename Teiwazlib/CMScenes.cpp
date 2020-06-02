#include "tyrpch.h"
#include "CMScenes.h"
#include <direct.h>
#include "StringManipulation.h"
#include <filesystem>
#include "Scene.h"
tyr::CMScenes::CMScenes(const std::string& absoluteSceneFolder)
{
	_mkdir(absoluteSceneFolder.c_str()); //making dir if dir does not exist
	for (auto& entry : std::filesystem::directory_iterator(absoluteSceneFolder))
	{

		std::string filename{ GetFileFromPath(entry.path().string()) };

		if (DoesExtensionMatch(filename, "tyrScene"))
		{
			RemoveExtension(filename);
			const auto test = filename;
			
			m_Scenes.emplace_back(new Scene(filename, absoluteSceneFolder));
			
		}
	}
}


