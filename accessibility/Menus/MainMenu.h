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
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static MainMenuHandler* menuHandler;
		int menuSelectCounter = 0;
		bool typing = false;
		int currentMenu = MenuType::MenuList::MAIN_MENU;
		std::wstring oldMenu = gDataManager->GetAccessibilityString(328).data();
		std::vector<int> menu;
		std::vector<int> menuMain = { MenuType::MainMenu::MM_ONLINE_DUEL, MenuType::MainMenu::MM_SP_DUEL, MenuType::MainMenu::MM_PUZZLES, MenuType::MainMenu::MM_REPLAY, MenuType::MainMenu::MM_DECK_EDITOR, MenuType::MainMenu::MM_GAME_OPTIONS };
		std::vector<int> menuGameOptions = { MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS, MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME, MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC, MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME, MenuType::GameOptionsMenu::USE_MUD_KEYBOARD };
		void ReadMenu(irr::EKEY_CODE key = irr::EKEY_CODE::KEY_UNKNOWN) override;
		void ReadReplayList() override;
		void ReadMenuAndValue() override;
	};
}

#endif //MAIN_MENU_HANDLER_H
