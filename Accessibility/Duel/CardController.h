#ifndef CARD_CONTROLLER_HANDLER_H
#define CARD_CONTROLLER_HANDLER_H

#include "Control/IEventHandler.h"
#include "../gframe/client_card.h"
#include "FieldFocus/AccessibilityFieldFocus.h"

namespace ygo {
	class CardController : IEventHandler{
	public:
		CardController();
		static IEventHandler* GetInstance();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);
		bool HasEventKey(irr::EKEY_CODE key) override;

		void SetCard(ClientCard* card);
		void ReadCardInfo();
		void ReadCardBasicInfo();
		void ShowCardOptions(int x = 0, int y = 0);
		void ReadAvailableCommands();

		ClientCard* GetSelectedCard();
		void SetCardType(AccessibilityFieldFocus::CardType type);
		AccessibilityFieldFocus::Field GetCardLocation(const ClientCard* card);
		bool isSelected = false;
	private:
		static IEventHandler* _cardController;
		ClientCard* _selectedCard;
		int _cardType = AccessibilityFieldFocus::CardType::MONSTER;
	};
}

#endif //CARD_CONTROLLER_HANDLER_H
