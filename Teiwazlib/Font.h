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

		explicit Font(const std::string& dataFolder, const std::string& path);
		~Font();
		
		friend bool operator==(Font* lhs, const std::string& rhs); //rhs == dataPath that gets hashed on creation
		

		SDXL::SDXLFont* m_pFont;
		size_t m_Hash;

	public:
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator=(const Font&) = delete;
		Font& operator=(Font&&) = delete;
	};
}


