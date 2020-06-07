#include "tyrpch.h"
#include "AnimatorVariable.h"
#include "TyrFunctions.h"
tyr::AnimatorVariable::AnimatorVariable(const std::string& name, float _Data, Equation _Equation)
	: m_Name(name)
	, m_Type(VariableType::Float)
	, m_Equation(_Equation)
	, fSetValue(_Data)
	, fComparatorValue(_Data){}
tyr::AnimatorVariable::AnimatorVariable(const std::string& name, bool _Data, Equation _Equation)
	: m_Name(name)
	, m_Type(VariableType::Bool)
	, m_Equation(_Equation)
	, fSetValue(0.f)
	, fComparatorValue(0.f)
{
	bSetValue = _Data;
	bComparatorValue = _Data;
}
tyr::AnimatorVariable::AnimatorVariable(AnimatorVariable&& other) noexcept
	: m_Name(std::move(other.m_Name))
	, m_Type(other.m_Type)
	, m_Equation(other.m_Equation)
	, fSetValue(0.f)
	, fComparatorValue(0.f)
{
	switch (m_Type)
	{
		case VariableType::Bool:
			bSetValue = other.bSetValue;
			bComparatorValue = other.bComparatorValue;
		break;
		case VariableType::Float:
			fSetValue = other.fSetValue;
			fComparatorValue = other.fComparatorValue;
		break;
	default: ; }
}

bool tyr::AnimatorVariable::DoEquation(float setValue)
{
	fSetValue = setValue;

	switch (m_Equation)
	{
	case Equation::Equal:
		return std::abs(fSetValue - fComparatorValue) < FLOAT_PRECISION;
	case Equation::NotEqual:
		return !(std::abs(fSetValue - fComparatorValue) < FLOAT_PRECISION);
	case Equation::BiggerThan:
		return fSetValue > fComparatorValue;
	case Equation::SmallerThan:
		return fSetValue < fComparatorValue;
	default:
		return false;
	}
	

}

bool tyr::AnimatorVariable::DoEquation(bool setValue)
{
	bSetValue = setValue;

	switch (m_Equation)
	{
	case Equation::Equal:
		return bSetValue == bComparatorValue;
	case Equation::NotEqual:
		return bSetValue != bComparatorValue;
	case Equation::BiggerThan:
		_FALLTHROUGH
	case Equation::SmallerThan:
		_FALLTHROUGH
	default:
		return false;
	}
}
