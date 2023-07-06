#ifndef DUEL_RULES_MENU_HANDLER_H
#define DUEL_RULES_MENU_HANDLER_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game_config.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"

#include "BaseMenu.h"

namespace ygo {
	class DuelRulesMenuHandler final : public BaseMenu {
	public:
		DuelRulesMenuHandler(int activeMenu = MenuType::MenuList::DUEL_RULES_MENU, const std::vector<int>& selectedMenu = {
			MenuType::HostDuel::RULES_OK, MenuType::HostDuel::NUM_PLAYERS_T1, MenuType::HostDuel::NUM_PLAYERS_T2,
			MenuType::HostDuel::BEST_OF, MenuType::HostDuel::TIME_LIMIT, MenuType::HostDuel::STARTING_LP,
			MenuType::HostDuel::STARTING_HAND, MenuType::HostDuel::CARDS_DRAW, MenuType::HostDuel::CHECK_DECK,
			MenuType::HostDuel::SHUFFLE_DECK, MenuType::HostDuel::ROOM_NAME, MenuType::HostDuel::ROOM_PASSWORD
		});
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static DuelRulesMenuHandler* menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //DUEL_RULES_MENU_HANDLER_H
