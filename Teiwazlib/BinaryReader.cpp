#include "tyrpch.h"
#include "BinaryReader.h"
#include <sstream>
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

