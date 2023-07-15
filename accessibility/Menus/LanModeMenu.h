#ifndef LAN_MODE_MENU_HANDLER_H
#define LAN_MODE_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class LanModeMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> lanModeMenu;
		LanModeMenuHandler(const int activeMenu = MenuType::MenuList::LAN_MODE_MENU, const std::vector<int>& selectedMenu = lanModeMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static LanModeMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //LAN_MODE_MENU_HANDLER_H
