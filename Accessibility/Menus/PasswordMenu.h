#ifndef PASSWORD_MENU_HANDLER_H
#define PASSWORD_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class PasswordMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> passwordMenu;
		PasswordMenuHandler(int activeMenu = MenuType::MenuList::SELECT_AI_MENU, const std::vector<int>& selectedMenu = passwordMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static PasswordMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //PASSWORD_MENU_HANDLER_H
