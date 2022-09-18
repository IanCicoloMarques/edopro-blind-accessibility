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
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Allowed Cards {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 1)));
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Duel Mode {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 2)));
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Rule {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 3)));
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Forbidden List {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 4)));
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Status {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 5)));
					ScreenReader::getReader()->textToSpeech(fmt::format(L"Notes {}", mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
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
					std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
					ScreenReader::getReader()->readScreen(nvdaString.c_str());
				}
				break;
			}
			case irr::KEY_KEY_V: {
				if (!event.KeyInput.PressedDown && mainGame->gBot.cbBotDeck->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
					std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
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
					ScreenReader::getReader()->readScreen(fmt::format(L"Chat active"), false);
					mainGame->env->setFocus(mainGame->ebChatInput);
				}
				break;
			}
			case irr::KEY_DOWN: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->roomListTable->isTrulyVisible() && currentMenu == L"Rooms") {
						if (onlineMatchCounter < mainGame->roomListTable->getRowCount() - 1)
							onlineMatchCounter++;
						mainGame->roomListTable->setSelected(onlineMatchCounter);
						std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(onlineMatchCounter, 5));
						int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
						if (numPlayers > 1)
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} Players {}, {}", numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
						else
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} Player {}, {}", numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
					}
				}
				break;
			}
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && menuSelectCounter == MenuType::PlayerDuel::PD_SELECT_DECK  && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
					}
					else if (mainGame->roomListTable->isTrulyVisible() && currentMenu == L"Rooms") {
						if (onlineMatchCounter > 0)
							onlineMatchCounter--;
						mainGame->roomListTable->setSelected(onlineMatchCounter);
						std::wstring numberPlayers = std::wstring(mainGame->roomListTable->getCellText(onlineMatchCounter, 5));
						int numPlayers = std::count(numberPlayers.begin(), numberPlayers.end(), ',') + 1;
						if (numPlayers > 1)
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} Players {}, {}", numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
						else
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} Player {}, {}", numPlayers, mainGame->roomListTable->getCellText(onlineMatchCounter, 5), mainGame->roomListTable->getCellText(onlineMatchCounter, 6)));
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
						if (menu.at(menuSelectCounter) == L"Rooms")
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} games", mainGame->roomListTable->getRowCount()));
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
						if (menu.at(menuSelectCounter) == L"Rooms")
							ScreenReader::getReader()->textToSpeech(fmt::format(L"{} games", mainGame->roomListTable->getRowCount()));
					}
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (menu.empty())
						menu = menuMain;
					if (menu.at(0) == L"Online Duel") {
						MainMenu();
					}
					//else if (selectedMenu == MainMenu::MAIN_MENU) {
					else if (menu.at(0) == L"Host Duel") {
						SPDuel();
					}
					//else if (selectedMenu == MainMenu::HOST_DUEL) {
					else if (menu.at(0) == L"Rules ok") {
						HostDuel();
					}
					//else if (selectedMenu == MainMenu::DUEL_MENU) {
					else if (menu.at(0) == L"Start Duel") {
						DuelMenu();
					}
					//else if (selectedMenu == MainMenu::AI_CONFIGURATION) {
					else if (menu.at(0) == L"AI Ok") {
						AIConfigMenu();
					}
					//else if (selectedMenu == MainMenu::ONLINE) {
					else if (menu.at(0) == L"Host") {
						OnlineDuel();
					}
					//else if (selectedMenu == MainMenu::ONLINE) {
					else if (menu.at(0) == L"Change Password") {
						PasswordMenu();
					}
					//else if (selectedMenu == MainMenu::ONLINE) {
					else if (menu.at(0) == L"Enable Sound Effects") {
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
					else if (mainGame->btnModeExit->isTrulyVisible())
						ClickButton(mainGame->btnModeExit);
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
								menuSelectCounter = 0;
								currentMenu = menu.at(menuSelectCounter);
							}
							else {
								menu = menuRulesOkOnline;
								menuSelectCounter = 0;
								currentMenu = menu.at(menuSelectCounter);
							}
						}
						break;
					}
					case BUTTON_ROOMPASSWORD_OK: {
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						if (mainGame->cbDeckSelect->isTrulyVisible()) {
							menu = menuRulesOkOnline;
						}
						else {
							menu = menuOnline;
						}
						break;
					}
					case BUTTON_ROOMPASSWORD_CANCEL: {
						menu = menuRulesOkOnline;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_LAN_MODE: {
						ScreenReader::getReader()->readScreen(L"LAN + AI");
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
							mainGame->ebNickName->setText(L"Player");
						}
						ScreenReader::getReader()->readScreen(L"Host game");
						menu = menuHostDuel;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_CREATE_HOST2: {
						if (wcslen(mainGame->ebNickName->getText())) {
							mainGame->ebNickName->setText(L"Player");
						}
						ScreenReader::getReader()->readScreen(L"Host online game");
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
							ScreenReader::getReader()->readScreen(L"Rules ok.");
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
						ScreenReader::getReader()->readScreen(L"Duel mode");
						break;
					}
					case BUTTON_HP_OBSERVER: {
						ScreenReader::getReader()->readScreen(L"Spectator mode");
						break;
					}
					case BUTTON_HP_READY: {
						ScreenReader::getReader()->readScreen(L"Player ready");
						break;
					}
					case BUTTON_HP_NOTREADY: {
						ScreenReader::getReader()->readScreen(L"Player not ready");
						break;
					}
					case BUTTON_HP_START: {
						ScreenReader::getReader()->readScreen(L"Start game");
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
						ScreenReader::getReader()->readScreen(L"Bot Configuration");
						menu = menuSelectAI;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						break;
					}
					case BUTTON_BOT_ADD: {
						menu = menuRulesOk;
						menuSelectCounter = 0;
						currentMenu = menu.at(menuSelectCounter);
						ScreenReader::getReader()->readScreen(L"Added Bot");
						break;
					}
					case BUTTON_DECK_EDIT: {
						ScreenReader::getReader()->readScreen(L"Deck Editor");
						break;
					}
				}
			}
			case irr::gui::EGET_CHECKBOX_CHANGED: {
				switch (id) {
					case CHECK_SHOW_LOCKED_ROOMS: {
						std::wstring screenReaderString;
						if (mainGame->chkShowPassword->isChecked())
							screenReaderString = L"Show locked rooms";
						else
							screenReaderString = L"Do not show locked rooms";
						ScreenReader::getReader()->readScreen(screenReaderString);
						break;
					}
					case CHECK_SHOW_ACTIVE_ROOMS: {
						std::wstring screenReaderString;
						if (mainGame->chkShowActiveRooms->isChecked())
							screenReaderString = L"Show active rooms";
						else
							screenReaderString = L"Do not show active rooms";
						ScreenReader::getReader()->readScreen(screenReaderString);
						break;
					}
				}
			}
			case irr::gui::EGET_COMBO_BOX_CHANGED: {
				switch (id) {
					case COMBOBOX_PLAYER_DECK: {
						std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str());
						break;
					}
					case COMBOBOX_BOT_DECK: {
						std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
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
				ScreenReader::getReader()->readScreen(std::wstring(L"Type the password").c_str());
				FocusTextBox(mainGame->ebRPName);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Password: {}", mainGame->ebRPName->getText()));
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
			std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
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
				ScreenReader::getReader()->readScreen(std::wstring(L"Type your name").c_str());
				FocusTextBox(mainGame->ebNickName);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set name as {}", mainGame->ebNickName->getText()));
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
				nvdaString = L"Get ready and select enemy before start the game";
			else
				nvdaString = L"Get ready and wait for enemy before start the game";
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
			std::wstring nvdaString = fmt::format(L"Deck {}", mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
		else if (menuSelectCounter == MenuType::SinglePlayerDuel::SP_AI_MENU && mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepWindBot->isEnabled()) {
			ClickButton(mainGame->btnHostPrepWindBot);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && mainGame->btnHostPrepDuelist->isEnabled()) {
			ClickButton(mainGame->btnHostPrepDuelist);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && !mainGame->btnHostPrepDuelist->isEnabled()) {
			ScreenReader::getReader()->readScreen(L"You are already on duel mode");
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && mainGame->btnHostPrepOB->isEnabled()) {
			ClickButton(mainGame->btnHostPrepOB);
		}
		else if (menuSelectCounter == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && !mainGame->btnHostPrepOB->isEnabled()) {
			ScreenReader::getReader()->readScreen(L"You are already on spectator mode");
		}
	}

	void MenuEventHandler::HostDuel() {
		if (menuSelectCounter == MenuType::HostDuel::RULES_OK && mainGame->btnHostConfirm->isEnabled()) {
			ClickButton(mainGame->btnHostConfirm);
		}
		else if (menuSelectCounter == MenuType::HostDuel::NUM_PLAYERS_T1 && mainGame->ebTeam1->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(L"Type number of players in the team 1").c_str());
				FocusTextBox(mainGame->ebTeam1);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set number of players as {}", mainGame->ebTeam1->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::NUM_PLAYERS_T2 && mainGame->ebTeam2->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(L"Type number of players in the team 2").c_str());
				FocusTextBox(mainGame->ebTeam2);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set number of players as {}", mainGame->ebTeam2->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::BEST_OF && mainGame->ebBestOf->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(L"Type number of matches").c_str());
				FocusTextBox(mainGame->ebBestOf);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set number of matches as {}", mainGame->ebBestOf->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::TIME_LIMIT && mainGame->ebTimeLimit->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(std::wstring(L"Type limit of time, in seconds, per turn").c_str());
				FocusTextBox(mainGame->ebTimeLimit);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set limit of time as {} seconds", mainGame->ebTimeLimit->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::STARTING_LP && mainGame->ebStartLP->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(L"Type number of starting Life points");
				FocusTextBox(mainGame->ebStartLP);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set starting life points as {}", mainGame->ebStartLP->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::STARTING_HAND && mainGame->ebStartHand->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(L"Type starting number of cards on hand");
				FocusTextBox(mainGame->ebStartHand);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set starting cards on hand as {}", mainGame->ebStartHand->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::CARDS_DRAW && mainGame->ebDrawCount->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(L"Type number of cards per draw");
				FocusTextBox(mainGame->ebDrawCount);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set cards per draw as {}", mainGame->ebDrawCount->getText()));
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
				ScreenReader::getReader()->readScreen(L"Type room's name");
				FocusTextBox(mainGame->ebHostNotes);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set room's name as {}", mainGame->ebHostNotes->getText()));
			}
		}
		else if (menuSelectCounter == MenuType::HostDuel::ROOM_PASSWORD && mainGame->ebServerPass->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(L"Type room's password");
				FocusTextBox(mainGame->ebServerPass);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set password as {}", mainGame->ebServerPass->getText()));
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
			ScreenReader::getReader()->readScreen(fmt::format(L"Server {}", mainGame->serverChoice->getItem(mainGame->serverChoice->getSelected())));
			mainGame->env->setFocus(mainGame->serverChoice);
		}
		else if (menuSelectCounter == MenuType::OnlineMenu::PLAYER_NAME && mainGame->ebNickNameOnline->isTrulyVisible()) {
			if (!typing) {
				ScreenReader::getReader()->readScreen(L"Type your name");
				FocusTextBox(mainGame->ebNickNameOnline);
				typing = true;
			}
			else {
				typing = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
				ScreenReader::getReader()->readScreen(fmt::format(L"Set Player name as {}", mainGame->ebNickNameOnline->getText()));
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
		}
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME && mainGame->gSettings.scrSoundVolume->isTrulyVisible()) {
			if (!scrollSelected) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
				mainGame->env->setFocus(mainGame->gSettings.scrSoundVolume);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Volume set to {}", gGameConfig->soundVolume));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC && mainGame->gSettings.chkEnableMusic->isTrulyVisible()) {
			CheckBox(mainGame->gSettings.chkEnableMusic);
		}
		else if (menuSelectCounter == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME && mainGame->gSettings.scrMusicVolume->isTrulyVisible()) {
			if (!scrollSelected) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
				mainGame->env->setFocus(mainGame->gSettings.scrMusicVolume);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Volume set to {}", gGameConfig->musicVolume));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
	}
}
