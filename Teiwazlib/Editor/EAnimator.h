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
		void RenderConnectionProperties(int selected);
		void OnSelectionChanged(int newSelected);
		
		Animator* m_pAnimator;

		char m_Temp[30]{};
		bool m_WindowIsOpen;
	};


}
#endif