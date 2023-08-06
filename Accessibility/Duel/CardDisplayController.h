#ifndef CARD_DISPLAY_CONTROLLER_H
#define CARD_DISPLAY_CONTROLLER_H
#include "FieldFocus/AccessibilityFieldFocus.h"
#include "../gframe/client_card.h"
#include "../gframe/client_field.h"


namespace ygo {
	class CardDisplayController{
	public:
		static CardDisplayController* GetInstance();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);
		void ChangeCurrentCardIndex(irr::EKEY_CODE ekeyCode);
		void ShowCardInfo();
		void TryClickCard();
		ClientCard* GetSelectedCard();
		static void CloseDisplay();
		int currentCardIndex = 0;

	private:
		static CardDisplayController* _cardDisplayController;
		bool CanDisplayCards(irr::SEvent event);
		void DisplayTable(const irr::SEvent& event, AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player);
		void DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text);
		void DisplayCardsReverse(const std::vector<ClientCard*>& field, const std::wstring& text);
		void DisplayChain(const irr::SEvent& event);
		void DisplayMonsterField(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplaySpellField(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplayExtraDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplayDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplayHand(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplaySpecialSummonableMonsters(const irr::SEvent& event);
		void DisplayGraveyard(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplayRemovedCards(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field);
		void DisplayActivableCards(const irr::SEvent& event);
		void DisplaySelectableCards(const irr::SEvent& event);
		void DisplaySelectableCards(const std::vector<ClientCard*>& field, const std::wstring& text = L"");
		void DisplayCards(const std::vector<ChainInfo>& field);
		void ShowSelectCard();
		void ScrollDisplay(unsigned initialIndex, irr::EKEY_CODE ekeyCode);
	};
}

#endif //CARD_DISPLAY_CONTROLLER_H
