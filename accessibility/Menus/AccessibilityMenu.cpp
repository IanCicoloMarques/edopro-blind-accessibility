#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

#include "AIMenu.h"
#include "ConfigurationMenu.h"
#include "DuelRulesMenu.h"
#include "LanModeMenu.h"
#include "MainMenu.h"
#include "OnlineModeMenu.h"
#include "PreDuelMenu.h"
#include "PreDuelOnlineMenu.h"
#include "PuzzlesMenu.h"

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
		if(menu == menuPassword)
		{
			if(currentMenu == MenuType::PasswordMenu::PASS_SET_PASSWORD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_SET_PASSWORD).data(), mainGame->ebRPName->getText());
			else if(currentMenu == MenuType::PasswordMenu::PASS_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_OK).data();
			else if(currentMenu == MenuType::PasswordMenu::PASS_CANCEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_CANCEL).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void MenuEventHandler::ReadMenu(irr::EKEY_CODE ekeyCode)
	{
		if (activeMenu != nullptr) {
			activeMenu->SetMenu(ekeyCode);
		}
	};

	void MenuEventHandler::KeyInputEvent(const irr::SEvent& event)
	{
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
			case irr::KEY_KEY_F: {
				if (!event.KeyInput.PressedDown && mainGame->btnHostPrepNotReady->isEnabled() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					ClickButton(mainGame->btnHostPrepNotReady);
				break;
			}
			case irr::KEY_KEY_C: {
				if (!event.KeyInput.PressedDown && mainGame->cbDeckSelect->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->cbDeckSelect);
					const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
					ScreenReader::getReader()->readScreen(nvdaString);
				}
				break;
			}
			case irr::KEY_KEY_V: {
				if (!event.KeyInput.PressedDown && mainGame->gBot.cbBotDeck->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
					const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
					ScreenReader::getReader()->readScreen(nvdaString);
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
					return;
				}
				break;
			}
			case irr::KEY_RETURN:{
				if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					mainGame->env->removeFocus(mainGame->env->getFocus());
					return;
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnRPNo->isTrulyVisible())
						ClickButton(mainGame->btnRPNo);
					else if (mainGame->btnJoinCancel2->isTrulyVisible())
						ClickButton(mainGame->btnJoinCancel2);
					else if (mainGame->gSettings.window->isTrulyVisible())
						mainGame->HideElement(mainGame->gSettings.window);
					else if (mainGame->btnSinglePlayCancel->isTrulyVisible())
						ClickButton(mainGame->btnSinglePlayCancel);
					else if (mainGame->btnReplayCancel->isTrulyVisible())
						ClickButton(mainGame->btnReplayCancel);
				}

				break;
			}
		}
		CheckMenu();
		if(activeMenu != nullptr && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
		{
			activeMenu->KeyInputEvent(event);
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
							else
								activeMenu = PreDuelOnlineMenuHandler::GetMenu();
						}
						break;
					}
					case BUTTON_ROOMPASSWORD_OK: {
						if (mainGame->cbDeckSelect->isTrulyVisible())
							activeMenu = PreDuelOnlineMenuHandler::GetMenu();
						else
							activeMenu = OnlineModeMenuHandler::GetMenu();
						break;
					}
					case BUTTON_ROOMPASSWORD_CANCEL: {
						activeMenu = PreDuelOnlineMenuHandler::GetMenu();
						break;
					}
					case BUTTON_LAN_MODE: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(MenuType::MainMenu::MM_SP_DUEL).data());
						activeMenu = LanModeMenuHandler::GetMenu();
						break;
					}
					case BUTTON_JOIN_CANCEL: {
						activeMenu = MainMenuHandler::GetMenu();
						break;
					}
					case BUTTON_CREATE_HOST: {
						if (wcslen(mainGame->ebNickName->getText())) {
							mainGame->ebNickName->setText(gDataManager->GetAccessibilityString(207).data());
						}
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(208).data());
						activeMenu = DuelRulesMenuHandler::GetMenu();
						break;
					}
					case BUTTON_CREATE_HOST2: {
						if (wcslen(mainGame->ebNickName->getText())) {
							mainGame->ebNickName->setText(gDataManager->GetAccessibilityString(207).data());
						}
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(209).data());
						activeMenu = DuelRulesMenuHandler::GetMenu();
						break;
					}
					case BUTTON_HOST_CONFIRM: {
						if (mainGame->isHostingOnline) {
							activeMenu = PreDuelOnlineMenuHandler::GetMenu();
						}
						else {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(210).data());
							activeMenu = PreDuelMenuHandler::GetMenu();
						}
						break;
					}
					case BUTTON_HOST_CANCEL: {
						if (mainGame->isHostingOnline)
							activeMenu = OnlineModeMenuHandler::GetMenu();
						else
							activeMenu = LanModeMenuHandler::GetMenu();
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
						if (mainGame->isHostingOnline)
							activeMenu = OnlineModeMenuHandler::GetMenu();
						else
							activeMenu = DuelRulesMenuHandler::GetMenu();
						break;
					}
					case BUTTON_HP_AI_TOGGLE: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(216).data());
						activeMenu = AiMenuHandler::GetMenu();
						break;
					}
					case BUTTON_BOT_ADD: {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(217).data());
						activeMenu = DuelRulesMenuHandler::GetMenu();
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
		}
	}

	void MenuEventHandler::CheckMenu() {
		if (ConfigurationMenuHandler::IsActive())
			activeMenu = ConfigurationMenuHandler::GetMenu();
		else if (MainMenuHandler::IsActive())
			activeMenu = MainMenuHandler::GetMenu();
		else if (LanModeMenuHandler::IsActive())
			activeMenu = LanModeMenuHandler::GetMenu();
		else if (AiMenuHandler::IsActive())
			activeMenu = AiMenuHandler::GetMenu();
		else if (PreDuelMenuHandler::IsActive())
			activeMenu = PreDuelMenuHandler::GetMenu();
		else if (OnlineModeMenuHandler::IsActive())
			activeMenu = OnlineModeMenuHandler::GetMenu();
		else if (PreDuelOnlineMenuHandler::IsActive())
			activeMenu = PreDuelOnlineMenuHandler::GetMenu();
		else if (DuelRulesMenuHandler::IsActive())
			activeMenu = DuelRulesMenuHandler::GetMenu();
		else if (PuzzlesMenuHandler::IsActive())
			activeMenu = PuzzlesMenuHandler::GetMenu();
		else if (mainGame->ebRPName->isEnabled() && mainGame->ebRPName->isTrulyVisible())
			menu = menuPassword;
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
}
