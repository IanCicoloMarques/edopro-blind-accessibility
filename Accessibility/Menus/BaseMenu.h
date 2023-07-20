#ifndef BASE_MENU_H
#define BASE_MENU_H

#include <vector>
#include "../gframe/game.h"
#include "../accessibility/Control/IEventHandler.h"
#include <IGUIWindow.h>
#include <IGUIEditBox.h>
#include <IrrlichtDevice.h>



namespace ygo {
	class BaseMenu : public IEventHandler {

		/**
		 * \brief Simulates an event
		 * \param target graphical element to simulate the event on
		 * \param type type of event to be simulated
		 */
		static void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type);

	public:

		BaseMenu(int activeMenu, std::vector<int> selectedMenu) : _selectedMenu(std::move(selectedMenu)),
																  _currentMenu{activeMenu}
		{
		}

		/**
		 * \brief Check if the current menu is in the list of selected menus
		 * \return True or false
		 */
		bool MenuInRange();

		/**
		 * \brief Set the next menu selected after pressing the keys Arrow Right or Arrow Left
		 * \param key can be either Arrow Right or Arrow Left
		 */
		virtual void SetSelectedMenu(irr::EKEY_CODE key = irr::EKEY_CODE::KEY_UNKNOWN);

		/**
		 * \brief Set the active menu
		 */
		virtual void SetMenu();

		/**
		 * \brief Reads, using text-to-speech, the current menu name and value
		 */
		virtual void ReadMenuAndValue() = 0;

		/**
		 * \brief Simulates a button click
		 * \param btn the button to be clicked
		 */
		static void ClickButton(irr::gui::IGUIElement* btn) {
			TriggerEvent(btn, irr::gui::EGET_BUTTON_CLICKED);
		}

		/**
		 * \brief Focus on a text box so the user can type
		 * \param editBox the text box to be focused
		 */
		static void FocusTextBox(irr::gui::IGUIEditBox* editBox) {
			if (editBox->isTrulyVisible()) {
				editBox->setText(L"");
				mainGame->env->setFocus(editBox);
			}
		}

	protected:
		/**
		 * \brief Tells if the player is typing, so he can't navigate through the menu with the shotcuts
		 */
		bool _typing = false;


		/**
		 * \brief Tells if the player is using a scroll menu (to select the volume, for example)
		 */
		bool _scrolling = false;

		/**
		 * \brief Has a list of the active menu options
		 */
		std::vector<int> _activeMenu;

		/**
		 * \brief Has a list of the selected menu options
		 */
		std::vector<int> _selectedMenu;

		/**
		 * \brief Counter to know which menu option is currently selected
		 */
		int _currentMenuIndex = 0;

		/**
		 * \brief Code of the current menu option selected
		 */
		int _currentMenu = 0;

		/**
		 * \brief The code of the previous selected menu
		 */
		int _previousMenu;
	};

	inline void BaseMenu::TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type)
	{
		irr::SEvent event{};
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		ygo::mainGame->device->postEventFromUser(event);
	}

	inline bool BaseMenu::MenuInRange()
	{
		if(_activeMenu.empty() || _currentMenuIndex >= _activeMenu.size() || _currentMenuIndex < 0)
			return false;
		return true;
	}

	inline void BaseMenu::SetSelectedMenu(irr::EKEY_CODE key)
	{
		SetMenu();
		if(key == irr::KEY_RIGHT)
		{
			_currentMenuIndex++;
			if (_currentMenuIndex >= _activeMenu.size())
				_currentMenuIndex = 0;
		}
		else if(key == irr::KEY_LEFT)
		{
			_currentMenuIndex--;
			if (_currentMenuIndex < 0)
				_currentMenuIndex = 0;
		}
		if(MenuInRange())
			_currentMenu = _activeMenu.at(_currentMenuIndex);
		ReadMenuAndValue();
	}

	inline void BaseMenu::SetMenu()
	{
		_typing = false;
		mainGame->env->removeFocus(mainGame->env->getFocus());
		if (_activeMenu != _selectedMenu)
		{
			_activeMenu = _selectedMenu;
			_currentMenuIndex = 0;
			if(MenuInRange())
				_currentMenu = _activeMenu.at(_currentMenuIndex);
		}
	}
}

#endif //BASE_MENU_H
