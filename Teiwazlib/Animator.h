#pragma once
#include <map>
#include <vector>
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
	};

	
	class Animation;
	class Rect;
	class Animator final
	{
	public:
		Animator();
		~Animator();

		void SetAnimation(AnimationID id);
		void Update(float elapsed);

		void SetFloat(const std::string& variable, float value);
		void SetBool(const std::string& variable, bool value);

		bool IsAtEnd() const;
		const Rect& GetCurrentAnimation() const;

		static Animator* Create(const std::string& path);
		
#ifdef EDITOR_MODE
		void Save();
#endif
	private:
		
		std::string m_Name;
		std::vector<Connection*> m_pConnections;;
		

		Animation* m_pCurrent; //weak pointer
		
	public:
		Animator(const Animator&) = delete;
		Animator(Animator&&) = delete;
		Animator& operator=(const Animator&) = delete;
		Animator& operator=(Animator&&) = delete;
	};


}
#pragma once
