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
		virtual ~ETabAnimations() = default;

		void CreateTabItems() override;
		void OpenAnimationEditorWindow(AnimationID id);
	protected:

		void PreTabRender() override;
		void PostTabRender() override;
		void OnItemDoubleClick(TabItem& clickedItem) override;
	private:
		std::string m_SceneFolder;
	public:
		ETabAnimations(const ETabAnimations&) = delete;
		ETabAnimations(ETabAnimations&&) = delete;
		ETabAnimations& operator=(const ETabAnimations&) = delete;
		ETabAnimations& operator=(ETabAnimations&&) = delete;
	};
}
#endif
