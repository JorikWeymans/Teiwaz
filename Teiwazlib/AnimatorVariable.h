#pragma once
namespace tyr
{
	enum class VariableType : BYTE { Bool = 0, Float = 1 };
	enum class Equation : BYTE
	{
		Equal = 0,
		NotEqual = 1,
		BiggerThan = 2,
		SmallerThan = 3,
	};
	class AnimatorVariable final
	{
	public:
		explicit AnimatorVariable(const std::string& name, float _Data, Equation _Equation);
		explicit AnimatorVariable(const std::string& name, bool _Data,  Equation _Equation);
		AnimatorVariable(AnimatorVariable&& other) noexcept;
		~AnimatorVariable() = default;
		
		_NODISCARD const std::string& GetName() const noexcept { return m_Name; };
		_NODISCARD VariableType GetType() const noexcept { return m_Type; };


		bool DoEquation(float setValue);
		bool DoEquation(bool setValue);
	private:
		std::string m_Name;
		VariableType m_Type;
		Equation m_Equation;

		union
		{
			bool bSetValue{};
			float fSetValue;
		};

		union
		{
			bool bComparatorValue{};
			float fComparatorValue;
		};
	public:
		AnimatorVariable() = delete;
		AnimatorVariable(const AnimatorVariable&) = delete;

		AnimatorVariable& operator=(const AnimatorVariable&) = delete;
		AnimatorVariable& operator=(AnimatorVariable&&) = delete;
	};


}
