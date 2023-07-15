#include "PuzzlesMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	PuzzlesMenuHandler* PuzzlesMenuHandler::_menuHandler = nullptr;
	std::vector<int> PuzzlesMenuHandler::puzzlesMenu = {
		MenuType::PuzzlesMenu::PUZZLES_START, MenuType::PuzzlesMenu::PUZZLES_DELETE,
		MenuType::PuzzlesMenu::PUZZLES_RENAME, MenuType::PuzzlesMenu::PUZZLES_OPEN_FILE
	};

	PuzzlesMenuHandler::PuzzlesMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* PuzzlesMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new PuzzlesMenuHandler();
		return _menuHandler;
	}

	bool PuzzlesMenuHandler::IsActive()
	{
		bool isActive = false;
		if (mainGame->btnSinglePlayCancel->isEnabled() && mainGame->btnSinglePlayCancel->isTrulyVisible())
			isActive = true;
		return isActive;
	}

	void PuzzlesMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::PuzzlesMenu::PUZZLES_START)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PuzzlesMenu::PUZZLES_START).data();
			else if(_currentMenu == MenuType::PuzzlesMenu::PUZZLES_DELETE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PuzzlesMenu::PUZZLES_DELETE).data();
			else if(_currentMenu == MenuType::PuzzlesMenu::PUZZLES_RENAME)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PuzzlesMenu::PUZZLES_RENAME).data();
			else if(_currentMenu == MenuType::PuzzlesMenu::PUZZLES_OPEN_FILE)
				menuValue = gDataManager->GetAccessibilityString(MenuType::PuzzlesMenu::PUZZLES_OPEN_FILE).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	};

	void PuzzlesMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
		case irr::KEY_UP:
		case irr::KEY_DOWN: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->lstSinglePlayList->isTrulyVisible())
						ReadSinglePlayerList();
				}
				break;
		}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					if (_selectedMenu != puzzlesMenu)
						_selectedMenu = puzzlesMenu;
					if(!_scrolling)
						SetMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_activeMenu != _selectedMenu)
						SetMenu();
					if (_currentMenu == MenuType::PuzzlesMenu::PUZZLES_START && mainGame->btnLoadSinglePlay->isTrulyVisible())
						ClickButton(mainGame->btnLoadSinglePlay);
					else if (_currentMenu == MenuType::PuzzlesMenu::PUZZLES_DELETE && mainGame->btnDeleteSinglePlay->isTrulyVisible())
						ClickButton(mainGame->btnDeleteSinglePlay);
					else if (_currentMenu == MenuType::PuzzlesMenu::PUZZLES_RENAME && mainGame->btnRenameSinglePlay->isTrulyVisible())
						ClickButton(mainGame->btnRenameSinglePlay);
					else if (_currentMenu == MenuType::PuzzlesMenu::PUZZLES_OPEN_FILE && mainGame->btnOpenSinglePlay->isTrulyVisible())
						ClickButton(mainGame->btnOpenSinglePlay);

				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnSinglePlayCancel->isTrulyVisible())
						ClickButton(mainGame->btnSinglePlayCancel);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void PuzzlesMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void PuzzlesMenuHandler::ReadSinglePlayerList()
	{
		mainGame->env->setFocus(mainGame->lstSinglePlayList);
		irr::s32 listItem = mainGame->lstSinglePlayList->getSelected();
		if (listItem == -1) {
			listItem = 0;
			mainGame->lstSinglePlayList->setSelected(mainGame->lstSinglePlayList->getListItem(listItem));
		}
		ScreenReader::getReader()->textToSpeech(fmt::format(L"{}", mainGame->lstSinglePlayList->getListItem(listItem)));
	}
}
