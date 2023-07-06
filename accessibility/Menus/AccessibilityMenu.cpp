#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

#include "LanModeMenu.h"
#include "MainMenu.h"

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

	static inline void CheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (chkbox->isTrulyVisible()) {
			if (chkbox->isChecked())
				gSoundManager->PlaySoundEffect(SoundManager::SFX::UNCONFIRM);
			else
				gSoundManager->PlaySoundEffect(SoundManager::SFX::CONFIRM);
			chkbox->setChecked(!chkbox->isChecked());
		}
	}

	static inline void FocusTextBox(irr::gui::IGUIEditBox* editBox) {
		if (editBox->isTrulyVisible()) {
			editBox->setText(L"");
			mainGame->env->setFocus(editBox);
		}
	}

	IEventHandler* MenuEventHandler::getMenuHandler()
	{
		if (menuHandler == nullptr)
			menuHandler = new MenuEventHandler();
		return menuHandler;
	}

	void MenuEventHandler::ReadOnlineRoomFromList(irr::EKEY_CODE key)
	{
		if(key == irr::KEY_UP)
		{
			if (onlineMatchCounter > 0)
				onlineMatchCounter--;
		}
		else if(key == irr::KEY_DOWN)
		{
			if (onlineMatchCounter < mainGame->roomListTable->getRowCount() - 1)
				onlineMatchCounter++;
		}
		mainGame->roomListTable->setSelected(onlineMatchCounter);
		std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(onlineMatchCounter, 5));
		int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
		if (numPlayers > 1)
			ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(195).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
		else
			ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(196).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
	}

	void MenuEventHandler::ReadSinglePlayerList()
	{
		mainGame->env->setFocus(mainGame->lstSinglePlayList);
		irr::s32 listItem = mainGame->lstSinglePlayList->getSelected();
		if (listItem == -1) {
			listItem = 0;
			mainGame->lstSinglePlayList->setSelected(mainGame->lstSinglePlayList->getListItem(listItem));
		}
		ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstSinglePlayList->getListItem(listItem)));
	}

	void MenuEventHandler::ReadReplayList()
	{
		mainGame->env->setFocus(mainGame->lstReplayList);
		irr::s32 listItem = mainGame->lstReplayList->getSelected();
		if (listItem == -1) {
			listItem = 0;
			mainGame->lstReplayList->setSelected(mainGame->lstReplayList->getListItem(listItem));
		}
		ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstReplayList->getListItem(listItem)));
	};

	void MenuEventHandler::ReadMenuAndValue()
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
		else if(menu == menuSinglePlayer)
		{
			if(currentMenu == MenuType::SinglePlayerMenu::SP_HOST)
				menuValue = gDataManager->GetAccessibilityString(MenuType::SinglePlayerMenu::SP_HOST).data();
			else if(currentMenu == MenuType::SinglePlayerMenu::SP_PLAYER_NAME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::SinglePlayerMenu::SP_PLAYER_NAME).data(), mainGame->ebNickName->getText());
		}
		else if(menu == menuHostDuel)
		{
			if(currentMenu == MenuType::HostDuel::RULES_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::HostDuel::RULES_OK).data();
			else if(currentMenu == MenuType::HostDuel::NUM_PLAYERS_T1)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::NUM_PLAYERS_T1).data(), mainGame->ebTeam1->getText());
			else if(currentMenu == MenuType::HostDuel::NUM_PLAYERS_T2)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::NUM_PLAYERS_T2).data(), mainGame->ebTeam2->getText());
			else if(currentMenu == MenuType::HostDuel::BEST_OF)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::BEST_OF).data(), mainGame->ebBestOf->getText());
			else if(currentMenu == MenuType::HostDuel::TIME_LIMIT)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::TIME_LIMIT).data(), mainGame->ebTimeLimit->getText());
			else if(currentMenu == MenuType::HostDuel::STARTING_LP)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::STARTING_LP).data(), mainGame->ebStartLP->getText());
			else if(currentMenu == MenuType::HostDuel::STARTING_HAND)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::STARTING_HAND).data(), mainGame->ebStartHand->getText());
			else if(currentMenu == MenuType::HostDuel::CARDS_DRAW)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::CARDS_DRAW).data(), mainGame->ebDrawCount->getText());
			else if(currentMenu == MenuType::HostDuel::CHECK_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::CHECK_DECK).data(), mainGame->chkNoCheckDeckContent->isChecked());
			else if(currentMenu == MenuType::HostDuel::SHUFFLE_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::SHUFFLE_DECK).data(), mainGame->chkNoShuffleDeck->isChecked());
			else if(currentMenu == MenuType::HostDuel::ROOM_NAME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::ROOM_NAME).data(), mainGame->ebHostNotes->getText());
			else if(currentMenu == MenuType::HostDuel::ROOM_PASSWORD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::HostDuel::ROOM_PASSWORD).data(), mainGame->ebServerPass->getText());
		}
		else if(menu == menuRulesOk)
		{
			if(currentMenu == MenuType::PlayerDuel::PD_START_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_START_DUEL).data();
			else if(currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			else if(currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data();
			else if(currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY)
					menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_PLAYER_READY).data();
			else if(currentMenu == MenuType::SinglePlayerDuel::SP_AI_MENU)
					menuValue = gDataManager->GetAccessibilityString(MenuType::SinglePlayerDuel::SP_AI_MENU).data();
		}
		else if(menu == menuSelectAI)
		{
			if(currentMenu == MenuType::AIConfigMenu::AIC_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_OK).data();
			else if(currentMenu == MenuType::AIConfigMenu::AIC_SELECT_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_SELECT_DECK).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
			else if(currentMenu == MenuType::AIConfigMenu::AIC_ATR)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_ATR).data(), mainGame->gBot.chkThrowRock->isChecked());
		}
		else if(menu == menuOnline)
		{
			if(currentMenu == MenuType::OnlineMenu::HOST)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineMenu::HOST).data();
			else if(currentMenu == MenuType::OnlineMenu::REFRESH)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineMenu::REFRESH).data();
			else if(currentMenu == MenuType::OnlineMenu::ROOMS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::ROOMS_LIST).data(), mainGame->roomListTable->getRowCount());
			else if(currentMenu == MenuType::OnlineMenu::SERVER)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::SERVER).data(), mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected()));
			else if(currentMenu == MenuType::OnlineMenu::PLAYER_NAME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::PLAYER_NAME).data(), mainGame->ebNickNameOnline->getText());
			else if(currentMenu == MenuType::OnlineMenu::ALLOWED_CARDS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::ALLOWED_CARDS).data(), mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected()));
			else if(currentMenu == MenuType::OnlineMenu::FORBIDDEN_LIST)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::FORBIDDEN_LIST).data(), mainGame->cbFilterBanlist->getItem(mainGame->cbFilterRule->getSelected()));
			else if(currentMenu == MenuType::OnlineMenu::LOCKED_ROOMS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::LOCKED_ROOMS).data(), mainGame->chkShowPassword->isChecked());
			else if(currentMenu == MenuType::OnlineMenu::STARTED_ROOMS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::OnlineMenu::STARTED_ROOMS).data(), mainGame->chkShowActiveRooms->isChecked());
		}
		else if(menu == menuPassword)
		{
			if(currentMenu == MenuType::PasswordMenu::PASS_SET_PASSWORD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_SET_PASSWORD).data(), mainGame->ebRPName->getText());
			else if(currentMenu == MenuType::PasswordMenu::PASS_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_OK).data();
			else if(currentMenu == MenuType::PasswordMenu::PASS_CANCEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_CANCEL).data();
		}
		else if(menu == menuDeckEditor)
		{
			if(currentMenu == Accessibility::Dict::Menu::OK)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::OK).data();
			else if(currentMenu == Accessibility::Dict::Menu::CANCEL)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::CANCEL).data();
		}
		else if(menu == menuGameOptions)
		{
			if(currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS).data(), mainGame->gSettings.chkEnableSound->isChecked());
			else if(currentMenu == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME).data(), gGameConfig->soundVolume);
			else if(currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC).data(), mainGame->gSettings.chkEnableMusic->isChecked());
			else if(currentMenu == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME).data(), gGameConfig->musicVolume);
			else if(currentMenu == MenuType::GameOptionsMenu::USE_MUD_KEYBOARD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::USE_MUD_KEYBOARD).data(), mainGame->gSettings.chkUseMudKeyboard->isChecked());
		}
		else if(menu == menuRulesOkOnline)
		{
			if(currentMenu == MenuType::PlayerDuel::PD_START_DUEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_START_DUEL).data();
			else if(currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			else if(currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_SELECT_DECK).data();
			else if(currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PlayerDuel::PD_PLAYER_READY).data();
			else if(currentMenu == MenuType::SinglePlayerDuel::SP_AI_MENU)
				menuValue = gDataManager->GetAccessibilityString(MenuType::SinglePlayerDuel::SP_AI_MENU).data();
			else if(currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineDuel::OD_DUEL_MODE).data();
			else if(currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::OnlineDuel::OD_SPECTATE_MODE).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void MenuEventHandler::ReadMenu(irr::EKEY_CODE ekeyCode)
	{
		if (!scrollSelected && activeMenu != nullptr) {
			activeMenu->SetMenu(ekeyCode);
		}
	};

	void MenuEventHandler::KeyInputEvent(const irr::SEvent& event)
	{
		CheckMenu();
		if(activeMenu != nullptr)
			activeMenu->KeyInputEvent(event);
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_D: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepStart->isEnabled()) {
						ClickButton(mainGame->btnHostPrepStart);
					}
					else if (!mainGame->wSinglePlay->isTrulyVisible()) {
						ClickButton(mainGame->btnLanMode);
					}
					if (mainGame->btnCreateHost->isTrulyVisible()) {
						ClickButton(mainGame->btnCreateHost);
					}
					else if (mainGame->btnHostConfirm->isTrulyVisible()) {
						ClickButton(mainGame->btnHostConfirm);
					}
					else if (mainGame->btnHostPrepReady->isTrulyVisible()) {
						ClickButton(mainGame->btnHostPrepReady);
					}
					else if (mainGame->gBot.btnAdd->isTrulyVisible()) {
						ClickButton(mainGame->gBot.btnAdd);
					}
					else if (mainGame->btnHostPrepWindBot->isTrulyVisible()) {
						ClickButton(mainGame->btnHostPrepWindBot);
					}
				}
				break;
			}
			case irr::KEY_KEY_G: {
				if (!event.KeyInput.PressedDown && mainGame->btnDeckEdit->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					ClickButton(mainGame->btnDeckEdit);
				}

				break;
			}
			case irr::KEY_KEY_I: {
				if (!event.KeyInput.PressedDown && mainGame->roomListTable->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					//ScreenReader::getReader()->textToSpeech(fmt::format(L"Player {}", mainGame->roomListTable->getCellData(onlineMatchCounter, 0)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(186).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 1)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(187).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 2)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(188).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 3)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(189).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 4)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(190).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 5)));
					ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(191).data(), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
				}
				break;
			}
			case irr::KEY_KEY_F: {
				if (!event.KeyInput.PressedDown && mainGame->btnHostPrepNotReady->isEnabled() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					ClickButton(mainGame->btnHostPrepNotReady);
				break;
			}
			case irr::KEY_KEY_C: {
				if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->cbDeckSelect);
					std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
					ScreenReader::getReader()->readScreen(nvdaString.c_str());
				}
				break;
			}
			case irr::KEY_KEY_V: {
				if (!event.KeyInput.PressedDown && mainGame->gBot.cbBotDeck->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
					std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
					ScreenReader::getReader()->readScreen(nvdaString.c_str());
				}
				break;
			}
			case irr::KEY_KEY_B: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					ScreenReader::getReader()->readLastMessage();
				}
				break;
			}
			case irr::KEY_KEY_M: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(193).data()), false);
					mainGame->env->setFocus(mainGame->ebChatInput);
				}
				break;
			}
			case irr::KEY_DOWN: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
					}
					else if (mainGame->roomListTable->isTrulyVisible() && currentMenu == MenuType::OnlineMenu::ROOMS)
						ReadOnlineRoomFromList(irr::KEY_DOWN);
					else if (mainGame->lstSinglePlayList->isTrulyVisible())
						ReadSinglePlayerList();
					else if (mainGame->lstReplayList->isTrulyVisible())
						ReadReplayList();
				}
				break;
			}
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
					}
					else if (mainGame->roomListTable->isTrulyVisible() && currentMenu == MenuType::OnlineMenu::ROOMS) {
						ReadOnlineRoomFromList(irr::KEY_UP);
					}
					else if (mainGame->lstSinglePlayList->isTrulyVisible())
						ReadSinglePlayerList();
					else if (mainGame->lstReplayList->isTrulyVisible())
						ReadReplayList();
				}
				break;
			}
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					ReadMenu(irr::KEY_RIGHT);
				break;
			}
			case irr::KEY_LEFT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					ReadMenu(irr::KEY_LEFT);
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					mainGame->env->removeFocus(mainGame->env->getFocus());
				if (!event.KeyInput.PressedDown) {
					if (menu.empty())
					{
						menu = menuMain;
						activeMenu = MainMenuHandler::GetMenu();
					}
					if (menu.at(0) == MenuType::MainMenu::MM_ONLINE_DUEL) {
					}
					else if (menu.at(0) == MenuType::SinglePlayerMenu::SP_HOST) {
						SPDuel();
					}
					else if (menu.at(0) == MenuType::HostDuel::RULES_OK) {
						HostDuel();
					}
					else if (menu.at(0) == MenuType::PlayerDuel::PD_START_DUEL) {
						DuelMenu();
					}
					else if (menu.at(0) == MenuType::AIConfigMenu::AIC_OK) {
						AIConfigMenu();
					}
					else if (menu.at(0) == MenuType::OnlineMenu::HOST) {
						OnlineDuel();
					}
					else if (menu.at(0) == MenuType::PasswordMenu::PASS_SET_PASSWORD) {
						PasswordMenu();
					}
					else if (menu.at(0) == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS) {
						GameOptions();
					}
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					menuSelectCounter = 0;
					onlineMatchCounter = 0;
					if (mainGame->btnRPNo->isTrulyVisible())
						ClickButton(mainGame->btnRPNo);
					else if (mainGame->btnHostPrepCancel->isTrulyVisible())
						ClickButton(mainGame->btnHostPrepCancel);
					else if (mainGame->btnHostCancel->isTrulyVisible())
						ClickButton(mainGame->btnHostCancel);
					else if (mainGame->btnJoinCancel->isTrulyVisible())
						ClickButton(mainGame->btnJoinCancel);
					else if (mainGame->btnJoinCancel2->isTrulyVisible())
						ClickButton(mainGame->btnJoinCancel2);
					else if (mainGame->gSettings.window->isTrulyVisible())
						mainGame->HideElement(mainGame->gSettings.window);
					else if (mainGame->btnSinglePlayCancel->isTrulyVisible())
						ClickButton(mainGame->btnSinglePlayCancel);
					else if (mainGame->btnReplayCancel->isTrulyVisible())
						ClickButton(mainGame->btnReplayCancel);
					else if (mainGame->btnModeExit->isTrulyVisible())
						ClickButton(mainGame->btnModeExit);
					if (menu.empty())
					{
						menu = menuMain;
						activeMenu = MainMenuHandler::GetMenu();
					}
					else
						currentMenu = menu.at(menuSelectCounter);
				}

				break;
			}
		}
	}

	void MenuEventHandler::GuiEvent(const irr::SEvent& event)
	{
		int id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED: {
				switch (id) {
					case BUTTON_JOIN_HOST2: {
						if (mainGame->roomListTable->getSelected() >= 0) {
							if (mainGame->ebRPName->isTrulyVisible()) {
								menu = menuPassword;
							}
							else {
								menu = menuRulesOkOnline;
							}
							menuSelectCounter = 0;
							currentMenu = menu.at(menuSelectCounter);
						}
						break;
					}
					case BUTTON_ROOMPASSWORD_OK: {
						if (mainGame->cbDeckSelect->isTrulyVisible()) {
							menu = menuRulesOkOnline;
						}
						else {
							menu = menuOnline;
						}
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_ROOMPASSWORD_CANCEL: {
						menu = menuRulesOkOnline;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_LAN_MODE: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_SP_DUEL).data());
						menu = menuSinglePlayer;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						activeMenu = LanModeMenuHandler::GetMenu();
						break;
					}
					case BUTTON_JOIN_CANCEL: {
						menu = menuMain;
						activeMenu = MainMenuHandler::GetMenu();
						break;
					}
					case BUTTON_CREATE_HOST: {
						if (wcslen(mainGame->ebNickName->getText())) {
							mainGame->ebNickName->setText(gDataManager->GetAccessibilityString(207).data());
						}
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(208).data());
						menu = menuHostDuel;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_CREATE_HOST2: {
						if (wcslen(mainGame->ebNickName->getText())) {
							mainGame->ebNickName->setText(gDataManager->GetAccessibilityString(207).data());
						}
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(209).data());
						menu = menuHostDuel;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_HOST_CONFIRM: {
						if (mainGame->isHostingOnline) {
							menu = menuRulesOkOnline;
						}
						else {
							menu = menuRulesOk;
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(210).data());
						}
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_HOST_CANCEL: {
						if (mainGame->isHostingOnline) {
							menu = menuOnline;
						}
						else {
							menu = menuSinglePlayer;
							activeMenu = LanModeMenuHandler::GetMenu();
						}
						break;
					}
					case BUTTON_HP_DUELIST: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(211).data());
						break;
					}
					case BUTTON_HP_OBSERVER: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(212).data());
						break;
					}
					case BUTTON_HP_READY: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(213).data());
						break;
					}
					case BUTTON_HP_NOTREADY: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(214).data());
						break;
					}
					case BUTTON_HP_START: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(215).data());
						break;
					}
					case BUTTON_HP_CANCEL: {
						if (mainGame->isHostingOnline) {
							menu = menuOnline;
						}
						else {
							menu = menuHostDuel;
						}
						break;
					}
					case BUTTON_HP_AI_TOGGLE: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(216).data());
						menu = menuSelectAI;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_BOT_ADD: {
						menu = menuRulesOk;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(217).data());
						break;
					}
					case BUTTON_DECK_EDIT: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(218).data());
						break;
					}
					default:{
						CheckMenu();
						if(activeMenu != nullptr)
							activeMenu->KeyInputEvent(event);
						break;
					}
				}
			}
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
					default:{
						CheckMenu();
						if(activeMenu != nullptr)
							activeMenu->KeyInputEvent(event);
						break;
					}
				}
			}
			case irr::gui::EGET_COMBO_BOX_CHANGED: {
				switch (id) {
					case COMBOBOX_PLAYER_DECK: {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					case COMBOBOX_BOT_DECK: {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					case SERVER_CHOICE: {
						std::wstring nvdaString = fmt::format(L"{}", mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					case CB_FILTER_ALLOWED_CARDS: {
						std::wstring nvdaString = fmt::format(L"{}", mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					case CB_FILTER_BANLIST: {
						std::wstring nvdaString = fmt::format(L"{}", mainGame->cbFilterBanlist->getItem(mainGame->cbFilterBanlist->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					default:{
						CheckMenu();
						if(activeMenu != nullptr)
							activeMenu->KeyInputEvent(event);
						break;
					}
				}
			}
		}
	}

	void MenuEventHandler::CheckMenu() {
		if (mainGame->gSettings.window->isTrulyVisible())
			menu = menuGameOptions;
		else if (
			(mainGame->btnOnlineMode->isEnabled() && mainGame->btnOnlineMode->isTrulyVisible()) ||
			(mainGame->btnReplayCancel->isEnabled() && mainGame->btnReplayCancel->isTrulyVisible()))
		{
			menu = menuMain;
			activeMenu = MainMenuHandler::GetMenu();
		}
		else if (mainGame->ebRPName->isEnabled() && mainGame->ebRPName->isTrulyVisible())
			menu = menuPassword;
		else if (mainGame->btnCreateHost->isEnabled() && mainGame->btnCreateHost->isTrulyVisible())
			activeMenu = LanModeMenuHandler::GetMenu();
		else if (mainGame->gBot.btnAdd->isEnabled() && mainGame->gBot.btnAdd->isTrulyVisible())
			menu = menuSelectAI;
		else if (mainGame->btnHostPrepWindBot->isEnabled() && mainGame->btnHostPrepWindBot->isTrulyVisible())
			menu = menuRulesOk;
		else if (mainGame->btnCreateHost2->isEnabled() && mainGame->btnCreateHost2->isTrulyVisible())
			menu = menuOnline;
		else if (mainGame->btnSinglePlayCancel->isEnabled() && mainGame->btnSinglePlayCancel->isTrulyVisible())
			menu = menuPuzzles;
		else if ((mainGame->btnHostPrepDuelist->isEnabled() && mainGame->btnHostPrepDuelist->isTrulyVisible()) ||
			mainGame->btnHostPrepOB->isEnabled() && mainGame->btnHostPrepOB->isTrulyVisible())
			menu = menuRulesOkOnline;
		else if (mainGame->ebStartLP->isTrulyVisible())
			menu = menuHostDuel;
	}


	void MenuEventHandler::PasswordMenu() {
		if (currentMenu == MenuType::PasswordMenu::PASS_SET_PASSWORD && mainGame->ebRPName->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(223).data()).c_str());
				FocusTextBox(mainGame->ebRPName);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(224).data(), mainGame->ebRPName->getText()));
			}
		}
		else if (currentMenu == MenuType::PasswordMenu::PASS_OK && mainGame->btnRPYes->isEnabled()) {
			ClickButton(mainGame->btnRPYes);
		}
		else if (currentMenu == MenuType::PasswordMenu::PASS_CANCEL && mainGame->btnRPNo->isEnabled()) {
			ClickButton(mainGame->btnRPNo);
		}
	}

	void MenuEventHandler::AIConfigMenu() {
		if (currentMenu == MenuType::AIConfigMenu::AIC_OK && mainGame->gBot.btnAdd->isTrulyVisible() && mainGame->gBot.btnAdd->isEnabled()) {
			ClickButton(mainGame->gBot.btnAdd);
		}
		else if (currentMenu == MenuType::AIConfigMenu::AIC_SELECT_DECK && mainGame->gBot.cbBotDeck->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
			std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
		else if (currentMenu == MenuType::AIConfigMenu::AIC_ATR && mainGame->gBot.chkThrowRock->isTrulyVisible()) {
			CheckBox(mainGame->gBot.chkThrowRock);
		}
	}

	void MenuEventHandler::SPDuel() {
		if (currentMenu == MenuType::SinglePlayerMenu::SP_HOST && mainGame->btnCreateHost->isEnabled()) {
			ClickButton(mainGame->btnCreateHost);
		}
		else if (currentMenu == MenuType::SinglePlayerMenu::SP_PLAYER_NAME && mainGame->ebNickName->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(225).data()).c_str());
				FocusTextBox(mainGame->ebNickName);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(226).data(), mainGame->ebNickName->getText()));
			}
		}
	}

	void MenuEventHandler::DuelMenu() {
		if (currentMenu == MenuType::PlayerDuel::PD_START_DUEL && mainGame->btnHostPrepStart->isEnabled()) {
			ClickButton(mainGame->btnHostPrepStart);
		}
		else if (currentMenu == MenuType::PlayerDuel::PD_START_DUEL && !mainGame->btnHostPrepStart->isEnabled() && mainGame->btnHostPrepStart->isTrulyVisible()) {
			std::wstring nvdaString;
			if (oldMenu == L"SinglePlayer")
				nvdaString = gDataManager->GetAccessibilityString(227).data();
			else
				nvdaString = gDataManager->GetAccessibilityString(228).data();
			ScreenReader::getReader()->readScreen(nvdaString);
		}
		else if (currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepReady->isTrulyVisible() && mainGame->btnHostPrepReady->isEnabled()) {
			ClickButton(mainGame->btnHostPrepReady);
		}
		else if (currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepNotReady->isEnabled()) {
			ClickButton(mainGame->btnHostPrepNotReady);
		}
		else if (currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK && mainGame->cbDeckSelect->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->cbDeckSelect);
			std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
		else if (currentMenu == MenuType::SinglePlayerDuel::SP_AI_MENU && mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepWindBot->isEnabled()) {
			ClickButton(mainGame->btnHostPrepWindBot);
		}
		else if (currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && mainGame->btnHostPrepDuelist->isEnabled()) {
			ClickButton(mainGame->btnHostPrepDuelist);
		}
		else if (currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && !mainGame->btnHostPrepDuelist->isEnabled()) {
			ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(229).data());
		}
		else if (currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && mainGame->btnHostPrepOB->isEnabled()) {
			ClickButton(mainGame->btnHostPrepOB);
		}
		else if (currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && !mainGame->btnHostPrepOB->isEnabled()) {
			ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(230).data());
		}
	}

	void MenuEventHandler::HostDuel() {
		if (currentMenu == MenuType::HostDuel::RULES_OK && mainGame->btnHostConfirm->isEnabled()) {
			ClickButton(mainGame->btnHostConfirm);
		}
		else if (currentMenu == MenuType::HostDuel::NUM_PLAYERS_T1 && mainGame->ebTeam1->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(231).data()).c_str());
				FocusTextBox(mainGame->ebTeam1);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(232).data(), mainGame->ebTeam1->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::NUM_PLAYERS_T2 && mainGame->ebTeam2->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(233).data()).c_str());
				FocusTextBox(mainGame->ebTeam2);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(234).data(), mainGame->ebTeam2->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::BEST_OF && mainGame->ebBestOf->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(235).data()).c_str());
				FocusTextBox(mainGame->ebBestOf);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(236).data(), mainGame->ebBestOf->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::TIME_LIMIT && mainGame->ebTimeLimit->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(237).data()).c_str());
				FocusTextBox(mainGame->ebTimeLimit);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(238).data(), mainGame->ebTimeLimit->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::STARTING_LP && mainGame->ebStartLP->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(239).data());
				FocusTextBox(mainGame->ebStartLP);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(240).data(), mainGame->ebStartLP->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::STARTING_HAND && mainGame->ebStartHand->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(241).data());
				FocusTextBox(mainGame->ebStartHand);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(242).data(), mainGame->ebStartHand->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::CARDS_DRAW && mainGame->ebDrawCount->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(243).data());
				FocusTextBox(mainGame->ebDrawCount);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(244).data(), mainGame->ebDrawCount->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::CHECK_DECK && mainGame->chkNoCheckDeckContent->isTrulyVisible()) {
			CheckBox(mainGame->chkNoCheckDeckContent);
			CheckBox(mainGame->chkNoCheckDeckSize);
		}
		else if (currentMenu == MenuType::HostDuel::SHUFFLE_DECK && mainGame->chkNoShuffleDeck->isTrulyVisible()) {
			CheckBox(mainGame->chkNoShuffleDeck);
		}
		else if (currentMenu == MenuType::HostDuel::ROOM_NAME && mainGame->ebHostNotes->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(245).data());
				FocusTextBox(mainGame->ebHostNotes);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(246).data(), mainGame->ebHostNotes->getText()));
			}
		}
		else if (currentMenu == MenuType::HostDuel::ROOM_PASSWORD && mainGame->ebServerPass->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(247).data());
				FocusTextBox(mainGame->ebServerPass);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(248).data(), mainGame->ebServerPass->getText()));
			}
		}
	}

	void MenuEventHandler::OnlineDuel() {
		menu = menuOnline;
		if (currentMenu == MenuType::OnlineMenu::HOST && mainGame->btnCreateHost2->isEnabled()) {
			ClickButton(mainGame->btnCreateHost2);
		}
		else if (currentMenu == MenuType::OnlineMenu::REFRESH && mainGame->btnLanRefresh2->isEnabled()) {
			onlineMatchCounter = 0;
			ServerLobby::RefreshRooms();
		}
		else if (currentMenu == MenuType::OnlineMenu::JOIN_ONLINE_DUEL && mainGame->btnJoinHost2->isEnabled()) {
			ClickButton(mainGame->btnJoinHost2);
		}
		else if (currentMenu == MenuType::OnlineMenu::SERVER && mainGame->serverChoice->isTrulyVisible()) {
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(249).data(), mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected())));
			mainGame->env->setFocus(mainGame->serverChoice);
		}
		else if (currentMenu == MenuType::OnlineMenu::PLAYER_NAME && mainGame->ebNickNameOnline->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(250).data());
				FocusTextBox(mainGame->ebNickNameOnline);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(251).data(), mainGame->ebNickNameOnline->getText()));
			}
		}
		else if (currentMenu == MenuType::OnlineMenu::ALLOWED_CARDS && mainGame->cbFilterRule->isTrulyVisible()) {
			ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected())));
			mainGame->env->setFocus(mainGame->cbFilterRule);
		}
		else if (currentMenu == MenuType::OnlineMenu::FORBIDDEN_LIST && mainGame->cbFilterBanlist->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->cbFilterBanlist);
			ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterBanlist->getItem(mainGame->cbFilterBanlist->getSelected())));
		}
		else if (currentMenu == MenuType::OnlineMenu::LOCKED_ROOMS && mainGame->chkShowPassword->isTrulyVisible()) {
			CheckBox(mainGame->chkShowPassword);
		}
		else if (currentMenu == MenuType::OnlineMenu::STARTED_ROOMS && mainGame->chkShowActiveRooms->isTrulyVisible()) {
			CheckBox(mainGame->chkShowActiveRooms);
		}
	}

	void MenuEventHandler::GameOptions() {
		menu = menuGameOptions;
		if (currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS && mainGame->gSettings.chkEnableSound->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkEnableSound);
			gSoundManager->EnableSounds(mainGame->gSettings.chkEnableSound->isChecked());
			gGameConfig->enablesound = mainGame->gSettings.chkEnableSound->isChecked();
		}
		else if (currentMenu == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME && mainGame->gSettings.scrSoundVolume->isTrulyVisible()) {
			if (!scrollSelected) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
				mainGame->env->setFocus(mainGame->gSettings.scrSoundVolume);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(252).data(), gGameConfig->soundVolume));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC && mainGame->gSettings.chkEnableMusic->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkEnableMusic);
			gSoundManager->EnableMusic(mainGame->gSettings.chkEnableMusic->isChecked());
			gGameConfig->enablemusic = mainGame->gSettings.chkEnableMusic->isChecked();
		}
		else if (currentMenu == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME && mainGame->gSettings.scrMusicVolume->isTrulyVisible()) {
			if (!scrollSelected) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
				mainGame->env->setFocus(mainGame->gSettings.scrMusicVolume);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(252).data(), gGameConfig->musicVolume));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (currentMenu == MenuType::GameOptionsMenu::USE_MUD_KEYBOARD && mainGame->gSettings.chkUseMudKeyboard->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkUseMudKeyboard);
			gGameConfig->mudKeyboard = mainGame->gSettings.chkUseMudKeyboard->isChecked();
			EventHandler::mudConfiguration = mainGame->gSettings.chkUseMudKeyboard->isChecked();
		}
	}
}
