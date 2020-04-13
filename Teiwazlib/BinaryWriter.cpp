#include "tyrpch.h"
#include "BinaryWriter.h"

#include "sstream"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <conio.h> 
#include <direct.h>
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 
using namespace std;

// ***----------------------------------------------------------***
// * _  _ ____ ____ _  _ ____ _       _ _ _ ____ _ ___ ____ ____  *
// * |\ | |  | |__/ |\/| |__| |       | | | |__/ |  |  |___ |__/  *
// * | \| |__| |  \ |  | |  | |___    |_|_| |  \ |  |  |___ |  \  *
// *															  *
// ***----------------------------------------------------------***
tyr::BinaryWriter::BinaryWriter(const std::string& filePath, bool autoOpen, bool generateSubFolder)
	: m_FilePath(filePath)
	, m_IsOpen(false)
{
	UNREFERENCED_PARAMETER(autoOpen);



	if (generateSubFolder) CreateFolders(filePath);

	
	if (autoOpen)
	{
		m_Writer = std::ofstream(m_FilePath, std::ios::out | std::ios::binary);
	}
	m_IsOpen = m_Writer.is_open();
}

void tyr::BinaryWriter::Close()
{

	m_Writer.close();
	m_IsOpen = m_Writer.is_open();

}

void tyr::BinaryWriter::Open()
{
	if (!m_IsOpen)
	{
		m_Writer = std::ofstream(m_FilePath, std::ios::out | std::ios::binary);
		m_IsOpen = m_Writer.is_open();
	}
}

bool tyr::BinaryWriter::IsOpen() const
{
	return m_IsOpen;
}

void tyr::BinaryWriter::WriteString(const std::string& string)
{
	const streamsize size = static_cast<streamsize>(string.size() + 1U);
	m_Writer.write(static_cast<const char*>(string.c_str()), size);
}

void tyr::BinaryWriter::CreateFolders(const std::string& path)
{
	int index = 2;

	size_t found = path.find('/', index);
	while (found < path.size())
	{

		std::string subbed = path.substr(0, found + 1);
#pragma warning (suppress : 6031)
		 _mkdir(subbed.c_str());
		index = subbed.size();
		found = path.find('/', index);
	}
}


// ***---------------------------------------------***
// * _ _ _ _ ___  ____    _ _ _ ____ _ ___ ____ ____ *
// * | | | | |  \ |___    | | | |__/ |  |  |___ |__/ *
// * |_|_| | |__/ |___    |_|_| |  \ |  |  |___ |  \ *
// *												 *
// ***---------------------------------------------***
//tyr::WBinaryWriter::WBinaryWriter(const std::wstring& filePath, bool autoOpen, bool generateSubFolder)
//	: m_FilePath(filePath)
//{
//	UNREFERENCED_PARAMETER(autoOpen);
//
//
//
//	if (generateSubFolder) CreateFolders(filePath);
//
//
//	if (autoOpen)
//	{
//		m_Writer = std::wofstream(m_FilePath, std::wios::out | std::wios::binary);
//	}
//}
//
//void tyr::WBinaryWriter::Close()
//{
//	m_Writer.close();
//}
//
//void tyr::WBinaryWriter::Open()
//{
//	if (!m_Writer.is_open())
//	{
//		m_Writer = std::wofstream(m_FilePath, std::wios::out | std::wios::binary);
//	}
//}
//
//bool tyr::WBinaryWriter::IsOpen() const
//{
//	return m_Writer.is_open();
//}
//
//void tyr::WBinaryWriter::WriteString(const std::wstring& string)
//{
//	const streamsize size = string.size() + 1U;
//	
//	m_Writer.write(static_cast<const wchar_t*>(string.c_str()), size);
//}
//
//void tyr::WBinaryWriter::CreateFolders(const std::wstring& path)
//{
//	int index = 2;
//
//	size_t found = path.find('/', index);
//	while (found < path.size())
//	{
//
//		std::wstring subbed = path.substr(0, found + 1);
//#pragma warning (suppress : 6031)
//		_wmkdir(subbed.c_str());
//		index = subbed.size();
//		found = path.find('/', index);
//	}
//}