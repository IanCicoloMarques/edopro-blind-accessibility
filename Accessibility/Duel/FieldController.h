#ifndef FIELD_CONTROLLER_HANDLER_H
#define FIELD_CONTROLLER_HANDLER_H

#include "CardController.h"
#include "FieldSlotController.h"
#include "../gframe/client_card.h"

#include "IEventReceiver.h"

namespace ygo {
	class FieldController{
	public:
		static FieldController* GetFieldController();
		void SetSelectedCardField();
		void SelectFieldSlot(const irr::SEvent& event, int slot, const int& field);
		void ReadFreeSlots(const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE, bool isLink = false);
		int currenField = 0;
	private:
		static FieldController* _fieldController;
		bool IsOnField(const ClientCard* card, const int& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		void SetCursorOnSlot(int slot, const int& field);
		FieldSlotModel* GetSlotPosition(const int& slot, const int& field);
		CardController* _cardController = nullptr;
	};
}

#endif //FIELD_CONTROLLER_HANDLER_H
