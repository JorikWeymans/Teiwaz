#include "tyrpch.h"
#include "AnimatorVariable.h"
#include "TyrFunctions.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
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
tyr::AnimatorVariable::AnimatorVariable() // Private
	: m_Name("")
	, m_Type(VariableType::Float)
	, m_Equation(Equation::Equal)
	, fSetValue(0.f)
	, fComparatorValue(0.f) {}

tyr::AnimatorVariable* tyr::AnimatorVariable::Create(BinaryReader& reader)
{
	AnimatorVariable* pTheVariable = new AnimatorVariable();
	pTheVariable->m_Name     = reader.ReadString();
	pTheVariable->m_Type     = reader.Read<VariableType>();
	pTheVariable->m_Equation = reader.Read<Equation>();

	
	switch (pTheVariable->m_Type)
	{
	case VariableType::Bool:
		{
		const bool readBool = reader.Read<bool>();
		pTheVariable->bComparatorValue = readBool;
		pTheVariable->bSetValue = readBool;
		break;
		}
		
	case VariableType::Float:
		{
			const float readFloat = reader.Read<float>();
			pTheVariable->fComparatorValue = readFloat;
			pTheVariable->fSetValue = readFloat;
			break;
		}
	default:
#ifdef EDITOR_MODE
		SDXL_ImGui_ConsoleLogError("AnimatorVariable type is wrong");
#endif
		;
	}
	
	return pTheVariable;
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


#ifdef EDITOR_MODE
void tyr::AnimatorVariable::Save(BinaryWriter& writer)
{
	writer.Write(m_Name);
	writer.Write(m_Type);
	writer.Write(m_Equation);

	//No need to save setvalue, because the save is for saving animator, not the state of the game
	switch (m_Type)
	{
		case VariableType::Bool:
			writer.Write(bComparatorValue);
		break;
		case VariableType::Float:
			writer.Write(fComparatorValue);
		break;
		default:
			SDXL_ImGui_ConsoleLogError("AnimatorVariable type is wrong")
		; }
	}


#endif
