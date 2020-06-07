#include "ETabItem.h"
#include <vector>
#ifdef EDITOR_MODE
namespace  tyr
{
	class GameContext;
	class EAnimation;
	class ETabAnimations final : public ETabItem
	{

	public:
		explicit ETabAnimations(GameContext* pContext);
		virtual ~ETabAnimations();

		void CreateTabItems() override;
	protected:

		void PreTabRender() override;
		void PostTabRender() override;
		void OnItemDoubleClick(TabItem& clickedItem) override;
	private:
		std::string m_SceneFolder;
		EAnimation* m_pEditorAni;
	public:
		ETabAnimations(const ETabAnimations&) = delete;
		ETabAnimations(ETabAnimations&&) = delete;
		ETabAnimations& operator=(const ETabAnimations&) = delete;
		ETabAnimations& operator=(ETabAnimations&&) = delete;
	};
}
#endif
