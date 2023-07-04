#ifndef MENU_EVENT_HANDLER_H
#define MENU_EVENT_HANDLER_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game.h"
#include "../gframe/game_config.h"
#include "../gframe/server_lobby.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/CGUIFileSelectListBox/CGUIFileSelectListBox.h"
#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/ScreenReader/StringBuilder.h"
#include "../accessibility/ScreenReader/ScreenReader.h"
#include "../accessibility/ScreenReader/Messages/AccessibilityStringDictionary.h"
#include <IGUIWindow.h>
#include <IGUIEditBox.h>
#include <IGUIComboBox.h>
#include <IGUICheckBox.h>
#include <IGUITable.h>
#include <IGUIScrollBar.h>
#include <IrrlichtDevice.h>
#include <IGUITabControl.h>

#include "BaseMenu.h"

namespace ygo {
	class MenuEventHandler : public IEventHandler {
	public:
		static IEventHandler* getMenuHandler();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static IEventHandler* menuHandler;
		BaseMenu* activeMenu;
		int prev_operation;
		int prev_sel;
		int menuSelectCounter = 0;
		int subMenuSelectCounter = 0;
		int onlineMatchCounter = 0;
		int currentSelectedSubMenu = 0;
		int oldSelectedSubMenu = 0;
		bool typing = false;
		bool scrollSelected = false;
		MenuType::MenuList selectedMenu = MenuType::MenuList::MAIN_MENU;
		int currentMenu = MenuType::MenuList::MAIN_MENU;
		std::wstring oldMenu = gDataManager->GetAccessibilityString(328).data();
		std::vector<int> menu;
		std::vector<int> menuMain = { MenuType::MainMenu::MM_ONLINE_DUEL, MenuType::MainMenu::MM_SP_DUEL, MenuType::MainMenu::MM_PUZZLES, MenuType::MainMenu::MM_REPLAY, MenuType::MainMenu::MM_DECK_EDITOR, MenuType::MainMenu::MM_GAME_OPTIONS };
		std::vector<int> menuSinglePlayer = { MenuType::SinglePlayerMenu::SP_HOST, MenuType::SinglePlayerMenu::SP_PLAYER_NAME };
		std::vector<int> menuHostDuel = { MenuType::HostDuel::RULES_OK, MenuType::HostDuel::NUM_PLAYERS_T1, MenuType::HostDuel::NUM_PLAYERS_T2, MenuType::HostDuel::BEST_OF, MenuType::HostDuel::TIME_LIMIT, MenuType::HostDuel::STARTING_LP, MenuType::HostDuel::STARTING_HAND, MenuType::HostDuel::CARDS_DRAW, MenuType::HostDuel::CHECK_DECK, MenuType::HostDuel::SHUFFLE_DECK, MenuType::HostDuel::ROOM_NAME, MenuType::HostDuel::ROOM_PASSWORD };
		std::vector<int> menuRulesOk = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::SinglePlayerDuel::SP_AI_MENU };
		std::vector<int> menuRulesOkOnline = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::OnlineDuel::OD_DUEL_MODE, MenuType::OnlineDuel::OD_SPECTATE_MODE };
		std::vector<int> menuSelectAI = { MenuType::AIConfigMenu::AIC_OK, MenuType::AIConfigMenu::AIC_SELECT_DECK, MenuType::AIConfigMenu::AIC_ATR };
		std::vector<int> menuOnline = { MenuType::OnlineMenu::HOST, MenuType::OnlineMenu::REFRESH, MenuType::OnlineMenu::ROOMS, MenuType::OnlineMenu::SERVER, MenuType::OnlineMenu::PLAYER_NAME, MenuType::OnlineMenu::ALLOWED_CARDS, MenuType::OnlineMenu::FORBIDDEN_LIST, MenuType::OnlineMenu::LOCKED_ROOMS, MenuType::OnlineMenu::STARTED_ROOMS };
		std::vector<int> menuPassword = { MenuType::PasswordMenu::PASS_SET_PASSWORD, MenuType::PasswordMenu::PASS_OK, MenuType::PasswordMenu::PASS_CANCEL };
		std::vector<int> menuDeckEditor = { Accessibility::Dict::Menu::OK, Accessibility::Dict::Menu::CANCEL };
		std::vector<int> menuGameOptions = { MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS, MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME, MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC, MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME, MenuType::GameOptionsMenu::USE_MUD_KEYBOARD };
		std::vector<int> menuPuzzles = { 0 };
		void CheckMenu();
		void HostDuel();
		void DuelMenu();
		void SPDuel();
		void AIConfigMenu();
		void OnlineDuel();
		void PasswordMenu();
		void GameOptions();
		void ReadOnlineRoomFromList(irr::EKEY_CODE key);
		void ReadMenu(irr::EKEY_CODE key);
		void ReadSinglePlayerList();
		void ReadReplayList();
		void ReadMenuAndValue();
	};
}

#endif //MENU_EVENT_H
