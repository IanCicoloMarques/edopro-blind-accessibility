#ifndef DECK_EDITOR_MENU_HANDLER_H
#define DECK_EDITOR_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"
#include "FieldFocus/AccessibilityDeckFocus.h"

namespace ygo {
	class DeckEditorMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> deckEditorMenu;
		static std::vector<int> viewCardsMenu;
		static std::vector<int> deckOptionsMenu;
		static std::vector<int> searchCardMenu;
		DeckEditorMenuHandler(int activeMenu = MenuType::MenuList::DECK_EDITOR, const std::vector<int>& selectedMenu = deckEditorMenu);
		static BaseMenu* GetMenu();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static DeckEditorMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
		void SetStack(AccessibilityDeckFocus::CardStack cardStack);
		void ReadCardInfo();
		void AddOrRemoveCardsFromDeck();
		void SelectCard(irr::EKEY_CODE key);
		void SelectCard(irr::EKEY_CODE key, const Deck::Vector& deck);
		void DeckOptionsMenu();
		void SearchOptionsMenu();
		int	_selectedCardStack = AccessibilityDeckFocus::CardStack::MAIN_DECK;
		int _selectedCardIndex = 0;
		bool _newDeck = false;
	};
}

#endif //DECK_EDITOR_MENU_HANDLER_H
