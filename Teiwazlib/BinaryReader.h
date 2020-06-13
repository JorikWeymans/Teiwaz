#pragma once
#include <fstream>
namespace tyr
{
	// ***-------------------------------------------------------------***
	// * _  _ ____ ____ _  _ ____ _       ____ ____ ____ ___  ____ ____  *
	// * |\ | |  | |__/ |\/| |__| |       |__/ |___ |__| |  \ |___ |__/  *
	// * | \| |__| |  \ |  | |  | |___    |  \ |___ |  | |__/ |___ |  \  *
	// *                                                               	 *
	// ***-------------------------------------------------------------***
	class BinaryReader final
	{
	public:
		explicit BinaryReader(const std::string& filePath, bool autoOpen = true);
		~BinaryReader() = default;

		void Open();
		void Close();
		_NODISCARD bool IsOpen() const { return m_IsOpen; }

		_NODISCARD int Peek() { return m_Reader.peek(); }
		_NODISCARD int GetBufferPosition();
		void SetBufferPosition(int pos);
		void moveBufferPosition(int amount);

		std::string ReadString();
		template<typename T>
		T Read() //no _NODISCARD, because the user can omit what he read to just move in file
		{
			T data;
			if (!m_IsOpen || !std::is_pod<T>()) return T{};
			m_Reader.read(reinterpret_cast<char*>(&data), sizeof(T));
			return data;
		}

		template<>
		std::string Read()
		{
			return ReadString();
		}
	private:
		std::string m_FilePath;
		std::ifstream m_Reader;
		bool m_IsOpen;


	public:


		BinaryReader(BinaryReader&) = delete;
		BinaryReader(BinaryReader&&) = delete;
		BinaryReader& operator=(BinaryReader&) = delete;
		BinaryReader& operator=(BinaryReader&&) = delete;
	};
}

// ***-------------------------------------------------***
// * _ _ _ _ ___  ____    ____ ____ ____ ___  ____ ____  *
// * | | | | |  \ |___    |__/ |___ |__| |  \ |___ |__/  *
// * |_|_| | |__/ |___    |  \ |___ |  | |__/ |___ |  \  *
// *                                                     *
// ***-------------------------------------------------***                                                   
//class WBinaryReader final
//	{
//	public:
//		explicit WBinaryReader(const std::wstring& filePath, bool autoOpen = true);
//		~WBinaryReader() = default;
//
//		void Open();
//		void Close();
//		bool IsOpen() const { return m_Reader.is_open(); }
//
//		int Peek() { return m_Reader.peek(); }
//		int GetBufferPosition();
//		void SetBufferPosition(int pos);
//		void moveBufferPosition(int amount);
//
//		std::wstring ReadString();
//
//	private:
//		std::wstring m_FilePath;
//		std::wifstream m_Reader;
//
//
//	public:
//		template<typename T>
//		T Read()
//		{
//			T data;
//			if (!m_Reader.is_open() || !std::is_pod<T>()) return T{};
//			m_Reader.read(reinterpret_cast<wchar_t*>(&data), sizeof(T) / 2); // /2 cuz wchar = 2byte
//			return data;
//		}
//
//		WBinaryReader(WBinaryReader&) = delete;
//		WBinaryReader(WBinaryReader&&) = delete;
//		WBinaryReader& operator=(WBinaryReader&) = delete;
//		WBinaryReader& operator=(WBinaryReader&&) = delete;
//	};
//}
