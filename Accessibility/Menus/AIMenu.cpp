#include "AIMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	AiMenuHandler* AiMenuHandler::_menuHandler = nullptr;
	std::vector<int> AiMenuHandler::aiMenu = { MenuType::AIConfigMenu::AIC_OK, MenuType::AIConfigMenu::AIC_SELECT_DECK, MenuType::AIConfigMenu::AIC_ALWAYS_ROCK };

	AiMenuHandler::AiMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* AiMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new AiMenuHandler();
		return _menuHandler;
	}

	bool AiMenuHandler::IsActive()
	{
		bool isActive = false;
		if (mainGame->gBot.btnAdd->isEnabled() && mainGame->gBot.btnAdd->isTrulyVisible())
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

	void AiMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::AIConfigMenu::AIC_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_OK).data();
			else if(_currentMenu == MenuType::AIConfigMenu::AIC_SELECT_DECK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_SELECT_DECK).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
			else if(_currentMenu == MenuType::AIConfigMenu::AIC_ALWAYS_ROCK)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::AIConfigMenu::AIC_ALWAYS_ROCK).data(), mainGame->gBot.chkThrowRock->isChecked());
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void AiMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_DOWN:
			case irr::KEY_UP: {
					if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						if (!event.KeyInput.PressedDown && mainGame->gBot.cbBotDeck->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
							const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
							ScreenReader::getReader()->readScreen(nvdaString);
						}
					}
					break;
			}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					if (_selectedMenu != aiMenu)
						_selectedMenu = aiMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_activeMenu != _selectedMenu)
						SetSelectedMenu();
					if (_currentMenu == MenuType::AIConfigMenu::AIC_OK && mainGame->gBot.btnAdd->isTrulyVisible() && mainGame->gBot.btnAdd->isEnabled()) {
						ClickButton(mainGame->gBot.btnAdd);
					}
					else if (_currentMenu == MenuType::AIConfigMenu::AIC_SELECT_DECK && mainGame->gBot.cbBotDeck->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->gBot.cbBotDeck);
						const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
					}
					else if (_currentMenu == MenuType::AIConfigMenu::AIC_ALWAYS_ROCK && mainGame->gBot.chkThrowRock->isTrulyVisible()) {
						CheckBox(mainGame->gBot.chkThrowRock);
					}
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepWindBot->isEnabled())
						ClickButton(mainGame->btnHostPrepWindBot);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void AiMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		const int id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
			case irr::gui::EGET_COMBO_BOX_CHANGED: {
					switch (id) {
					case COMBOBOX_BOT_DECK: {
						const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->gBot.cbBotDeck->getItem(mainGame->gBot.cbBotDeck->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
						break;
					}
				}
			}
		}
	}
}
