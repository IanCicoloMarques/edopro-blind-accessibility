#ifndef CONFIGURATION_MENU_HANDLER_H
#define CONFIGURATION_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class ConfigurationMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> configurationMenu;
		ConfigurationMenuHandler(int activeMenu = MenuType::MenuList::SELECT_AI_MENU, const std::vector<int>& selectedMenu = configurationMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void ReadMenuAndValue() override;
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static ConfigurationMenuHandler* _menuHandler;
	};
}

#endif //CONFIGURATION_MENU_HANDLER_H
