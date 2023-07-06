#include "DuelRulesMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	IEventHandler* MenuEventHandler::menuHandler = nullptr;

	DuelRulesMenuHandler::DuelRulesMenuHandler(int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* DuelRulesMenuHandler::GetMenu()
	{
		if (menuHandler == nullptr)
			menuHandler = new DuelRulesMenuHandler();
		return menuHandler;
	}

	void DuelRulesMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_selectedMenu == _activeMenu)
		{
			if(_currentMenu == MenuType::HostDuel::RULES_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::HostDuel::RULES_OK).data();
			else if(_currentMenu == MenuType::HostDuel::NUM_PLAYERS_T1)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::NUM_PLAYERS_T1).data(), mainGame->ebTeam1->getText());
			else if(_currentMenu == MenuType::HostDuel::NUM_PLAYERS_T2)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::NUM_PLAYERS_T2).data(), mainGame->ebTeam2->getText());
			else if(_currentMenu == MenuType::HostDuel::BEST_OF)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::BEST_OF).data(), mainGame->ebBestOf->getText());
			else if(_currentMenu == MenuType::HostDuel::TIME_LIMIT)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::TIME_LIMIT).data(), mainGame->ebTimeLimit->getText());
			else if(_currentMenu == MenuType::HostDuel::STARTING_LP)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::STARTING_LP).data(), mainGame->ebStartLP->getText());
			else if(_currentMenu == MenuType::HostDuel::STARTING_HAND)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::STARTING_HAND).data(), mainGame->ebStartHand->getText());
			else if(_currentMenu == MenuType::HostDuel::CARDS_DRAW)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::CARDS_DRAW).data(), mainGame->ebDrawCount->getText());
			else if(_currentMenu == MenuType::HostDuel::CHECK_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::CHECK_DECK).data(), mainGame->chkNoCheckDeckContent->isChecked());
			else if(_currentMenu == MenuType::HostDuel::SHUFFLE_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::SHUFFLE_DECK).data(), mainGame->chkNoShuffleDeck->isChecked());
			else if(_currentMenu == MenuType::HostDuel::ROOM_NAME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::ROOM_NAME).data(), mainGame->ebHostNotes->getText());
			else if(_currentMenu == MenuType::HostDuel::ROOM_PASSWORD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::ROOM_PASSWORD).data(), mainGame->ebServerPass->getText());
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void DuelRulesMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_B: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					ScreenReader::getReader()->readLastMessage();
				}
				break;
			}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					SetMenu(event.KeyInput.Key);
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					mainGame->env->removeFocus(mainGame->env->getFocus());
				if (!event.KeyInput.PressedDown) {
					if (_selectedMenu != _activeMenu)
						SetMenu();
					if (_currentMenu == MenuType::SinglePlayerMenu::SP_HOST && mainGame->btnCreateHost->isEnabled()) {
						ClickButton(mainGame->btnCreateHost);
					}
					else if (_currentMenu == MenuType::SinglePlayerMenu::SP_PLAYER_NAME && mainGame->ebNickName->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(225).data()));
							FocusTextBox(mainGame->ebNickName);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(226).data(), mainGame->ebNickName->getText()));
						}
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
					if (_activeMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _activeMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void DuelRulesMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
}
