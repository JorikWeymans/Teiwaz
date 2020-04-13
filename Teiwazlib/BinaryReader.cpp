#include "tyrpch.h"
#include "BinaryReader.h"
#include <sstream>

// ***-------------------------------------------------------------***
// * _  _ ____ ____ _  _ ____ _       ____ ____ ____ ___  ____ ____  *
// * |\ | |  | |__/ |\/| |__| |       |__/ |___ |__| |  \ |___ |__/  *
// * | \| |__| |  \ |  | |  | |___    |  \ |___ |  | |__/ |___ |  \  *
// *                                                               	 *
// ***-------------------------------------------------------------***
tyr::BinaryReader::BinaryReader(const std::string& filePath, bool autoOpen)
	: m_FilePath(filePath)
	, m_IsOpen(false)
{
	if(autoOpen)
	{
		m_Reader = std::ifstream(m_FilePath, std::ios::in | std::ios::binary);
	}

	m_IsOpen = m_Reader.is_open();
}

void tyr::BinaryReader::Open()
{
	m_Reader = std::ifstream(m_FilePath, std::ios::in | std::ios::binary);
	m_IsOpen = m_Reader.is_open();
}

void tyr::BinaryReader::Close()
{
	m_Reader.close();
}

int tyr::BinaryReader::GetBufferPosition()
{

	
	if (!m_IsOpen) return -1;
	return static_cast<int>(m_Reader.tellg());
	
}

void tyr::BinaryReader::SetBufferPosition(int pos)
{
	if (!m_IsOpen) return;
	m_Reader.seekg(pos);
}

void tyr::BinaryReader::moveBufferPosition(int amount)
{
	if (!m_IsOpen) return;
	int bPos = GetBufferPosition();
	SetBufferPosition(bPos + amount);
}

std::string tyr::BinaryReader::ReadString()
{
	auto tempChar{ '0' };
	std::stringstream ss;

	while (tempChar != '\0')
	{
		m_Reader.read(static_cast<char*>(&tempChar), 1);
		if (tempChar != '\0')  ss << tempChar;

	}
	return ss.str();
}


// ***-------------------------------------------------***
// * _ _ _ _ ___  ____    ____ ____ ____ ___  ____ ____  *
// * | | | | |  \ |___    |__/ |___ |__| |  \ |___ |__/  *
// * |_|_| | |__/ |___    |  \ |___ |  | |__/ |___ |  \  *
// *                                                     *
// ***-------------------------------------------------***
//tyr::WBinaryReader::WBinaryReader(const std::wstring& filePath, bool autoOpen)
//	: m_FilePath(filePath)
//{
//	if (autoOpen)
//	{
//		m_Reader = std::wifstream(m_FilePath, std::wios::in | std::wios::binary);
//	}
//
//}
//
//void tyr::WBinaryReader::Open()
//{
//	m_Reader = std::wifstream(m_FilePath, std::wios::in | std::wios::binary);
//}
//
//void tyr::WBinaryReader::Close()
//{
//	m_Reader.close();
//}
//
//int tyr::WBinaryReader::GetBufferPosition()
//{
//	if (!m_Reader.is_open()) return -1;
//	return static_cast<int>(m_Reader.tellg());
//}
//
//void tyr::WBinaryReader::SetBufferPosition(int pos)
//{
//	if (!m_Reader.is_open()) return;
//	m_Reader.seekg(pos);
//}
//
//void tyr::WBinaryReader::moveBufferPosition(int amount)
//{
//	if (!m_Reader.is_open()) return;
//	int bPos = GetBufferPosition();
//	SetBufferPosition(bPos + amount);
//}
//
//std::wstring tyr::WBinaryReader::ReadString()
//{
//	std::wstringstream ss;
//	wchar_t temp;
//	while (true)
//	{
//		m_Reader.read(reinterpret_cast<wchar_t*>(&temp), 1);
//		if (temp == '\0') break;
//
//		ss << temp;
//
//	}
//	return ss.str();
//}