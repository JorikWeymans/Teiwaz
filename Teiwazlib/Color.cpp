#include "tyrpch.h"
#include "Color.h"

tyr::Color::Color(float r, float g, float b, float a)
	:r(r), g(g), b(b), a(a)
{
}


tyr::Color::operator SDXL::SDXLVec4() const
{
	return { r,g,b,a };
}

tyr::Color::operator SDXL::Float4() const
{
	return SDXL::Float4( r,g,b,a );
}
