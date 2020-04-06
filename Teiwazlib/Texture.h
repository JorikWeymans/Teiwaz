#pragma once
#include "Vectors.h"

namespace tyr
{
	class ContentManager;

	class Texture final
	{
	public:
		SDXL::SDXLImage* SDXL() const;
		const Vector2& GetDimension() const;
	private:
		friend ContentManager;

		explicit Texture(const std::wstring& dataFolder, const std::wstring& path);
		~Texture();

		friend bool operator==(Texture* lhs, const std::wstring& rhs); //rhs == dataPath that gets hashed on creation

		
		SDXL::SDXLImage* m_pImage;
		size_t m_Hash;
		Vector2 m_Dimension;

	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;
	};


	
}


