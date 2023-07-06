#ifndef PRE_DUEL_MENU_HANDLER_H
#define PRE_DUEL_MENU_HANDLER_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game_config.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"

#include "BaseMenu.h"

namespace ygo {
	class PreDuelMenuHandler final : public BaseMenu {
	public:
		PreDuelMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_MENU, const std::vector<int>&
			                   selectedMenu = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::SinglePlayerDuel::SP_AI_MENU });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static PreDuelMenuHandler* menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //PRE_DUEL_MENU_HANDLER_H
