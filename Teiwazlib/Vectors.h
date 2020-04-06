#pragma once
namespace tyr
{
	enum class PivotMode;
	class Vector2
	{
	public:
		explicit Vector2(float x, float y);
		explicit Vector2(const PivotMode& pMode);
		
		float x, y;
		
	};

	class Vector3
	{
	public:
		explicit Vector3(float x, float y, float z);
		explicit Vector3(const Vector2& vec);
		
		float x, y, z;
	};


	class Rectangle
	{
	public:
		explicit Rectangle();
		explicit Rectangle(float x, float y, float width, float height);
		explicit Rectangle(const Vector2& pos, float width, float height);
		explicit Rectangle(const Vector2& pos, const Vector2& dimension);
		explicit operator SDXL::SDXLRect() const;

		void Set(float x, float y, float width, float height);
		
		
		explicit operator bool() const;
	private:
		Vector2 m_Pos;
		float m_Width, m_Height;
		bool m_IsSet;
	};
	
	


















	
}