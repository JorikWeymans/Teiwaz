#pragma once
#include <map>
#include <vector>
#include "AnimatorVariable.h"
namespace tyr
{
	struct Connection
	{
		explicit Connection(AnimationID _Lhs, AnimationID _Rhs, AnimatorVariable&& _Variable);
		AnimationID lhs, rhs;
		AnimatorVariable variable;
	};

	
	class Animation;
	class Rect;
	class Animator final
	{
	public:
		Animator();
		~Animator();

		void AddAnimation(AnimationID id);
		void AddAnimation(Animation* pAni);
		void SetAnimation(AnimationID id);
		void Update(float elapsed);

		void SetFloat(const std::string& variable, float value);
		void SetBool(const std::string& variable, bool value);

		bool IsAtEnd() const;
		const Rect& GetCurrentAnimation() const;

	private:

		std::map<AnimationID, Animation* > m_pAnimations; //weak pointers
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
