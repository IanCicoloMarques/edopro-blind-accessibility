#ifndef CARD_CONTROLLER_HANDLER_H
#define CARD_CONTROLLER_HANDLER_H

#include "Control/IEventHandler.h"
#include "../gframe/client_card.h"
#include "FieldFocus/AccessibilityFieldFocus.h"

namespace ygo {
	class CardController{
	public:
		static CardController* GetInstance();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);

		void SetCard(ClientCard* card);
		void ReadCardInfo();
		void ReadCardBasicInfo();
		void ShowCardOptions(int x = 0, int y = 0);
		void ReadAvailableCommands();
		ClientCard* GetSelectedCard();
		void SetCardType(AccessibilityFieldFocus::CardType type);
		bool isSelected = false;
	private:
		static CardController* _cardController;
		ClientCard* _selectedCard = nullptr;
		int _cardType = AccessibilityFieldFocus::CardType::MONSTER;
	};
}

#endif //CARD_CONTROLLER_HANDLER_H
