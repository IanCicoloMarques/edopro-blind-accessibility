#ifndef PRE_DUEL_ONLINE_MENU_HANDLER_H
#define PRE_DUEL_ONLINE_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class PreDuelOnlineMenuHandler final : public BaseMenu {
	public:
		PreDuelOnlineMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_ONLINE_MENU, const std::vector<int>&
			                   selectedMenu = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::OnlineDuel::OD_DUEL_MODE, MenuType::OnlineDuel::OD_SPECTATE_MODE });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static PreDuelOnlineMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //PRE_DUEL_ONLINE_MENU_HANDLER_H
