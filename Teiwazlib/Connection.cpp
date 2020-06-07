#include "tyrpch.h"
#include "Connection.h"

#include "BinaryWriter.h"
#include "BinaryReader.h"

tyr::Connection::Connection(AnimationID _Lhs, AnimationID _Rhs, AnimatorVariable* _pVariable)
	: lhs(_Lhs)
	, rhs(_Rhs)
	, pVariable(_pVariable)
{
}
tyr::Connection::Connection()
	: lhs(0)
	, rhs(0)
	, pVariable(nullptr)
{
}

tyr::Connection::~Connection()
{
	SAFE_DELETE(pVariable);
}

void tyr::Connection::Save(BinaryWriter& writer)
{
	writer.Write(lhs);
	writer.Write(rhs);
	pVariable->Save(writer);

}

tyr::Connection* tyr::Connection::Create(BinaryReader& reader)
{
	UNREFERENCED_PARAMETER(reader);
	Connection* pTheConnection = new Connection();
	pTheConnection->lhs = reader.Read<AnimationID>();
	pTheConnection->rhs = reader.Read<AnimationID>();
	pTheConnection->pVariable = AnimatorVariable::Create(reader);



	return pTheConnection;
}

