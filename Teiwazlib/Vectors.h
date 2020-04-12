#pragma once
#include "Proprties.h"
namespace tyr
{
	enum class PivotMode;
	struct Vector2_POD
	{
		float x, y;
	};
	class Vector2
	{
	public:
		Vector2() : Vector2(0.f,0.f) {}
		explicit Vector2(float x, float y);
		explicit Vector2(const PivotMode& pMode);
		explicit Vector2(const Vector2_POD& pod);
		explicit operator SDXL::SDXLVec2() const;

		float x, y;

		float Cross(const Vector2& rhs) const;

		Vector2_POD ToPOD() const;
		//Override operators
		Vector2& operator+=(const Vector2& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Vector2& operator-=(const Vector2& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		Vector2& operator*=(const Vector2& rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			return *this;
		}
		Vector2& operator*=(const float& rhs)
		{
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		Vector2& operator*=(const int& rhs)
		{
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		// friends defined inside class body are inline and are hidden from non-ADL lookup (cppreference)
		friend Vector2 operator+(Vector2 lhs, const Vector2& rhs)
		{
			lhs += rhs;
			return lhs;
		}
		friend Vector2 operator-(Vector2 lhs, const Vector2& rhs)
		{
			lhs -= rhs;
			return lhs;
		}
		friend Vector2 operator*(Vector2 lhs, const Vector2& rhs)
		{
			lhs *= rhs;
			return lhs;
		}
		friend Vector2 operator*(Vector2 lhs, const float& rhs)
		{
			lhs *= rhs;
			return lhs;
		}
		friend Vector2 operator*(Vector2 lhs, const int& rhs)
		{
			lhs *= rhs;
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

	struct Rect_POD
	{
		Vector2_POD v;
		float width, height;
	};
	class Rect final
	{
	public:
		explicit Rect();
		explicit Rect(float x, float y, float width, float height);
		explicit Rect(const Vector2& pos, float width, float height);
		explicit Rect(const Vector2& pos, const Vector2& dimension);
		explicit Rect(const Rect_POD& pod);
		
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
	
	

	inline Vector2 abs(const Vector2& v)
	{
		return  Vector2((v.x < 0) ? -v.x : v.x,
							(v.y < 0) ? -v.y : v.y);
		
	}
















	
}