#pragma once
#ifdef EDITOR_MODE
namespace tyr
{
	class Animator;

	class EAnimator final
	{
	public:
		explicit EAnimator();
		~EAnimator();

		void OpenAnimatorEditorWindow(Animator* pAnimator);
		void RenderEditor();
	private:
		Animator* m_pAnimator;
		bool m_WindowIsOpen;
	};


}
#endif