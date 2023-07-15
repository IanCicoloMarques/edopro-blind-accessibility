#include "OnlineModeMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	OnlineModeMenuHandler* OnlineModeMenuHandler::_menuHandler = nullptr;
	std::vector<int> OnlineModeMenuHandler::onlineModeMenu = {
		MenuType::OnlineMenu::HOST, MenuType::OnlineMenu::REFRESH, MenuType::OnlineMenu::ROOMS,
		MenuType::OnlineMenu::SERVER, MenuType::OnlineMenu::PLAYER_NAME, MenuType::OnlineMenu::ALLOWED_CARDS,
		MenuType::OnlineMenu::FORBIDDEN_LIST, MenuType::OnlineMenu::LOCKED_ROOMS, MenuType::OnlineMenu::STARTED_ROOMS
	};

	OnlineModeMenuHandler::OnlineModeMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* OnlineModeMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new OnlineModeMenuHandler();
		return _menuHandler;
	}

	bool OnlineModeMenuHandler::IsActive()
	{
		bool isActive = false;
		if (mainGame->ebStartLP->isTrulyVisible())
			isActive = true;
		return isActive;
	}

	static void CheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (chkbox->isTrulyVisible()) {
			if (chkbox->isChecked())
				gSoundManager->PlaySoundEffect(SoundManager::SFX::UNCONFIRM);
			else
				gSoundManager->PlaySoundEffect(SoundManager::SFX::CONFIRM);
			chkbox->setChecked(!chkbox->isChecked());
		}
	}

	void OnlineModeMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {

			case irr::KEY_KEY_I: {
					if (!event.KeyInput.PressedDown && mainGame->roomListTable->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						//ScreenReader::getReader()->textToSpeech(fmt::format(L"Player {}", mainGame->roomListTable->getCellData(onlineMatchCounter, 0)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(186).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 1)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(187).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 2)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(188).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 3)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(189).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 4)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(190).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 5)));
						ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(191).data(), mainGame->roomListTable->getCellText(_onlineMatchIndex, 6)));
					}
					break;
			}
			case irr::KEY_DOWN:
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->roomListTable->isTrulyVisible() && _currentMenu == MenuType::OnlineMenu::ROOMS)
						ReadOnlineRoomFromList(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					if (_selectedMenu != onlineModeMenu)
						_selectedMenu = onlineModeMenu;
					SetMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_activeMenu != _selectedMenu)
						SetMenu();
					if (_currentMenu == MenuType::OnlineMenu::HOST && mainGame->btnCreateHost2->isEnabled())
						ClickButton(mainGame->btnCreateHost2);
					else if (_currentMenu == MenuType::OnlineMenu::REFRESH && mainGame->btnLanRefresh2->isEnabled()) {
						_onlineMatchIndex = 0;
						ServerLobby::RefreshRooms();
					}
					else if (_currentMenu == MenuType::OnlineMenu::ROOMS && mainGame->btnJoinHost2->isEnabled())
						ClickButton(mainGame->btnJoinHost2);
					else if (_currentMenu == MenuType::OnlineMenu::SERVER && mainGame->serverChoice->isTrulyVisible())
					{
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(249).data(), mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected())));
						mainGame->env->setFocus(mainGame->serverChoice);
					}
					else if (_currentMenu == MenuType::OnlineMenu::PLAYER_NAME && mainGame->ebNickNameOnline->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(250).data());
							FocusTextBox(mainGame->ebNickNameOnline);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(251).data(), mainGame->ebNickNameOnline->getText()));
						}
					}
					else if (_currentMenu == MenuType::OnlineMenu::ALLOWED_CARDS && mainGame->cbFilterRule->isTrulyVisible()) {
						ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected())));
						mainGame->env->setFocus(mainGame->cbFilterRule);
					}
					else if (_currentMenu == MenuType::OnlineMenu::FORBIDDEN_LIST && mainGame->cbFilterBanlist->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->cbFilterBanlist);
						ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterBanlist->getItem(mainGame->cbFilterBanlist->getSelected())));
					}
					else if (_currentMenu == MenuType::OnlineMenu::LOCKED_ROOMS && mainGame->chkShowPassword->isTrulyVisible())
						CheckBox(mainGame->chkShowPassword);
					else if (_currentMenu == MenuType::OnlineMenu::STARTED_ROOMS && mainGame->chkShowActiveRooms->isTrulyVisible())
						CheckBox(mainGame->chkShowActiveRooms);
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnJoinCancel2->isTrulyVisible())
						ClickButton(mainGame->btnJoinCancel2);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void OnlineModeMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		const int id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
			case irr::gui::EGET_CHECKBOX_CHANGED: {
				switch (id) {
					case CHECK_SHOW_LOCKED_ROOMS: {
						std::wstring screenReaderString;
						if (mainGame->chkShowPassword->isChecked())
							screenReaderString = gDataManager->GetAccessibilityString(219).data();
						else
							screenReaderString = gDataManager->GetAccessibilityString(220).data();
						ScreenReader::getReader()->readScreen(screenReaderString);
						break;
					}
					case CHECK_SHOW_ACTIVE_ROOMS: {
						std::wstring screenReaderString;
						if (mainGame->chkShowActiveRooms->isChecked())
							screenReaderString = gDataManager->GetAccessibilityString(221).data();
						else
							screenReaderString = gDataManager->GetAccessibilityString(222).data();
						ScreenReader::getReader()->readScreen(screenReaderString);
						break;
					}
				}
			}
			case irr::gui::EGET_COMBO_BOX_CHANGED: {
				switch (id) {
					case SERVER_CHOICE: {
						const std::wstring nvdaString = fmt::format(L"{}", mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
						break;
					}
					case CB_FILTER_ALLOWED_CARDS: {
						const std::wstring nvdaString = fmt::format(L"{}", mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
						break;
					}
					case CB_FILTER_BANLIST: {
						const std::wstring nvdaString = fmt::format(L"{}", mainGame->cbFilterBanlist->getItem(mainGame->cbFilterBanlist->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
						break;
					}
				}
			}
		}
	}

	void OnlineModeMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::PlayerDuel::PD_START_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_START_DUEL).data();
			else if(_currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			else if(_currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data();
			else if(_currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_PLAYER_READY).data();
			else if(_currentMenu == MenuType::SinglePlayerDuel::SP_AI_MENU)
				menuValue = gDataManager->GetAccessibilityString(MenuType::SinglePlayerDuel::SP_AI_MENU).data();
			else if(_currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineDuel::OD_DUEL_MODE).data();
			else if(_currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineDuel::OD_SPECTATE_MODE).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void OnlineModeMenuHandler::ReadOnlineRoomFromList(irr::EKEY_CODE key)
	{
		if(key == irr::KEY_UP)
		{
			if (_onlineMatchIndex > 0)
				_onlineMatchIndex--;
		}
		else if(key == irr::KEY_DOWN)
		{
			if (_onlineMatchIndex < mainGame->roomListTable->getRowCount() - 1)
				_onlineMatchIndex++;
		}
		mainGame->roomListTable->setSelected(_onlineMatchIndex);
		std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(_onlineMatchIndex, 5));
		int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
		if (numPlayers > 1)
			ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(195).data(), numPlayers, mainGame->roomListTable->getCellText(_onlineMatchIndex, 5), mainGame->roomListTable->getCellText(_onlineMatchIndex, 6)));
		else
			ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(196).data(), numPlayers, mainGame->roomListTable->getCellText(_onlineMatchIndex, 5), mainGame->roomListTable->getCellText(_onlineMatchIndex, 6)));
	}
}
