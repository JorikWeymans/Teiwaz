#pragma once
#include "string"
namespace  tyr
{

	inline std::string GetFileFromPath(const std::string& path)
	{
		const unsigned int latest{ path.find_last_of('/') };
		return path.substr(latest + 1);
	}

	inline std::string GetExtension(const std::string& path)
	{
		const unsigned int latest{ path.rfind('.') }; //rfind because extension is usally short and at the back
		return path.substr(latest + 1);
	}

	inline bool DoesExtensionMatch(const std::string& path, const std::string& extension)
	{
		const std::string foundExtension{ GetExtension(path) };
		
		return foundExtension == extension;
		
	}

	inline void RemoveExtension(std::string& path)
	{
		path = path.substr(0, path.find_last_of('.'));
	}


}