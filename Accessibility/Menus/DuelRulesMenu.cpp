#include "DuelRulesMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	DuelRulesMenuHandler* DuelRulesMenuHandler::_menuHandler = nullptr;

	DuelRulesMenuHandler::DuelRulesMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	static void CheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (chkbox->isTrulyVisible()) {
			if (chkbox->isChecked())
				gSoundManager->PlaySoundEffect(SoundManager::SFX::UNCONFIRM);
			else
				gSoundManager->PlaySoundEffect(SoundManager::SFX::CONFIRM);
			chkbox->setChecked(!chkbox->isChecked());
		}
	}

	BaseMenu* DuelRulesMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new DuelRulesMenuHandler();
		return _menuHandler;
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
					if (_currentMenu == MenuType::HostDuel::RULES_OK && mainGame->btnHostConfirm->isEnabled())
						ClickButton(mainGame->btnHostConfirm);
					else if (_currentMenu == MenuType::HostDuel::NUM_PLAYERS_T1 && mainGame->ebTeam1->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(231).data()).c_str());
							FocusTextBox(mainGame->ebTeam1);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(232).data(), mainGame->ebTeam1->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::NUM_PLAYERS_T2 && mainGame->ebTeam2->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(233).data()).c_str());
							FocusTextBox(mainGame->ebTeam2);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(234).data(), mainGame->ebTeam2->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::BEST_OF && mainGame->ebBestOf->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(235).data()).c_str());
							FocusTextBox(mainGame->ebBestOf);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(236).data(), mainGame->ebBestOf->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::TIME_LIMIT && mainGame->ebTimeLimit->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(237).data()).c_str());
							FocusTextBox(mainGame->ebTimeLimit);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(238).data(), mainGame->ebTimeLimit->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::STARTING_LP && mainGame->ebStartLP->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(239).data());
							FocusTextBox(mainGame->ebStartLP);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(240).data(), mainGame->ebStartLP->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::STARTING_HAND && mainGame->ebStartHand->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(241).data());
							FocusTextBox(mainGame->ebStartHand);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(242).data(), mainGame->ebStartHand->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::CARDS_DRAW && mainGame->ebDrawCount->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(243).data());
							FocusTextBox(mainGame->ebDrawCount);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(244).data(), mainGame->ebDrawCount->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::CHECK_DECK && mainGame->chkNoCheckDeckContent->isTrulyVisible()) {
						CheckBox(mainGame->chkNoCheckDeckContent);
						CheckBox(mainGame->chkNoCheckDeckSize);
					}
					else if (_currentMenu == MenuType::HostDuel::SHUFFLE_DECK && mainGame->chkNoShuffleDeck->isTrulyVisible())
						CheckBox(mainGame->chkNoShuffleDeck);
					else if (_currentMenu == MenuType::HostDuel::ROOM_NAME && mainGame->ebHostNotes->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(245).data());
							FocusTextBox(mainGame->ebHostNotes);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(246).data(), mainGame->ebHostNotes->getText()));
						}
					}
					else if (_currentMenu == MenuType::HostDuel::ROOM_PASSWORD && mainGame->ebServerPass->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(247).data());
							FocusTextBox(mainGame->ebServerPass);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(248).data(), mainGame->ebServerPass->getText()));
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
