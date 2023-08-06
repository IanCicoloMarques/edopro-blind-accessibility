#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include "Models/FieldSlotModel.h"
#include "CardController.h"
#include "../gframe/client_card.h"
#include "../Control/IEventHandler.h"


namespace ygo {
	class FieldController{
	public:
		static FieldController* GetInstance();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);

		void SetSelectedCardField();
		void SelectFieldSlot(const irr::SEvent& event, int slot, AccessibilityFieldFocus::Field field);
		void SetMousePositionOnCardOnFieldOrHand(ClientCard* card);
		AccessibilityFieldFocus::DisplayedCards GetField();
		FieldSlotModel* GetFieldSlotModel(bool recursion = false, AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::PLAYER);
		void ReadFreeSlots(const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE, bool isLink = false);
		AccessibilityFieldFocus::Field currentField = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
		AccessibilityFieldFocus::Player currentPlayer = AccessibilityFieldFocus::Player::PLAYER;
	private:
		static FieldController* _fieldController;
		bool IsOnField(const ClientCard* card, const int& player = AccessibilityFieldFocus::Player::PLAYER);

	private:
		CardController* _cardController = nullptr;
	};
}

#endif //FIELD_CONTROLLER_H
