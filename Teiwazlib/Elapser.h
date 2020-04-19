#pragma once
namespace tyr
{
	class Elapser final
	{
	public:
		Elapser();
		explicit Elapser(float elapseTime);

		//return true when elapsed, only does it once
		bool Update(float deltaTime);

		void Reset();
		void Reset(float newElapseTime);
		void SetMax(float newElapseTime);
		
		bool HasElapsed() const;
		float GetMax() const { return m_Max; }
		
	private:
		float m_Max, m_Current;
		bool m_HasElapsed;
	public:
		Elapser(const Elapser&) = delete;
		Elapser(Elapser&&) = delete;
		Elapser& operator=(const Elapser&) = delete;
		Elapser& operator=(Elapser&&) = delete;
	};


	
}
