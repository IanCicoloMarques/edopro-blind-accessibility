#ifndef DECK_EDITOR_MENU_HANDLER_H
#define DECK_EDITOR_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class DeckEditorMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> deckEditorMenu;
		DeckEditorMenuHandler(int activeMenu = MenuType::MenuList::PRE_DUEL_ONLINE_MENU, const std::vector<int>&
			                   selectedMenu = deckEditorMenu);
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static DeckEditorMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //DECK_EDITOR_MENU_HANDLER_H
