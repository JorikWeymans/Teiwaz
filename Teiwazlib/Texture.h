#pragma once
namespace tyr
{
	class Texture final
	{
	public:
		explicit Texture(const std::wstring& dataFolder, const std::wstring& path);
		~Texture();
		SDXL::SDXLImage* SDXL() const;
		
		//rhs == dataPath that gets hashed on creation
		friend bool operator==(Texture* lhs, const std::wstring& rhs);
	private:
		SDXL::SDXLImage* m_pImage;
		size_t m_Hash;

	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;


	};


	
}


