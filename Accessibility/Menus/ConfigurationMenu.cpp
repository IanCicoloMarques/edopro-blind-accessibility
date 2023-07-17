#include "ConfigurationMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

namespace ygo {
	ConfigurationMenuHandler* ConfigurationMenuHandler::_menuHandler = nullptr;
	std::vector<int> ConfigurationMenuHandler::configurationMenu = {
		MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS, MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME,
		MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC, MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME,
		MenuType::GameOptionsMenu::USE_MUD_KEYBOARD
	};

	ConfigurationMenuHandler::ConfigurationMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* ConfigurationMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new ConfigurationMenuHandler();
		return _menuHandler;
	}

	bool ConfigurationMenuHandler::IsActive()
	{
		if (mainGame->gSettings.window->isTrulyVisible())
			return true;
		return false;
	};


	static void CheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (chkbox->isTrulyVisible()) {
			if (chkbox->isChecked())
				gSoundManager->PlaySoundEffect(SoundManager::SFX::UNCONFIRM);
			else
				gSoundManager->PlaySoundEffect(SoundManager::SFX::CONFIRM);
			chkbox->setChecked(!chkbox->isChecked());
		}
	}

	void ConfigurationMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS).data(), mainGame->gSettings.chkEnableSound->isChecked());
			else if(_currentMenu == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME).data(), gGameConfig->soundVolume);
			else if(_currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC).data(), mainGame->gSettings.chkEnableMusic->isChecked());
			else if(_currentMenu == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME).data(), gGameConfig->musicVolume);
			else if(_currentMenu == MenuType::GameOptionsMenu::USE_MUD_KEYBOARD)
				menuValue = fmt::format(L"{}: {}", gDataManager->GetAccessibilityString(MenuType::GameOptionsMenu::USE_MUD_KEYBOARD).data(), mainGame->gSettings.chkUseMudKeyboard->isChecked());
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	}

	void ConfigurationMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				{
					if (_selectedMenu != configurationMenu)
						_selectedMenu = configurationMenu;
					if(!_scrolling)
						SetSelectedMenu(event.KeyInput.Key);
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (_activeMenu != _selectedMenu)
						SetSelectedMenu();
					if (_currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_SOUND_EFFECTS && mainGame->gSettings.chkEnableSound->isTrulyVisible()) {
						CheckBox(mainGame->gSettings.chkEnableSound);
						gSoundManager->EnableSounds(mainGame->gSettings.chkEnableSound->isChecked());
						gGameConfig->enablesound = mainGame->gSettings.chkEnableSound->isChecked();
						ReadMenuAndValue();
					}
					else if (_currentMenu == MenuType::GameOptionsMenu::GAMEOP_SOUND_EFFECTS_VOLUME && mainGame->gSettings.scrSoundVolume->isTrulyVisible()) {
						if (!_scrolling) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
							mainGame->env->setFocus(mainGame->gSettings.scrSoundVolume);
							_scrolling = true;
						}
						else {
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(252).data(), gGameConfig->soundVolume));
							_scrolling = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
						}
					}
					else if (_currentMenu == MenuType::GameOptionsMenu::GAMEOP_ENABLE_MUSIC && mainGame->gSettings.chkEnableMusic->isTrulyVisible()) {
						CheckBox(mainGame->gSettings.chkEnableMusic);
						gSoundManager->EnableMusic(mainGame->gSettings.chkEnableMusic->isChecked());
						gGameConfig->enablemusic = mainGame->gSettings.chkEnableMusic->isChecked();
						ReadMenuAndValue();
					}
					else if (_currentMenu == MenuType::GameOptionsMenu::GAMEOP_MUSIC_VOLUME && mainGame->gSettings.scrMusicVolume->isTrulyVisible()) {
						if (!_scrolling) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(11).data());
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityTipsString(12).data());
							mainGame->env->setFocus(mainGame->gSettings.scrMusicVolume);
							_scrolling = true;
						}
						else {
							ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(252).data(), gGameConfig->musicVolume));
							_scrolling = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
						}
					}
					else if (_currentMenu == MenuType::GameOptionsMenu::USE_MUD_KEYBOARD && mainGame->gSettings.chkUseMudKeyboard->isTrulyVisible()) {
						CheckBox(mainGame->gSettings.chkUseMudKeyboard);
						gGameConfig->mudKeyboard = mainGame->gSettings.chkUseMudKeyboard->isChecked();
						EventHandler::mudConfiguration = mainGame->gSettings.chkUseMudKeyboard->isChecked();
						ReadMenuAndValue();
					}
				}
				break;
			}
			case irr::KEY_KEY_0: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->gSettings.window->isTrulyVisible())
						mainGame->HideElement(mainGame->gSettings.window);
					if (_selectedMenu.empty())
						_selectedMenu = _activeMenu;
					else
						_currentMenu = _selectedMenu.at(_currentMenuIndex);
				}

				break;
			}
		}
	}

	void ConfigurationMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
}
