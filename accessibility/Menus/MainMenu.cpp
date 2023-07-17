#include "MainMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	MainMenuHandler* MainMenuHandler::_menuHandler = nullptr;
	std::vector<int> MainMenuHandler::mainMenu = { MenuType::MainMenu::MM_ONLINE_DUEL, MenuType::MainMenu::MM_SP_DUEL,
		MenuType::MainMenu::MM_PUZZLES, MenuType::MainMenu::MM_REPLAY,
		MenuType::MainMenu::MM_DECK_EDITOR, MenuType::MainMenu::MM_GAME_OPTIONS
	};

	static inline void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
		irr::SEvent event;
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		ygo::mainGame->device->postEventFromUser(event);
	}

	static inline void ClickButton(irr::gui::IGUIElement* btn) {
		TriggerEvent(btn, irr::gui::EGET_BUTTON_CLICKED);
	}

	MainMenuHandler::MainMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* MainMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new MainMenuHandler();
		return _menuHandler;
	}

	bool MainMenuHandler::IsActive()
	{
		bool isActive = false;
		if (mainGame->btnOnlineMode->isEnabled() && mainGame->btnOnlineMode->isTrulyVisible())
			isActive = true;
		else if(mainGame->btnReplayCancel->isEnabled() && mainGame->btnReplayCancel->isTrulyVisible())
			isActive = true;
		return isActive;
	}

	void MainMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_selectedMenu == _activeMenu)
		{
			if(_currentMenu == MenuType::MainMenu::MM_ONLINE_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_ONLINE_DUEL).data();
			else if(_currentMenu == MenuType::MainMenu::MM_SP_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_SP_DUEL).data();
			else if(_currentMenu == MenuType::MainMenu::MM_PUZZLES)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_PUZZLES).data();
			else if(_currentMenu == MenuType::MainMenu::MM_REPLAY)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_REPLAY).data();
			else if(_currentMenu == MenuType::MainMenu::MM_DECK_EDITOR)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_DECK_EDITOR).data();
			else if(_currentMenu == MenuType::MainMenu::MM_GAME_OPTIONS)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_GAME_OPTIONS).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void MainMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_UP:
			case irr::KEY_DOWN: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->lstReplayList->isTrulyVisible())
						ReadReplayList();
				}
				break;
			}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					if (_selectedMenu != mainMenu)
						_selectedMenu = mainMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_selectedMenu != _activeMenu)
						SetSelectedMenu();
					if (_currentMenu == MenuType::MainMenu::MM_ONLINE_DUEL && mainGame->btnOnlineMode->isEnabled()) {
						ClickButton(mainGame->btnOnlineMode);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_SP_DUEL && mainGame->btnLanMode->isEnabled()) {
						ClickButton(mainGame->btnLanMode);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_PUZZLES && mainGame->btnSingleMode->isEnabled()) {
						ClickButton(mainGame->btnSingleMode);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_REPLAY && mainGame->btnReplayMode->isEnabled()) {
						ClickButton(mainGame->btnReplayMode);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_DECK_EDITOR && mainGame->btnDeckEdit->isEnabled()) {
						ClickButton(mainGame->btnDeckEdit);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_GAME_OPTIONS && mainGame->wBtnSettings->isEnabled()) {
						ClickButton(mainGame->btnSettings);
					}
					else if (_currentMenu == MenuType::MainMenu::MM_ACCESSIBILITY_KEYS) {
						ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage());
					}
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->gSettings.window->isTrulyVisible())
						mainGame->HideElement(mainGame->gSettings.window);
					else if (mainGame->btnModeExit->isTrulyVisible())
						ClickButton(mainGame->btnModeExit);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void MainMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void MainMenuHandler::ReadReplayList()
	{
		mainGame->env->setFocus(mainGame->lstReplayList);
		irr::s32 listItem = mainGame->lstReplayList->getSelected();
		if (listItem == -1) {
			listItem = 0;
			mainGame->lstReplayList->setSelected(mainGame->lstReplayList->getListItem(listItem));
		}
		ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstReplayList->getListItem(listItem)));
	};
}
