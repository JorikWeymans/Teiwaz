#pragma once
#include "AnimatorVariable.h"
namespace tyr
{
	class BinaryReader;
	class BinaryWriter;
	class Connection final
	{
	public:
		explicit Connection(AnimationID _Lhs, AnimationID _Rhs, AnimatorVariable* _pVariable);
		~Connection();
		void Save(BinaryWriter& writer);
		static Connection* Create(BinaryReader& reader);

		AnimationID lhs, rhs;
		AnimatorVariable* pVariable;
		
	private:
		Connection();

	public:
		Connection(const Connection&) = delete;
		Connection(Connection&&) = delete;
		Connection& operator=(const Connection&) = delete;
		Connection& operator=(Connection&&) = delete;
	};
}