#ifndef MAIN_MENU_HANDLER_H
#define MAIN_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class MainMenuHandler : public BaseMenu {
	public:
		static std::vector<int> mainMenu;
		MainMenuHandler(const int activeMenu = MenuType::MenuList::MAIN_MENU, const std::vector<int>& selectedMenu = mainMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static MainMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
		void ReadReplayList();
	};
}

#endif //MAIN_MENU_HANDLER_H
