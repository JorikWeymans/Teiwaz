#pragma once
#include <vector>
#ifdef EDITOR_MODE
#include "EWindow.h"
namespace tyr
{
	class GameContext;
	class ETabItem;
	class EWindowSouth final: public EWindow
	{
	public:
		explicit EWindowSouth(GameContext* pContext);
		~EWindowSouth();
		template <typename T>
		_NODISCARD	T* GetTabItem() const
		{
			for (auto* pT : m_pTabItems)
			{
				if (typeid(*pT) == typeid(T))
				{
					return static_cast<T*>(pT);
				}
			}
			return nullptr;
		}

		void Test();
	protected:
		void PreRender() override;
		void InternalRenderEditor() override;

	private:
		std::vector<ETabItem*> m_pTabItems;
	public:
		EWindowSouth(const EWindowSouth&) = delete;
		EWindowSouth(EWindowSouth&&) = delete;
		EWindowSouth& operator=(const EWindowSouth&) = delete;
		EWindowSouth& operator=(EWindowSouth&&) = delete;

	};


}

#endif
