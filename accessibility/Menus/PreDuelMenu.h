#ifndef PRE_DUEL_MENU_HANDLER_H
#define PRE_DUEL_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class PreDuelMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> preDuelMenu;
		PreDuelMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_MENU, const std::vector<int>&
			                   selectedMenu = preDuelMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static PreDuelMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //PRE_DUEL_MENU_HANDLER_H
