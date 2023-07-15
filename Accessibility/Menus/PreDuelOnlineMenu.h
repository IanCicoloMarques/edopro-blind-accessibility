#ifndef PRE_DUEL_ONLINE_MENU_HANDLER_H
#define PRE_DUEL_ONLINE_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class PreDuelOnlineMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> preDuelOnlineMenu;
		PreDuelOnlineMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_ONLINE_MENU, const std::vector<int>& selectedMenu = preDuelOnlineMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static PreDuelOnlineMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //PRE_DUEL_ONLINE_MENU_HANDLER_H
