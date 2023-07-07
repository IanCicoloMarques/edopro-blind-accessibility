#include "DeckEditorMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	DeckEditorMenuHandler* DeckEditorMenuHandler::_menuHandler = nullptr;

	DeckEditorMenuHandler::DeckEditorMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* DeckEditorMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new DeckEditorMenuHandler();
		return _menuHandler;
	}

	void DeckEditorMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == Accessibility::Dict::Menu::OK)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::OK).data();
			else if(_currentMenu == Accessibility::Dict::Menu::CANCEL)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::CANCEL).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void DeckEditorMenuHandler::KeyInputEvent(const irr::SEvent& event)
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
					if (_currentMenu == MenuType::PlayerDuel::PD_START_DUEL && mainGame->btnHostPrepStart->isEnabled())
						ClickButton(mainGame->btnHostPrepStart);
					else if (_currentMenu == MenuType::PlayerDuel::PD_START_DUEL && !mainGame->btnHostPrepStart->isEnabled() && mainGame->btnHostPrepStart->isTrulyVisible()) {
						std::wstring nvdaString;
						if (_previousMenu == MenuType::MainMenu::MM_SP_DUEL)
							nvdaString = gDataManager->GetAccessibilityString(227).data();
						else
							nvdaString = gDataManager->GetAccessibilityString(228).data();
						ScreenReader::getReader()->readScreen(nvdaString);
					}
					else if (_currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepReady->isTrulyVisible() && mainGame->btnHostPrepReady->isEnabled())
						ClickButton(mainGame->btnHostPrepReady);
					else if (_currentMenu == MenuType::PlayerDuel::PD_PLAYER_READY && mainGame->btnHostPrepNotReady->isEnabled())
						ClickButton(mainGame->btnHostPrepNotReady);
					else if (_currentMenu == MenuType::PlayerDuel::PD_SELECT_DECK && mainGame->cbDeckSelect->isTrulyVisible()) {
						mainGame->env->setFocus(mainGame->cbDeckSelect);
						const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(192).data(), mainGame->cbDeckSelect->getItem(mainGame->cbDeckSelect->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString);
					}
					else if (_currentMenu == MenuType::SinglePlayerDuel::SP_AI_MENU && mainGame->btnHostPrepWindBot->isTrulyVisible() && mainGame->btnHostPrepWindBot->isEnabled())
						ClickButton(mainGame->btnHostPrepWindBot);
					else if (_currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && mainGame->btnHostPrepDuelist->isEnabled())
						ClickButton(mainGame->btnHostPrepDuelist);
					else if (_currentMenu == MenuType::OnlineDuel::OD_DUEL_MODE && mainGame->btnHostPrepDuelist->isTrulyVisible() && !mainGame->btnHostPrepDuelist->isEnabled())
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(229).data());
					else if (_currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && mainGame->btnHostPrepOB->isEnabled())
						ClickButton(mainGame->btnHostPrepOB);
					else if (_currentMenu == MenuType::OnlineDuel::OD_SPECTATE_MODE && mainGame->btnHostPrepOB->isTrulyVisible() && !mainGame->btnHostPrepOB->isEnabled())
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(230).data());
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
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void DeckEditorMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
}
