#pragma once
#include <fstream>
namespace tyr
{
	// ***----------------------------------------------------------***
	// * _  _ ____ ____ _  _ ____ _       _ _ _ ____ _ ___ ____ ____  *
	// * |\ | |  | |__/ |\/| |__| |       | | | |__/ |  |  |___ |__/  *
	// * | \| |__| |  \ |  | |  | |___    |_|_| |  \ |  |  |___ |  \  *
	// *															  *
	// ***----------------------------------------------------------***
	class BinaryWriter final
	{
	public:
		explicit BinaryWriter(const std::string& filePath, bool autoOpen = true, bool generateSubFolder = true);
		~BinaryWriter() = default;
		void Close();
		void Open();

		bool IsOpen() const;

		template<typename T>
		bool Write(T toWrite)
		{
			if (m_IsOpen && std::is_pod<T>())
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


		static void CreateFolders(const std::string& path);
	public:

		BinaryWriter(BinaryWriter&) = delete;
		BinaryWriter(BinaryWriter&&) = delete;
		BinaryWriter& operator=(BinaryWriter&) = delete;
		BinaryWriter& operator=(BinaryWriter&&) = delete;
	};
}
	
// ***---------------------------------------------***
// * _ _ _ _ ___  ____    _ _ _ ____ _ ___ ____ ____ *
// * | | | | |  \ |___    | | | |__/ |  |  |___ |__/ *
// * |_|_| | |__/ |___    |_|_| |  \ |  |  |___ |  \ *
// *												 *
// ***---------------------------------------------***

	//class WBinaryWriter final
	//{
	//public:
	//	explicit WBinaryWriter(const std::wstring& filePath, bool autoOpen = true, bool generateSubFolder = true);
	//	~WBinaryWriter() = default;
	//	void Close();
	//	void Open();

	//	bool IsOpen() const;

	//	template<typename T>
	//	bool Write(T toWrite)
	//	{
	//		if (m_Writer.is_open() && std::is_pod<T>())
	//		{
	//			auto s = sizeof(T);
	//			
	//			m_Writer.write(reinterpret_cast<wchar_t*>(&toWrite), s /2); // /2 cuz wchar = 2byte
	//			return true;
	//		}
	//		return false;
	//	}
	//	void WriteString(const std::wstring& string);
	//private:
	//	std::wstring m_FilePath;
	//	std::wofstream m_Writer;


	//	static void CreateFolders(const std::wstring& path);
	//public:

	//	WBinaryWriter(WBinaryWriter&) = delete;
	//	WBinaryWriter(WBinaryWriter&&) = delete;
	//	WBinaryWriter& operator=(WBinaryWriter&) = delete;
	//	WBinaryWriter& operator=(WBinaryWriter&&) = delete;
	//};
//}
