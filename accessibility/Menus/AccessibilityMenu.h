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
		std::wstring oldMenu = gDataManager->GetAccessibilityString(328).data();
		std::vector<std::wstring> menu;
		std::vector<std::wstring> menuMain = { gDataManager->GetAccessibilityString(328).data(), gDataManager->GetAccessibilityString(329).data(), gDataManager->GetAccessibilityString(330).data(), gDataManager->GetAccessibilityString(331).data(), gDataManager->GetAccessibilityString(332).data(), gDataManager->GetAccessibilityString(333).data() };
		std::vector<std::wstring> menuSinglePlayer = { gDataManager->GetAccessibilityString(334).data(), gDataManager->GetAccessibilityString(335).data() };
		std::vector<std::wstring> menuHostDuel = { gDataManager->GetAccessibilityString(336).data(), gDataManager->GetAccessibilityString(337).data(), gDataManager->GetAccessibilityString(338).data(), gDataManager->GetAccessibilityString(339).data(), gDataManager->GetAccessibilityString(340).data(), gDataManager->GetAccessibilityString(341).data(), gDataManager->GetAccessibilityString(342).data(), gDataManager->GetAccessibilityString(343).data(), gDataManager->GetAccessibilityString(344).data(), gDataManager->GetAccessibilityString(345).data(), gDataManager->GetAccessibilityString(346).data(), gDataManager->GetAccessibilityString(347).data() };
		std::vector<std::wstring> menuRulesOk = { gDataManager->GetAccessibilityString(348).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(350).data(), gDataManager->GetAccessibilityString(351).data() };
		std::vector<std::wstring> menuRulesOkOnline = { gDataManager->GetAccessibilityString(348).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(350).data(), gDataManager->GetAccessibilityString(352).data(), gDataManager->GetAccessibilityString(353).data() };
		std::vector<std::wstring> menuSelectAI = { gDataManager->GetAccessibilityString(354).data(), gDataManager->GetAccessibilityString(349).data(), gDataManager->GetAccessibilityString(355).data() };
		std::vector<std::wstring> menuOnline = { gDataManager->GetAccessibilityString(203).data(), gDataManager->GetAccessibilityString(356).data(), gDataManager->GetAccessibilityString(357).data(), gDataManager->GetAccessibilityString(358).data(), gDataManager->GetAccessibilityString(335).data(), gDataManager->GetAccessibilityString(359).data(), gDataManager->GetAccessibilityString(360).data(), gDataManager->GetAccessibilityString(361).data(), gDataManager->GetAccessibilityString(362).data() };
		std::vector<std::wstring> menuPassword = { gDataManager->GetAccessibilityString(363).data(), gDataManager->GetAccessibilityString(364).data(), gDataManager->GetAccessibilityString(365).data() };
		std::vector<std::wstring> menuDeckEditor = { gDataManager->GetAccessibilityString(364).data(), gDataManager->GetAccessibilityString(365).data() };
		std::vector<std::wstring> menuGameOptions = { gDataManager->GetAccessibilityString(366).data(), gDataManager->GetAccessibilityString(367).data(), gDataManager->GetAccessibilityString(368).data(), gDataManager->GetAccessibilityString(369).data() };
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
	};	
}

#endif //MENU_EVENT_H
