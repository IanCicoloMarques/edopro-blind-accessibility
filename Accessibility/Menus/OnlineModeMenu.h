#ifndef ONLINE_MODE_MENU_HANDLER_H
#define ONLINE_MODE_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class OnlineModeMenuHandler final : public BaseMenu {
	public:
		OnlineModeMenuHandler(int activeMenu = MenuType::MenuList::ONLINE_MODE_MENU, const std::vector<int>&
			                   selectedMenu = { MenuType::OnlineMenu::HOST, MenuType::OnlineMenu::REFRESH, MenuType::OnlineMenu::ROOMS, MenuType::OnlineMenu::SERVER, MenuType::OnlineMenu::PLAYER_NAME, MenuType::OnlineMenu::ALLOWED_CARDS, MenuType::OnlineMenu::FORBIDDEN_LIST, MenuType::OnlineMenu::LOCKED_ROOMS, MenuType::OnlineMenu::STARTED_ROOMS });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		void ReadMenuAndValue() override;
		static OnlineModeMenuHandler* _menuHandler;
		int _onlineMatchCounter = 0;
	};
}

#endif //ONLINE_MODE_MENU_HANDLER_H
