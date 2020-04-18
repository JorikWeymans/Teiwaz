#include "ETabItem.h"
#include <vector>
#ifdef USE_IM_GUI
namespace  tyr
{
	class GameContext;
	class ETabAnimations final : public ETabItem
	{
	private:
		struct AnimationItem
		{
			explicit AnimationItem(const std::string& _path, const std::string& _name)
				: path(_path), name(_name), isHovered(false) {}
			std::string path;
			std::string name;
			bool isHovered;
		};
	public:
		explicit ETabAnimations(GameContext* pContext);
		virtual ~ETabAnimations() = default;

	protected:

		void PreRender() override;
		void InternalRenderEditor() override;

	private:
		std::string m_SceneFolder;
		std::vector<AnimationItem> m_Files;
		TextureID m_Texture;
	public:
		ETabAnimations(const ETabAnimations&) = delete;
		ETabAnimations(ETabAnimations&&) = delete;
		ETabAnimations& operator=(const ETabAnimations&) = delete;
		ETabAnimations& operator=(ETabAnimations&&) = delete;
	};
}
#endif
