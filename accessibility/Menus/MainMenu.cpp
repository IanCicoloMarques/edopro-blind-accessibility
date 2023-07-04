#include "MainMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	IEventHandler* MenuEventHandler::menuHandler = nullptr;
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

	BaseMenu* MainMenuHandler::GetMenu()
	{
		if (menuHandler == nullptr)
			menuHandler = new MainMenuHandler();
		return menuHandler;
	}

	void MainMenuHandler::ReadMenu(irr::EKEY_CODE key)
	{
		typing = false;
		mainGame->env->removeFocus(mainGame->env->getFocus());
		if (menu != menuMain)
		{
			menu = menuMain;
			menuSelectCounter = 0;
		}
		if(key == irr::KEY_RIGHT)
		{
			menuSelectCounter++;
			if (menuSelectCounter >= menu.size())
				menuSelectCounter = 0;
		}
		else if(key == irr::KEY_LEFT)
		{
			menuSelectCounter--;
			if (menuSelectCounter < 0)
				menuSelectCounter = menu.size() - 1;
		}
		currentMenu = menu.at(menuSelectCounter);
		ReadMenuAndValue();
	};


	void MainMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(menu == menuMain)
		{
			if(currentMenu == MenuType::MainMenu::MM_ONLINE_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_ONLINE_DUEL).data();
			else if(currentMenu == MenuType::MainMenu::MM_SP_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_SP_DUEL).data();
			else if(currentMenu == MenuType::MainMenu::MM_PUZZLES)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_PUZZLES).data();
			else if(currentMenu == MenuType::MainMenu::MM_REPLAY)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_REPLAY).data();
			else if(currentMenu == MenuType::MainMenu::MM_DECK_EDITOR)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_DECK_EDITOR).data();
			else if(currentMenu == MenuType::MainMenu::MM_GAME_OPTIONS)
				menuValue = gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_GAME_OPTIONS).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void MainMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_B: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					ScreenReader::getReader()->readLastMessage();
				}
				break;
			}
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
					ReadMenu(event.KeyInput.Key);
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					mainGame->env->removeFocus(mainGame->env->getFocus());
				if (!event.KeyInput.PressedDown) {
					if (menu != menuMain)
						ReadMenu();
					if (currentMenu == MenuType::MainMenu::MM_ONLINE_DUEL && mainGame->btnOnlineMode->isEnabled()) {
						ClickButton(mainGame->btnOnlineMode);
					}
					else if (currentMenu == MenuType::MainMenu::MM_SP_DUEL && mainGame->btnLanMode->isEnabled()) {
						ClickButton(mainGame->btnLanMode);
					}
					else if (currentMenu == MenuType::MainMenu::MM_PUZZLES && mainGame->btnSingleMode->isEnabled()) {
						ClickButton(mainGame->btnSingleMode);
					}
					else if (currentMenu == MenuType::MainMenu::MM_REPLAY && mainGame->btnReplayMode->isEnabled()) {
						ClickButton(mainGame->btnReplayMode);
					}
					else if (currentMenu == MenuType::MainMenu::MM_DECK_EDITOR && mainGame->btnDeckEdit->isEnabled()) {
						ClickButton(mainGame->btnDeckEdit);
					}
					else if (currentMenu == MenuType::MainMenu::MM_GAME_OPTIONS && mainGame->wBtnSettings->isEnabled()) {
						ClickButton(mainGame->btnSettings);
						menu = menuGameOptions;
					}
					else if (currentMenu == MenuType::MainMenu::MM_ACCESSIBILITY_KEYS) {
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
					if (menu.empty())
						menu = menuMain;
					else
						currentMenu = menu.at(menuSelectCounter);
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
