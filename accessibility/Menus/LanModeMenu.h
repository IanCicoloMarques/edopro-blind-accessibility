#ifndef LAN_MODE_MENU_HANDLER_H
#define LAN_MODE_MENU_HANDLER_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game_config.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"

#include "BaseMenu.h"

namespace ygo {
	class LanModeMenuHandler final : public BaseMenu {
	public:
		LanModeMenuHandler(const int activeMenu = MenuType::MenuList::LAN_MODE_MENU, const std::vector<int>&
			                   selectedMenu = { MenuType::SinglePlayerMenu::SP_HOST, MenuType::SinglePlayerMenu::SP_PLAYER_NAME });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static LanModeMenuHandler* menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //LAN_MODE_MENU_HANDLER_H
