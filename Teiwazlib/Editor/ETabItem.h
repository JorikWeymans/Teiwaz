#pragma once
#include <vector>
#ifdef EDITOR_MODE
namespace tyr
{
	struct TabItem
	{
		explicit TabItem(const std::string& _path, const std::string& _name)
			: path(_path), name(_name), isHovered(false) {}
		std::string path;
		std::string name;
		bool isHovered;
	};
}

namespace  tyr
{
	class GameContext;



	
	class ETabItem
	{
	public:
		explicit ETabItem(const char* name, GameContext* pContext, TextureID textureID);
		virtual ~ETabItem() = default;
		void RenderEditor();
		virtual void CreateTabItems() = 0;
	protected:

		virtual void PreTabRender() = 0;
		virtual void PostTabRender() = 0;
		virtual void OnItemDoubleClick(TabItem& clickedItem) = 0;
		
		const char* m_Name;
		GameContext* const m_pContext; //Weak ptr
		std::vector<TabItem> m_TabItems;
		TextureID m_TextureID;

		


	private:
		void RenderTabItems();

	public:
		ETabItem(const ETabItem&) = delete;
		ETabItem(ETabItem&&) = delete;
		ETabItem& operator=(const ETabItem&) = delete;
		ETabItem& operator=(ETabItem&&) = delete;
	};
}
#endif
