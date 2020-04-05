#pragma once
namespace tyr
{
	class ContentManager;

	class Font final
	{
	public:

		SDXL::SDXLFont* SDXL() const;
	private:
		friend ContentManager;

		explicit Font(const std::wstring& dataFolder, const std::wstring& path);
		~Font();
		
		friend bool operator==(Font* lhs, const std::wstring& rhs); //rhs == dataPath that gets hashed on creation
		

		SDXL::SDXLFont* m_pFont;
		size_t m_Hash;

	public:
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) = delete;
	};
}


