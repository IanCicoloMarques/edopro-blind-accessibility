#include "AccessibilityMenu.h"

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

	void MenuEventHandler::KeyInputEvent(const irr::SEvent& event)
	{
		IScreenReader* screenReader = ScreenReader::getReader();
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
					if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && menuSelectCounter == MenuType::PlayerDuel::PD_SELECT_DECK && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
					}
					else if (mainGame->roomListTable->isTrulyVisible() && currentMenu == gDataManager->GetAccessibilityString(194).data()) {
						if (onlineMatchCounter < mainGame->roomListTable->getRowCount() - 1)
							onlineMatchCounter++;
						mainGame->roomListTable->setSelected(onlineMatchCounter);
						std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(onlineMatchCounter, 5));
						int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
						if (numPlayers > 1)
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(195).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
						else
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(196).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
					}
					else if (mainGame->lstSinglePlayList->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->lstSinglePlayList);
						irr::s32 listItem = mainGame->lstSinglePlayList->getSelected();
						if (listItem == -1) {
							listItem = 0;
							mainGame->lstSinglePlayList->setSelected(mainGame->lstSinglePlayList->getListItem(listItem));
						}
						ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstSinglePlayList->getListItem(listItem)));
					}
					else if (mainGame->lstReplayList->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->lstReplayList);
						irr::s32 listItem = mainGame->lstReplayList->getSelected();
						if (listItem == -1) {
							listItem = 0;
							mainGame->lstReplayList->setSelected(mainGame->lstReplayList->getListItem(listItem));
						}
						ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstReplayList->getListItem(listItem)));
					}
					
				}
				break;
			}
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && menuSelectCounter == MenuType::PlayerDuel::PD_SELECT_DECK  && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
					}
					else if (mainGame->roomListTable->isTrulyVisible() && currentMenu == gDataManager->GetAccessibilityString(194).data()) {
						if (onlineMatchCounter > 0)
							onlineMatchCounter--;
						mainGame->roomListTable->setSelected(onlineMatchCounter);
						std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(onlineMatchCounter, 5));
						int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
						if (numPlayers > 1)
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(195).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
						else
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(196).data(), numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
					}
					else if (mainGame->lstSinglePlayList->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->lstSinglePlayList);
						irr::s32 listItem = mainGame->lstSinglePlayList->getSelected();
						if (listItem == -1) {
							listItem = 0;
							mainGame->lstSinglePlayList->setSelected(mainGame->lstSinglePlayList->getListItem(listItem));
						}
						ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstSinglePlayList->getListItem(listItem)));
					}
					else if (mainGame->lstReplayList->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->lstReplayList);
						irr::s32 listItem = mainGame->lstReplayList->getSelected();
						if (listItem == -1) {
							listItem = 0;
							mainGame->lstReplayList->setSelected(mainGame->lstReplayList->getListItem(listItem));
						}
						ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstReplayList->getListItem(listItem)));
					}
				}
				break;
			}
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!scrollSelected) {
						CheckMenu();
						typing = false;
						mainGame->env->removeFocus(mainGame->env->getFocus());
						if (menu.empty())
							menu = menuMain;
						menuSelectCounter++;
						if (menuSelectCounter >= menu.size())
							menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						ScreenReader::getReader()->readScreen(menu.at(menuSelectCounter).c_str());
						if (menu.at(menuSelectCounter) == gDataManager->GetAccessibilityString(194).data())
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(197).data(), mainGame->roomListTable->getRowCount()));
					}
				}
				break;
			}
			case irr::KEY_LEFT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!scrollSelected) {
						CheckMenu();
						typing = false;
						mainGame->env->removeFocus(mainGame->env->getFocus());
						if (menu.empty())
							menu = menuMain;
						menuSelectCounter--;
						if (menuSelectCounter < 0)
							menuSelectCounter = menu.size() - 1;
						currentMenu = menu.at(menuSelectCounter);
						ScreenReader::getReader()->readScreen(menu.at(menuSelectCounter).c_str());
						if (menu.at(menuSelectCounter) == gDataManager->GetAccessibilityString(194).data())
							ScreenReader::getReader()->textToSpeech(fmt::format(gDataManager->GetAccessibilityString(197).data(), mainGame->roomListTable->getRowCount()));
					}
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					mainGame->env->removeFocus(mainGame->env->getFocus());
				if (!event.KeyInput.PressedDown) {
					if (menu.empty())
						menu = menuMain;
					if (menu.at(0) == gDataManager->GetAccessibilityString(198).data()) {
						MainMenu();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(199).data()) {
						SPDuel();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(200).data()) {
						HostDuel();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(201).data()) {
						DuelMenu();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(202).data()) {
						AIConfigMenu();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(203).data()) {
						OnlineDuel();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(204).data()) {
						PasswordMenu();
					}
					else if (menu.at(0) == gDataManager->GetAccessibilityString(205).data()) {
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
						menu = menuMain;
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
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(206).data());
						menu = menuSinglePlayer;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_JOIN_CANCEL: {
						menu = menuMain;
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
				}
			}
		}
	}

	void MenuEventHandler::CheckMenu() {

		if (mainGame->gSettings.window->isTrulyVisible())
			menu = menuGameOptions;
		else if (mainGame->btnOnlineMode->isEnabled() && mainGame->btnOnlineMode->isTrulyVisible())
			menu = menuMain;
		else if (mainGame->ebRPName->isEnabled() && mainGame->ebRPName->isTrulyVisible())
			menu = menuPassword;
		else if (mainGame->btnCreateHost->isEnabled() && mainGame->btnCreateHost->isTrulyVisible())
			menu = menuSinglePlayer;
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

	}

	void MenuEventHandler::MainMenu() {
		if (menuSelectCounter == MenuType::MainMenu::MM_ONLINE_DUEL && mainGame->btnOnlineMode->isEnabled()) {
			ClickButton(mainGame->btnOnlineMode);
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_SP_DUEL && mainGame->btnLanMode->isEnabled()) {
			ClickButton(mainGame->btnLanMode);
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_PUZZLES && mainGame->btnSingleMode->isEnabled()) {
			ClickButton(mainGame->btnSingleMode);
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_REPLAY && mainGame->btnReplayMode->isEnabled()) {
			ClickButton(mainGame->btnReplayMode);
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_DECK_EDITOR && mainGame->btnDeckEdit->isEnabled()) {
			ClickButton(mainGame->btnDeckEdit);
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_GAME_OPTIONS && mainGame->wBtnSettings->isEnabled()) {
			ClickButton(mainGame->btnSettings);
			menu = menuGameOptions;
		}
		else if (menuSelectCounter == MenuType::MainMenu::MM_ACCESSILITY_KEYS) {
			ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage());
		}
	}

	void MenuEventHandler::PasswordMenu() {
		if (menuSelectCounter == MenuType::PasswordMenu::PASS_SET_PASSWORD && mainGame->ebRPName->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::PasswordMenu::PASS_OK && mainGame->btnRPYes->isEnabled()) {
			ClickButton(mainGame->btnRPYes);
		}
		else if (menuSelectCounter == MenuType::PasswordMenu::PASS_CANCEL && mainGame->btnRPNo->isEnabled()) {
			ClickButton(mainGame->btnRPNo);
		}
	}

	void MenuEventHandler::AIConfigMenu() {
		if (menuSelectCounter == MenuType::AIConfigMenu::AIC_OK && mainGame->gBot.btnAdd->isTrulyVisible() && mainGame->gBot.btnAdd->isEnabled()) {
			ClickButton(mainGame->gBot.btnAdd);
		}
		else if (menuSelectCounter == MenuType::AIConfigMenu::AIC_SELECT_DECK && mainGame->gBot.cbBotDeck->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
			std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
		else if (menuSelectCounter == MenuType::AIConfigMenu::AIC_ATR && mainGame->gBot.chkThrowRock->isTrulyVisible()) {
			CheckBox(mainGame->gBot.chkThrowRock);
		}
	}

	void MenuEventHandler::SPDuel() {
		if (menuSelectCounter == MenuType::SinglePlayerMenu::SP_HOST && mainGame->btnCreateHost->isEnabled()) {
			ClickButton(mainGame->btnCreateHost);
		}
		else if (menuSelectCounter == MenuType::SinglePlayerMenu::SP_PLAYER_NAME && mainGame->ebNickName->isTrulyVisible()) {
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
		if (menuSelectCounter == MenuType::PlayerDuel::PD_START_DUEL && mainGame->btnHostPrepStart->isEnabled()) {
			ClickButton(mainGame->btnHostPrepStart);
		}
		else if (menuSelectCounter == MenuType::PlayerDuel::PD_START_DUEL && !mainGame->btnHostPrepStart->isEnabled() && mainGame->btnHostPrepStart->isTrulyVisible()) {
			std::wstring nvdaString;
			if (oldMenu == L"SinglePlayer")
				nvdaString = gDataManager->GetAccessibilityString(227).data();
			else
				nvdaString = gDataManager->GetAccessibilityString(228).data();
			ScreenReader::getReader()->readScreen(nvdaString);
		}
		else if (menuSelectCounter == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepReady->isTrulyVisible() && mainGame->btnHostPrepReady->isEnabled()) {
			ClickButton(mainGame->btnHostPrepReady);
		}
		else if (menuSelectCounter == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepNotReady->isEnabled()) {
			ClickButton(mainGame->btnHostPrepNotReady);
		}
		else if (menuSelectCounter == MenuType::PlayerDuel::PD_SELECT_DECK && mainGame->cbDeckSelect->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->cbDeckSelect);
			std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
		else if (menuSelectCounter == MenuType::SinglePlayerDuel::SP_AI_MENU && mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepWindBot->isEnabled()) {
			ClickButton(mainGame->btnHostPrepWindBot);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && mainGame->btnHostPrepDuelist->isEnabled()) {
			ClickButton(mainGame->btnHostPrepDuelist);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && !mainGame->btnHostPrepDuelist->isEnabled()) {
			ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(229).data());
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && mainGame->btnHostPrepOB->isEnabled()) {
			ClickButton(mainGame->btnHostPrepOB);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && !mainGame->btnHostPrepOB->isEnabled()) {
			ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(230).data());
		}
	}

	void MenuEventHandler::HostDuel() {
		if (menuSelectCounter == MenuType::HostDuel::RULES_OK && mainGame->btnHostConfirm->isEnabled()) {
			ClickButton(mainGame->btnHostConfirm);
		}
		else if (menuSelectCounter == MenuType::HostDuel::NUM_PLAYERS_T1 && mainGame->ebTeam1->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::NUM_PLAYERS_T2 && mainGame->ebTeam2->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::BEST_OF && mainGame->ebBestOf->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::TIME_LIMIT && mainGame->ebTimeLimit->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::STARTING_LP && mainGame->ebStartLP->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::STARTING_HAND && mainGame->ebStartHand->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::CARDS_DRAW && mainGame->ebDrawCount->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::CHECK_DECK && mainGame->chkNoCheckDeckContent->isTrulyVisible()) {
			CheckBox(mainGame->chkNoCheckDeckContent);
			CheckBox(mainGame->chkNoCheckDeckSize);
		}
		else if (menuSelectCounter == MenuType::HostDuel::SHUFFLE_DECK && mainGame->chkNoShuffleDeck->isTrulyVisible()) {
			CheckBox(mainGame->chkNoShuffleDeck);
		}
		else if (menuSelectCounter == MenuType::HostDuel::ROOM_NAME && mainGame->ebHostNotes->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::HostDuel::ROOM_PASSWORD && mainGame->ebServerPass->isTrulyVisible()) {
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
		if (menuSelectCounter == MenuType::OnlineMenu::HOST && mainGame->btnCreateHost2->isEnabled()) {
			ClickButton(mainGame->btnCreateHost2);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::REFRESH && mainGame->btnLanRefresh2->isEnabled()) {
			onlineMatchCounter = 0;
			ServerLobby::RefreshRooms();
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::HOST_ONLINE_DUEL && mainGame->btnJoinHost2->isEnabled()) {
			ClickButton(mainGame->btnJoinHost2);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::SERVER && mainGame->serverChoice->isTrulyVisible()) {
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(249).data(), mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected())));
			mainGame->env->setFocus(mainGame->serverChoice);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::PLAYER_NAME && mainGame->ebNickNameOnline->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::OnlineMenu::ALLOWED_CARDS && mainGame->cbFilterRule->isTrulyVisible()) {
			ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterRule->getItem(mainGame->cbFilterRule->getSelected())));
			mainGame->env->setFocus(mainGame->cbFilterRule);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::FORBIDDEN_LIST && mainGame->cbFilterBanlist->isTrulyVisible()) {
			mainGame->env->setFocus(mainGame->cbFilterBanlist);
			ScreenReader::getReader()->readScreen(fmt::format(L"{}", mainGame->cbFilterBanlist->getItem(mainGame->cbFilterBanlist->getSelected())));
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::LOCKED_ROOMS && mainGame->chkShowPassword->isTrulyVisible()) {
			CheckBox(mainGame->chkShowPassword);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::STARTED_ROOMS && mainGame->chkShowActiveRooms->isTrulyVisible()) {
			CheckBox(mainGame->chkShowActiveRooms);
		}
	}

	void MenuEventHandler::GameOptions() {
		menu = menuGameOptions;
		if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS && mainGame->gSettings.chkEnableSound->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkEnableSound);
			gSoundManager->EnableSounds(mainGame->gSettings.chkEnableSound->isChecked());
			gGameConfig->enablesound = mainGame->gSettings.chkEnableSound->isChecked();
		}
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME && mainGame->gSettings.scrSoundVolume->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC && mainGame->gSettings.chkEnableMusic->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkEnableMusic);
			gSoundManager->EnableMusic(mainGame->gSettings.chkEnableMusic->isChecked());
			gGameConfig->enablemusic = mainGame->gSettings.chkEnableMusic->isChecked();
		}
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME && mainGame->gSettings.scrMusicVolume->isTrulyVisible()) {
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
	}
}
