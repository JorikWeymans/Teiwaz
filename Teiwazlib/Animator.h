#pragma once
#include <vector>

namespace tyr
{
	class Animation;
	class Rect;
	class Connection;
	class Animator final
	{
	public:
		~Animator();

		void SetAnimation(AnimationID id);
		void Update(float elapsed);

		void SetFloat(const std::string& variable, float value);
		void SetBool(const std::string& variable, bool value);

		bool IsAtEnd() const;
		const Rect& GetCurrentAnimation() const;

		static Animator* Create(const std::string& path);

		const std::string& GetName() const noexcept { return m_Name; }
#ifdef EDITOR_MODE
		void Save();
#endif
	private:
		Animator();
		
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
