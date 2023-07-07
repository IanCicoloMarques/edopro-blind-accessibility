#ifndef MAIN_MENU_HANDLER_H
#define MAIN_MENU_HANDLER_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game_config.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"

#include "BaseMenu.h"

namespace ygo {
	class MainMenuHandler : public BaseMenu {
	public:
		MainMenuHandler(const int activeMenu = MenuType::MenuList::MAIN_MENU, const std::vector<int>& selectedMenu = { MenuType::MainMenu::MM_ONLINE_DUEL, MenuType::MainMenu::MM_SP_DUEL, MenuType::MainMenu::MM_PUZZLES, MenuType::MainMenu::MM_REPLAY, MenuType::MainMenu::MM_DECK_EDITOR, MenuType::MainMenu::MM_GAME_OPTIONS });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static MainMenuHandler* _menuHandler;
		std::vector<int> menuGameOptions = { MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS, MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME, MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC, MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME, MenuType::GameOptionsMenu::USE_MUD_KEYBOARD };
		void ReadMenuAndValue() override;
		void ReadReplayList();
	};
}

#endif //MAIN_MENU_HANDLER_H
