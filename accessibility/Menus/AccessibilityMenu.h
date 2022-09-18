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
#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/ScreenReader/StringBuilder.h"
#include "../accessibility/ScreenReader/ScreenReader.h"
#include <IGUIWindow.h>
#include <IGUIEditBox.h>
#include <IGUIComboBox.h>
#include <IGUICheckBox.h>
#include <IGUITable.h>
#include <IGUIScrollBar.h>
#include <IrrlichtDevice.h>

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
		std::wstring currentMenu = L"Online Duel";
		std::wstring oldMenu = L"Online Duel";
		std::vector<std::wstring> menu;
		std::vector<std::wstring> menuMain = { L"Online Duel", L"Duel", L"Deck Editor", L"Game Options", L"Accessibility" };
		std::vector<std::wstring> menuSinglePlayer = { L"Host Duel", L"Player Name" };
		std::vector<std::wstring> menuHostDuel = { L"Rules ok", L"Num Players Team 1", L"Num Players Team 2", L"Best of", L"Time Limit", L"Starting LP", L"Starting Hand", L"Cards per Draw", L"Don't check deck", L"Don't shuffle deck", L"Room Name", L"Room Password" };
		std::vector<std::wstring> menuRulesOk = { L"Start Duel", L"Select Deck", L"Player Ready", L"Select AI" };
		std::vector<std::wstring> menuRulesOkOnline = { L"Start Duel", L"Select Deck", L"Player Ready", L"Enter Duel mode", L"Enter Spectate mode" };
		std::vector<std::wstring> menuSelectAI = { L"AI Ok", L"Select Deck", L"Always throw Rock" };
		std::vector<std::wstring> menuOnline = { L"Host", L"Refresh", L"Rooms", L"Server", L"Player Name", L"Allowed Cards", L"Forbidden List", L"Show Locked Rooms", L"Show Started Rooms" };
		std::vector<std::wstring> menuPassword = { L"Change Password", L"OK", L"Cancel" };
		std::vector<std::wstring> menuDeckEditor = { L"OK", L"Cancel" };
		std::vector<std::wstring> menuGameOptions = { L"Enable Sound Effects", L"Sound Effects Volume", L"Enable Music", L"Music Volume" };
		void CheckMenu();
		void MainMenu();
		void HostDuel();
		void DuelMenu();
		void SPDuel();
		void AIConfigMenu();
		void OnlineDuel();
		void PasswordMenu();
		void GameOptions();
	};	
}

#endif //MENU_EVENT_H
