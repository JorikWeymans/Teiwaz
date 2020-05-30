#include "tyrpch.h"
#include "TyrEnums.h"

namespace tyr
{
	Tag operator<<(const Tag& tag, const int& rhs)
	{
		BYTE castTag = static_cast<BYTE>(tag);
		if (castTag == 0x0)
			return static_cast<Tag>(0x1);

		if (castTag == 0xFF) //wrapping
			return static_cast<Tag>(0x0);

		//else
		Tag returnValue = static_cast<Tag>(static_cast<BYTE>(tag) << rhs);

		if (magic_enum::enum_contains(returnValue))
		{
			return returnValue;
		}

		//else
		return static_cast<Tag>(0xFF);


	}
	Tag operator++(tyr::Tag& tag, int)
	{
		tag = tag << 1;
		return tag; // to let the operator append
	}

	Tag operator>>(const Tag& tag, const int& rhs)
	{
		BYTE castTag = static_cast<BYTE>(tag);
		
		if (castTag == 0x00) //wrapping
			return static_cast<Tag>(0xFF);

		//else
		Tag returnValue = static_cast<Tag>(static_cast<BYTE>(tag) >> rhs);

		if(!magic_enum::enum_contains(returnValue))
		{
			returnValue = static_cast<Tag>(0x80); //Give it the left most bit to shift it (because all has every bit checked)
			while (!magic_enum::enum_contains(returnValue))
			{
				returnValue = static_cast<Tag>(static_cast<BYTE>(returnValue) >> rhs);
			}
		}

		return returnValue;


	}
	Tag operator--(tyr::Tag& tag, int)
	{
		tag = tag >> 1;
		return tag; // to let the operator append
	}
}
