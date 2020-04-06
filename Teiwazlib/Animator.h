#pragma once
#include <map>

namespace tyr
{
	class Animation;
	class Rect;
	class Animator final
	{
	public:
		Animator();
		~Animator();

		void AddAnimation(const std::string& name, Animation* ani);
		void SetAnimation(const std::string& name);
		void Update(float elapsed);
		
		std::map<std::string, Animation*> m_pAnimations;
		const Rect& GetCurrentAnimation() const;
		Animation* m_pCurrent; //weak pointer
		
	public:
		Animator(const Animator&) = delete;
		Animator(Animator&&) = delete;
		Animator& operator=(const Animator&) = delete;
		Animator& operator=(Animator&&) = delete;
	};


}
#pragma once
