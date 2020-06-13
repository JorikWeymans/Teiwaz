#pragma once
namespace tyr
{
	struct Color_POD
	{
		float r, g, b, a;
	};
	class Color
	{
	public:
		explicit Color(float r, float g, float b, float a = 1.f);
		explicit operator SDXL::SDXLVec4() const;
		explicit operator SDXL::Float4() const;
		Color_POD ToPOD() const;
		
		float r, g, b, a;
	};


#define ColorBlack	 tyr::Color(0.0f,0.0f,0.0f,1.0f)
#define ColorGray    tyr::Color(0.5f,0.5f,0.5f,1.f)
#define ColorWhite	 tyr::Color(1.0f,1.0f,1.0f,1.0f)
#define ColorRed	 tyr::Color(.95f,0.0f,0.0f,1.0f)
#define ColorGreen	 tyr::Color(0.0f,.95f,0.0f,1.0f)
#define ColorBlue	 tyr::Color(0.0f,0.0f,.95f,1.0f)
#define ColorYellow	 tyr::Color(.95f,.95f,0.0f,1.0f)
#define ColorCyan	 tyr::Color(0.0f,.95f,.95f,1.0f)
#define ColorMagenta tyr::Color(.95f,0.0f,.95f,1.0f)
	

	
}


