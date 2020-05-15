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

	protected:

		void PreRender() override;
		void InternalRenderEditor() override;

	private:
		std::string m_SceneFolder;
		std::vector<TabItem> m_Files;
		TextureID m_Texture;

		EAnimation* m_pEditorAni;
	public:
		ETabAnimations(const ETabAnimations&) = delete;
		ETabAnimations(ETabAnimations&&) = delete;
		ETabAnimations& operator=(const ETabAnimations&) = delete;
		ETabAnimations& operator=(ETabAnimations&&) = delete;
	};
}
#endif
