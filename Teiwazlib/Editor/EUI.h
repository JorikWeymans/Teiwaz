#pragma once
#ifdef EDITOR_MODE
#include <vector>

namespace tyr
{
	class SceneManager;
	class GameContext;
	class EMenuBar;
	class EWindow;
	class EAnimation;
	class EAnimator;
	
	class EUI final
	{
	public:
		explicit EUI(GameContext* pContext);
		~EUI();


		void RenderEditor();

		_NODISCARD EAnimation* GetAnimationEditor() const noexcept { return m_pEAnimation; }
		_NODISCARD EAnimator* GetAnimatorEditor() const noexcept { return m_pEAnimator; }
		
		template<typename  T>
		_NODISCARD	T* GetWindow() const
		{
			for (auto* pW : m_pWindows)
			{
				if(typeid(*pW) == typeid(T))
				{
					return static_cast<T*>(pW);
				}
			}
			return nullptr;
		}
		
	private:
		GameContext* const m_pContext;
		EMenuBar* m_pMenu;
		std::vector<EWindow*> m_pWindows;
		EAnimation* m_pEAnimation;
		EAnimator* m_pEAnimator;
	public:
		EUI(const EUI&) = delete;
		EUI(EUI&&) = delete;
		EUI& operator=(const EUI&) = delete;
		EUI& operator=(EUI&&) = delete;
	};
}

#endif
