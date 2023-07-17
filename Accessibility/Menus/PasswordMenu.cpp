#include "PasswordMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	PasswordMenuHandler* PasswordMenuHandler::_menuHandler = nullptr;
	std::vector<int> PasswordMenuHandler::passwordMenu = { MenuType::PasswordMenu::PASS_SET_PASSWORD, MenuType::PasswordMenu::PASS_OK, MenuType::PasswordMenu::PASS_CANCEL };

	PasswordMenuHandler::PasswordMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* PasswordMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new PasswordMenuHandler();
		return _menuHandler;
	}

	bool PasswordMenuHandler::IsActive()
	{
		bool isActive = false;
		if (mainGame->ebRPName->isEnabled() && mainGame->ebRPName->isTrulyVisible())
			isActive = true;
		return isActive;
	}

	void PasswordMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::PasswordMenu::PASS_SET_PASSWORD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_SET_PASSWORD).data(), mainGame->ebRPName->getText());
			else if(_currentMenu == MenuType::PasswordMenu::PASS_OK)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_OK).data();
			else if(_currentMenu == MenuType::PasswordMenu::PASS_CANCEL)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PasswordMenu::PASS_CANCEL).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void PasswordMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_I: {
					if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
						//TODO - Dar infomações sobre o menu
					}
					break;
			}
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
					if (_selectedMenu != passwordMenu)
						_selectedMenu = passwordMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_activeMenu != _selectedMenu)
						SetSelectedMenu();
					if (_currentMenu == MenuType::PasswordMenu::PASS_SET_PASSWORD && mainGame->ebRPName->isTrulyVisible()) {
						if (!_typing) {
							ScreenReader::getReader()->readScreen(std::wstring(gDataManager->GetAccessibilityString(223).data()));
							FocusTextBox(mainGame->ebRPName);
							_typing = true;
						}
						else {
							_typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(224).data(), mainGame->ebRPName->getText()));
						}
					}
					else if (_currentMenu == MenuType::PasswordMenu::PASS_OK && mainGame->btnRPYes->isEnabled()) {
						ClickButton(mainGame->btnRPYes);
					}
					else if (_currentMenu == MenuType::PasswordMenu::PASS_CANCEL && mainGame->btnRPNo->isEnabled()) {
						ClickButton(mainGame->btnRPNo);
					}
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnRPNo->isTrulyVisible() && mainGame->btnRPNo->isEnabled())
						ClickButton(mainGame->btnRPNo);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void PasswordMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
}
