#pragma once
#include "string"
namespace  tyr
{
	
	inline std::string GetFileFromPath(const std::string& path)
	{
		const  auto latest{ path.find_last_of('/') };
		return path.substr(latest + 1);
	}

	inline std::string GetExtension(const std::string& path, bool periodRemoved = true)
	{
		const auto latest{ path.rfind('.') }; //rfind because extension is usally short and at the back
		return path.substr(latest + (periodRemoved ? 1:0) );
	}

	inline bool DoesExtensionMatch(const std::string& path, const std::string& extension, bool periodRemoved = true)
	{
		const std::string foundExtension{ GetExtension(path, periodRemoved) };
		
		return foundExtension == extension;
		
	}

	inline void RemoveExtension(std::string& path)
	{
		path = path.substr(0, path.find_last_of('.'));
	}

	//for conversion specifiers => https://en.cppreference.com/w/c/io/vfprintf
	inline const char* FormatCharArray(const char* str, ...)
	{

		va_list arguments;
		va_start(arguments, str);
		
		const unsigned int bufferSize = 512;
		char buffer[bufferSize];
		vsnprintf(buffer, bufferSize, str, arguments);
		
		buffer[bufferSize - 1] = 0;
		
		va_end(arguments);
		return _strdup(buffer);
	}

	

}