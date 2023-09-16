#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include "Models/FieldSlotModel.h"
#include "CardController.h"
#include "../gframe/client_card.h"
#include "../Control/IEventHandler.h"


namespace ygo {
	class FieldController : IEventHandler{
	public:
		FieldController();
		static IEventHandler* GetInstance();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
		bool HasEventKey(irr::EKEY_CODE key) override;
		void RotateField();
		void ChangeFocusedPlayerField(AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::MAIN_PLAYER);

		void SetSelectedCardField();
		void SelectFieldSlot(const irr::SEvent& event, int slot, AccessibilityFieldFocus::Field field);
		void SetMousePositionOnCardOnFieldOrHand(ClientCard* card);
		void SetMousePositionOnSlot(AccessibilityFieldFocus::Field field, int slot = 0);
		AccessibilityFieldFocus::DisplayedCards GetField();
		FieldSlotModel* GetFieldSlotModel(bool recursion = false, AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::MAIN_PLAYER);
		FieldSlotModel* GetMonsterSpellSlotModel(AccessibilityFieldFocus::Player player);
		void ReadFreeSlots(const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::MAIN_PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE, bool isLink = false);
		AccessibilityFieldFocus::Field currentField = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		AccessibilityFieldFocus::Player currentPlayer = AccessibilityFieldFocus::Player::MAIN_PLAYER;
	private:
		static IEventHandler* _fieldController;
		CardController* _cardController = nullptr;
		bool IsOnField(ClientCard* card, const int& player = AccessibilityFieldFocus::Player::MAIN_PLAYER);
		bool IsInGraveyard(ClientCard* clientCard, AccessibilityFieldFocus::Player player);
		bool IsInExtraDeck(ClientCard* clientCard, AccessibilityFieldFocus::Player player);
		bool IsRemoved(ClientCard* clientCard, AccessibilityFieldFocus::Player player);
		bool IsInDeck(ClientCard* clientCard, AccessibilityFieldFocus::Player player);
		void ChangeField(const AccessibilityFieldFocus::Field& field);

	};
}

#endif //FIELD_CONTROLLER_H
