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
		int currentMenu = MenuType::MenuList::MAIN_MENU;
		std::vector<int> menu;
		std::vector<int> menuPassword = { MenuType::PasswordMenu::PASS_SET_PASSWORD, MenuType::PasswordMenu::PASS_OK, MenuType::PasswordMenu::PASS_CANCEL };
		void CheckMenu();
		void PasswordMenu();
		void ReadMenu(irr::EKEY_CODE key);
		void ReadReplayList();
		void ReadMenuAndValue();
	};
}

#endif //MENU_EVENT_H
