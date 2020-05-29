#pragma once
#include <sstream>
#define FLOAT_PRECISION 0.01f
namespace tyr
{
	//Testing code
	////                    ----1---- ----2---- ----3---- ----4----      
	//unsigned int read = 0b1000'0000'0000'0000'0000'0000'0000'0000;
	//
	//auto bin = tyr::ToBinaryString(read);
	//
	//BYTE ch = 0b1000'1000;
	//
	//auto chbin = tyr::ToBinaryString(ch);
	
	template<typename T>
	std::string ToBinaryString(T var)
	{
		std::stringstream ss;
		for (int i{ sizeof(var) * 8U - 1 }; i >= 0; --i)
		{
			var & (1u << i) ? ss << '1' : ss << '0';
		}
		return ss.str();
	}


	inline bool IsZero(float value, float precision = FLOAT_PRECISION)
	{
		return std::abs(value) < precision;
	}
}