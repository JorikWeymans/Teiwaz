#pragma once
#include <fstream>
namespace tyr
{
	class BinaryWriter final
	{
	public:
		explicit BinaryWriter(const std::string& filePath, bool autoOpen = true, bool generateSubFolder = true);
		~BinaryWriter();
		void Close();
		void Open();

		bool IsOpen() const;

		template<typename T>
		bool Write(T toWrite)
		{
			if(m_IsOpen && std::is_pod<T>())
			{
				m_Writer.write(reinterpret_cast<char*>(&toWrite), sizeof(T));
				return true;
			}
			return false;
		}
		void WriteString(const std::string& string);
		
	private:
		std::string m_FilePath;
		std::ofstream m_Writer;
		bool m_IsOpen;


		void CreateFolders(const std::string& path);
	public:
		
		BinaryWriter(BinaryWriter&) = delete;
		BinaryWriter(BinaryWriter&&) = delete;
		BinaryWriter& operator=(BinaryWriter&) = delete;
		BinaryWriter& operator=(BinaryWriter&&) = delete;
	};


}
