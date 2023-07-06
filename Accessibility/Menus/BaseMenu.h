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

		BaseMenu(int activeMenu, std::vector<int> selectedMenu) : _selectedMenu(std::move(selectedMenu)),
		                                                          _currentMenu{activeMenu}
		{
		}

		/**
		 * \brief Simulates an event
		 * \param target graphical element to simulate the event on
		 * \param type type of event to be simulated
		 */
		static void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type);

	public:
		/**
		 * \brief Set the next menu selected after pressing the keys Arrow Right or Arrow Left
		 * \param key can be either Arrow Right or Arrow Left
		 */
		virtual void SetMenu(irr::EKEY_CODE key = irr::EKEY_CODE::KEY_UNKNOWN);

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

	inline void BaseMenu::SetMenu(irr::EKEY_CODE key)
	{
		_typing = false;
		mainGame->env->removeFocus(mainGame->env->getFocus());
		if (_activeMenu != _selectedMenu)
		{
			_activeMenu = _selectedMenu;
			_currentMenuIndex = 0;
		}
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
				_currentMenuIndex = _activeMenu.size() - 1;
		}
		_currentMenu = _activeMenu.at(_currentMenuIndex);
		ReadMenuAndValue();
	}
}

#endif //BASE_MENU_H
