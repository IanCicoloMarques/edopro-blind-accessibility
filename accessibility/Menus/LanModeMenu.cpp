#include "LanModeMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	LanModeMenuHandler* LanModeMenuHandler::_menuHandler = nullptr;

	LanModeMenuHandler::LanModeMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* LanModeMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new LanModeMenuHandler();
		return _menuHandler;
	}

	void LanModeMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::SinglePlayerMenu::SP_HOST)
				menuValue = gDataManager->GetAccessibilityString(MenuType::SinglePlayerMenu::SP_HOST).data();
			else if(_currentMenu == MenuType::SinglePlayerMenu::SP_PLAYER_NAME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::SinglePlayerMenu::SP_PLAYER_NAME).data(), mainGame->ebNickName->getText());
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void LanModeMenuHandler::KeyInputEvent(const irr::SEvent& event)
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
					if (_activeMenu != _selectedMenu)
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
					if (_selectedMenu.empty())
						_selectedMenu = _selectedMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void LanModeMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
}
