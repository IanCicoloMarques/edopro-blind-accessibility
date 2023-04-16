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

namespace ygo {
	class MenuEventHandler : public IEventHandler {
	public:
		static IEventHandler* getMenuHandler();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static IEventHandler* menuHandler;
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
		std::wstring currentMenu = gDataManager->GetAccessibilityString(328).data();
		int currentMenuEnum = MenuType::MenuList::MAIN_MENU;
		std::wstring oldMenu = gDataManager->GetAccessibilityString(328).data();
		std::vector<std::wstring> menu;
		std::vector<std::wstring> menuMain = { gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_ONLINE_DUEL).data(), gDataManager->GetAccessibilityString(329).data(), gDataManager->GetAccessibilityString(330).data(), gDataManager->GetAccessibilityString(331).data(), gDataManager->GetAccessibilityString(332).data(), gDataManager->GetAccessibilityString(333).data() };
		std::vector<int> menuMainEnums = { MenuType::MainMenu::MM_ONLINE_DUEL, gDataManager->GetAccessibilityString(329).data(), gDataManager->GetAccessibilityString(330).data(), gDataManager->GetAccessibilityString(331).data(), gDataManager->GetAccessibilityString(332).data(), gDataManager->GetAccessibilityString(333).data() };
		std::vector<std::wstring> menuSinglePlayer = { gDataManager->GetAccessibilityString(199).data(), gDataManager->GetAccessibilityString(335).data() };
		std::vector<int> menuSinglePlayerEnums = { MenuType::SinglePlayerMenu::SP_HOST, MenuType::SinglePlayerMenu::SP_PLAYER_NAME };
		std::vector<std::wstring> menuHostDuel = { gDataManager->GetAccessibilityString(336).data(), gDataManager->GetAccessibilityString(337).data(), gDataManager->GetAccessibilityString(338).data(), gDataManager->GetAccessibilityString(339).data(), gDataManager->GetAccessibilityString(340).data(), gDataManager->GetAccessibilityString(341).data(), gDataManager->GetAccessibilityString(342).data(), gDataManager->GetAccessibilityString(343).data(), gDataManager->GetAccessibilityString(344).data(), gDataManager->GetAccessibilityString(345).data(), gDataManager->GetAccessibilityString(346).data(), gDataManager->GetAccessibilityString(347).data() };
		std::vector<int> menuHostDuelEnums = { MenuType::HostDuel::RULES_OK, MenuType::HostDuel::NUM_PLAYERS_T1, MenuType::HostDuel::NUM_PLAYERS_T2, MenuType::HostDuel::BEST_OF, MenuType::HostDuel::TIME_LIMIT, MenuType::HostDuel::STARTING_LP, MenuType::HostDuel::STARTING_HAND, MenuType::HostDuel::CARDS_DRAW, MenuType::HostDuel::CHECK_DECK, MenuType::HostDuel::SHUFFLE_DECK, MenuType::HostDuel::ROOM_NAME, MenuType::HostDuel::ROOM_PASSWORD };
		std::vector<std::wstring> menuRulesOk = { gDataManager->GetAccessibilityString(348).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(350).data(), gDataManager->GetAccessibilityString(351).data() };
		std::vector<int> menuRulesOkEnums = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::SinglePlayerDuel::SP_AI_MENU };
		std::vector<std::wstring> menuRulesOkOnline = { MenuType::PlayerDuel::PD_START_DUEL, MenuType::PlayerDuel::PD_SELECT_DECK, MenuType::PlayerDuel::PD_PLAYER_READY, MenuType::OnlineDuel::OD_DUEL_MODE, MenuType::OnlineDuel::OD_SPECTATE_MODE };
		std::vector<int> menuRulesOkOnlineEnums = { gDataManager->GetAccessibilityString(348).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(350).data(), gDataManager->GetAccessibilityString(352).data(), gDataManager->GetAccessibilityString(353).data() };
		std::vector<std::wstring> menuSelectAI = { gDataManager->GetAccessibilityString(354).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(355).data() };
		std::vector<int> menuSelectAIEnums = { MenuType::AIConfigMenu::AIC_OK, MenuType::AIConfigMenu::AIC_SELECT_DECK, MenuType::AIConfigMenu::AIC_ATR };
		std::vector<std::wstring> menuOnline = { gDataManager->GetAccessibilityString(203).data(), gDataManager->GetAccessibilityString(356).data(), gDataManager->GetAccessibilityString(194).data(), gDataManager->GetAccessibilityString(358).data(), gDataManager->GetAccessibilityString(335).data(), gDataManager->GetAccessibilityString(359).data(), gDataManager->GetAccessibilityString(360).data(), gDataManager->GetAccessibilityString(361).data(), gDataManager->GetAccessibilityString(362).data() };
		std::vector<int> menuOnlineEnums = { MenuType::OnlineMenu::HOST, MenuType::OnlineMenu::REFRESH, MenuType::OnlineMenu::ROOMS, MenuType::OnlineMenu::SERVER, MenuType::OnlineMenu::PLAYER_NAME, MenuType::OnlineMenu::ALLOWED_CARDS, MenuType::OnlineMenu::FORBIDDEN_LIST, MenuType::OnlineMenu::LOCKED_ROOMS, MenuType::OnlineMenu::STARTED_ROOMS };
		std::vector<std::wstring> menuPassword = { gDataManager->GetAccessibilityString(363).data(), gDataManager->GetAccessibilityString(364).data(), gDataManager->GetAccessibilityString(365).data() };
		std::vector<int> menuPasswordEnums = { MenuType::PasswordMenu::PASS_SET_PASSWORD, MenuType::PasswordMenu::PASS_OK, MenuType::PasswordMenu::PASS_CANCEL };
		std::vector<std::wstring> menuDeckEditor = { gDataManager->GetAccessibilityString(364).data(), gDataManager->GetAccessibilityString(365).data() };
		std::vector<int> menuDeckEditorEnums = { Accessibility::Dict::Menu::OK, Accessibility::Dict::Menu::CANCEL };
		std::vector<std::wstring> menuGameOptions = { gDataManager->GetAccessibilityString(366).data(), gDataManager->GetAccessibilityString(367).data(), gDataManager->GetAccessibilityString(368).data(), gDataManager->GetAccessibilityString(369).data() };
		std::vector<int> menuGameOptionsEnums = { MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS, MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME, MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC, MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME };
		std::vector<std::wstring> menuPuzzles = { L"" };
		void CheckMenu();
		void MainMenu();
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
