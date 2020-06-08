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

		void Menu();
		Animator* m_pAnimator;

		char m_TempConnectionName[30]{};
		char m_TempName[40]{};
		bool m_WindowIsOpen;
	};


}
#endif