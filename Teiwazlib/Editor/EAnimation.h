#pragma once
namespace tyr
{
	class GameContext;
	class Texture;
	class EAnimation final
	{
	public:
		explicit EAnimation(GameContext* pContext);
		~EAnimation() = default;

		void RenderEditor();
	private:
		GameContext* m_pContext;
		Texture* m_pTexture;
	public:
		EAnimation(const EAnimation&) = delete;
		EAnimation(EAnimation&&) = delete;
		EAnimation& operator=(const EAnimation&) = delete;
		EAnimation& operator=(EAnimation&&) = delete;

		
	};
}
