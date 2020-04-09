#pragma once
#include "Proprties.h"
namespace tyr
{
	enum class PivotMode;
	class Vector2
	{
	public:
		explicit Vector2(float x, float y);
		explicit Vector2(const PivotMode& pMode);
		
		float x, y;

		Vector2& operator+=(const Vector2& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}

		// friends defined inside class body are inline and are hidden from non-ADL lookup (cppreference)
		friend Vector2 operator+(Vector2 lhs, const Vector2& rhs)
		{
			lhs += rhs;
			return lhs;
		}
	};

	class Vector3
	{
	public:
		explicit Vector3(float x, float y, float z);
		explicit Vector3(const Vector2& vec);
		
		float x, y, z;
	};


	class Rect final
	{
	public:
		explicit Rect();
		explicit Rect(float x, float y, float width, float height);
		explicit Rect(const Vector2& pos, float width, float height);
		explicit Rect(const Vector2& pos, const Vector2& dimension);
		explicit operator SDXL::SDXLRect() const;

		void Set(float x, float y, float width, float height);
		

		static void AdjustRectToPivot(Rect& theRect, PivotMode pivot);
		explicit operator bool() const;



		
		PROPERTY(Vector2, pos); GET(pos) { return m_Pos; }  SET(pos) { m_Pos = value;}
		PROPERTY(float, width); GET(width) { return m_Width; }  SET(width) { m_Width = value; }
		PROPERTY(float, height); GET(height) { return m_Height; }  SET(height) { m_Height = value; }
	private:
	
		Vector2 m_Pos;
		float m_Width, m_Height;
		bool m_IsSet;
	};
	
	


















	
}