#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/FieldFocus/AccessibilityFieldFocus.h"
#include "../accessibility/Control/CardsDTO.h"

namespace ygo {
	class EventHandler : public IEventHandler
	{
	public:
		virtual void PushKey(const irr::SEvent& event) override;
	private:
		bool accessibilityFocus = true; //TODO- FAZER UMA CONFIGURAÇÃO NO MENU PRA ISSO
		bool selectZone = false;
		int cardSelectPosition = 0;
		int indexLookedUpCard = 0;
		AccessibilityFieldFocus::DisplayedField displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
		int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
		int battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		int cardType = AccessibilityFieldFocus::CardType::MONSTER;
		bool CheckIfCanViewCards(irr::SEvent event);
		void DisplayCards(const std::vector<ClientCard*>& field, const std::wstring & = L"");
		void CloseDialog();
		void ShowLocationCard();
		//void ScrollCardList();
		/*void DisplayCards(const std::vector<ChainInfo>& field, const std::wstring & = L"");
		void SetSelectableCards();
		bool UseCard(const AccessibilityFieldFocus::UseType& useType, irr::SEvent event);
		void SelectFieldSlot(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		void SelectFieldSlotNoPlayer(int slot);
		int GetFieldSlot(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		int SearchFieldSlot(const int& displayedField, ClientCard* card = NULL);
		float GetYPosition(int slot = 1);
		float GetXPosition(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		float GetXPosition(const AccessibilityFieldFocus::Scroll& position = AccessibilityFieldFocus::Scroll::RIGHT);
		AccessibilityFieldFocus::DisplayedCards GetCardField();
		void SimulateButton(irr::gui::IGUIElement* caller = nullptr);
		void MouseClick(const irr::SEvent& event, bool rightClick = false);
		void ChangeField(const AccessibilityFieldFocus::CardType& cardField);
		void ChangeFieldByCard();
		void SetMouseOnCard();
		void SetLookUpField();
		void ReadCardName();
		void TriggerOkButton();
		void ChangeFieldAndLook();
		bool CheckIfFieldSlotIsFree(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		std::wstring GetLinkMarks(ClientCard* card);
		std::wstring GetOverlayedCards(ClientCard* card);*/
	};
}

#endif
