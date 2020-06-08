#pragma once
#include "Vectors.h"

namespace tyr
{
	class ContentManager;
	class CMTextures;
	class Texture final
	{
	public:
		SDXL::SDXLImage* SDXL() const;
		const Vector2& GetDimension() const;
		const std::string& GetName() const;

		~Texture();
	private:
		friend ContentManager;
		friend CMTextures;
		explicit Texture(const std::string& dataFolder, const std::string& name);


		friend bool operator==(Texture* lhs, const std::string& rhs); //rhs == dataPath that gets hashed on creation

		
		SDXL::SDXLImage* m_pImage;
		size_t m_Hash;
		std::string m_Name;
		Vector2 m_Dimension;

	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;
	};


	
}


