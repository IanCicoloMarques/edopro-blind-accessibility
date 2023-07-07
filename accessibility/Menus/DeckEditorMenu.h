#ifndef DECK_EDITOR_MENU_HANDLER_H
#define DECK_EDITOR_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"

#include "BaseMenu.h"

namespace ygo {
	class DeckEditorMenuHandler final : public BaseMenu {
	public:
		DeckEditorMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_ONLINE_MENU, const std::vector<int>&
			                   selectedMenu = { Accessibility::Dict::Menu::OK, Accessibility::Dict::Menu::CANCEL });
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static DeckEditorMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //DECK_EDITOR_MENU_HANDLER_H
