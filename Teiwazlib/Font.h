#pragma once
namespace tyr
{
	class Font final
	{
	public:
		explicit Font(const std::wstring& dataFolder, const std::wstring& path);
		~Font();
		SDXL::SDXLFont* SDXL() const;

		//rhs == dataPath that gets hashed on creation
		friend bool operator==(Font* lhs, const std::wstring& rhs);
	private:
		SDXL::SDXLFont* m_pFont;
		size_t m_Hash;

	public:
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) = delete;
	};
}


