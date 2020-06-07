#pragma once
#include <map>
#include <functional>
#include <set>

namespace tyr
{

	template <typename T>
	struct Var
	{
		T data;
	};

	struct Varfloat : Var<float> {};

	struct ValBool : Var<bool> {};
	
	struct Connection
	{
		AnimationID Lhs, Rhs;
		std::string VariableName;
		
		//float condition;

		std::function<bool(float)> floatTest;
		std::function<bool(bool)> boolTest;
	

		
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
