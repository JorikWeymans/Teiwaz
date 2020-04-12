#pragma once
#include <fstream>
namespace tyr
{
	class BinaryReader final
	{
	public:
		explicit BinaryReader(const std::string& filePath, bool autoOpen = true);
		~BinaryReader() = default;

		void Open();
		void Close();
		bool IsOpen() const { return m_IsOpen; }

		int Peek() { return m_Reader.peek(); }
		int GetBufferPosition();
		void SetBufferPosition(int pos);
		void moveBufferPosition(int amount);

		std::string ReadString();
		
	private:
		std::string m_FilePath;
		std::ifstream m_Reader;
		bool m_IsOpen;


	public:
		template<typename T>
		T Read()
		{
			T data;
			if (!m_IsOpen || !std::is_pod<T>()) return T{};
			m_Reader.read(reinterpret_cast<char*>(&data), sizeof(T));
			return data;
		}

		BinaryReader(BinaryReader&) = delete;
		BinaryReader(BinaryReader&&) = delete;
		BinaryReader& operator=(BinaryReader&) = delete;
		BinaryReader& operator=(BinaryReader&&) = delete;
	};


}
