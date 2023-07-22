#include "FieldController.h"

#include "field.h"
#include "FieldSlotController.h"
#include "Helper/MouseHelper.h"
#include "Models/CardModel.h"
#include "ScreenReader/ScreenReader.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"
#include "../gframe/data_manager.h"

namespace ygo {
	FieldController* FieldController::_fieldController = nullptr;
	FieldController* FieldController::GetInstance()
	{
		if (_fieldController == nullptr)
			_fieldController = new FieldController();
		return _fieldController;
	}

	void FieldController::SetSelectedCardField()
	{
		_cardController = CardController::GetInstance();
		const ClientCard* card = _cardController->GetSelectedCard();
		if (!_cardController->GetSelectedCard())
			return;

		const bool foundCard = IsOnField(card);

		if (!foundCard) {
			const auto cardData = new CardModel(_cardController->GetSelectedCard());
			const int cardType = cardData->GetCardType();
			if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
				currentField = AccessibilityFieldFocus::PLAYER_MONSTERS;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			}
			else {
				currentField = AccessibilityFieldFocus::PLAYER_SPELLS;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
			}
		}
	}

	void FieldController::KeyInputEvent(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == irr::KEY_KEY_1 || event.KeyInput.Key == irr::KEY_NUMPAD1)
			SelectFieldSlot(event, 1, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_2 || event.KeyInput.Key == irr::KEY_NUMPAD2)
			SelectFieldSlot(event, 2, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_3 || event.KeyInput.Key == irr::KEY_NUMPAD3)
			SelectFieldSlot(event, 3, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_4 || event.KeyInput.Key == irr::KEY_NUMPAD4)
			SelectFieldSlot(event, 4, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_5 || event.KeyInput.Key == irr::KEY_NUMPAD5)
			SelectFieldSlot(event, 5, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_6 || event.KeyInput.Key == irr::KEY_NUMPAD6)
			SelectFieldSlot(event, 6, currentField);
		else if(event.KeyInput.Key == irr::KEY_KEY_7 || event.KeyInput.Key == irr::KEY_NUMPAD7)
			SelectFieldSlot(event, 7, currentField);
	}

	void FieldController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void FieldController::SelectFieldSlot(const irr::SEvent& event, int slot, const int& field)
	{
		if (slot == 0) slot = 1;
		const FieldSlotModel* fieldSlot = FieldSlotController::GetInstance()->GetFieldSlotData(slot, field);
		MouseHelper::SetCursorPosition(fieldSlot->xPosition, fieldSlot->yPosition);
		MouseHelper::Click(event);
	}

	void FieldController::SetMousePositionOnCardOnFieldOrHand()
	{
		CardController::GetInstance()->SetCard(mainGame->dField.clicked_card);
		if (GetField() == AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND)
			MouseHelper::SetCursorPosition(CardController::GetInstance()->GetSelectedCard());
		else {
			const FieldSlotModel* fieldSlot = GetFieldSlotModel();
			MouseHelper::SetCursorPosition(fieldSlot->xPosition, fieldSlot->yPosition);
		}
	}

	AccessibilityFieldFocus::DisplayedCards FieldController::GetField() {
		CardController::GetInstance();
		for (int i = 0; i < mainGame->dField.hand[0].size(); i++) {
			if (mainGame->dField.hand[0].size() > i && mainGame->dField.hand[0][i] == CardController::GetInstance()->GetSelectedCard())
				return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
			if (mainGame->dField.hand[1].size() > i && mainGame->dField.hand[1][i] == CardController::GetInstance()->GetSelectedCard())
				return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
		}
		return AccessibilityFieldFocus::DisplayedCards::DISPLAY_FIELD;
	}

	void FieldController::ReadFreeSlots(const AccessibilityFieldFocus::Player& player, const int& cardType, const bool isLink)
	{
		constexpr int maxCommonSlots = 5;
		std::wstring freeSlots = ygo::gDataManager->GetAccessibilityString(Accessibility::Dict::Duel::FREE_SLOTS).data();
		if(cardType == AccessibilityFieldFocus::CardType::MONSTER)
		{
			int slot = 1;

			for (const auto clientCard : mainGame->dField.mzone[player])
			{
				constexpr int maxMonsterSlots = 7;
				//TODO - FAZER VALIDAÇÃO DE SLOTS QUE PODEM TER LINKS
				if(clientCard == nullptr && slot <= maxCommonSlots && !isLink)
					freeSlots += fmt::format(L"{},", slot);
				else if(clientCard == nullptr && slot > maxCommonSlots && isLink)
					freeSlots += fmt::format(L"Link {},", slot - maxCommonSlots);
				slot++;
				if(slot > maxMonsterSlots)
					break;
			}
		}
		else if (cardType == AccessibilityFieldFocus::CardType::SPELL)
		{
			int slot = 1;
			for (const auto clientCard : mainGame->dField.szone[player])
			{
				if (clientCard == nullptr)
					freeSlots += fmt::format(L"{},", slot);
				slot++;
				if(slot > maxCommonSlots)
					break;
			}
		}
		if(!freeSlots.empty())
			ScreenReader::getReader()->readScreen(freeSlots, false);
	}

	bool FieldController::IsOnField(const ClientCard* card, const int& player)
	{
		_cardController = CardController::GetInstance();
		for (int i = 0; i < 6; i++) {
			if (mainGame->dField.mzone[player][i] && mainGame->dField.mzone[player][i] == card) {
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
				_cardController->isSelected = true;
				currentField = AccessibilityFieldFocus::PLAYER_MONSTERS;
				return true;
			}
			if (mainGame->dField.szone[player][i] && mainGame->dField.szone[player][i] == card) {
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
				_cardController->isSelected = true;
				currentField = AccessibilityFieldFocus::PLAYER_SPELLS;
				return true;
			}
		}
		return false;
	}

	FieldSlotModel* FieldController::GetFieldSlotModel(const bool recursion) {
		FieldSlotModel* fieldSlotModel = nullptr;
		int fieldSlot = 0;
		//Busca a carta no campo selecionado;
		if (currentField != AccessibilityFieldFocus::PLAYER_GRAVEYARD &&
			currentField != AccessibilityFieldFocus::PLAYER_EXTRA_DECK &&
			currentField != AccessibilityFieldFocus::PLAYER_BANNED_CARDS) {
			for (int i = 0; i < 7; i++) {
				if ((mainGame->dField.mzone[currentPlayer][i] && mainGame->dField.mzone[currentPlayer][i] == CardController::GetInstance()->GetSelectedCard()) ||
					(mainGame->dField.szone[currentPlayer][i] && mainGame->dField.szone[currentPlayer][i] == CardController::GetInstance()->GetSelectedCard())) {
					if (i < 5)
						fieldSlot = i + 1;
					else
						currentField = AccessibilityFieldFocus::Field::LINK_ZONE;
					break;
				}
			}
		}
		//Caso não encontre a carta, busca no outro campo;
		if (fieldSlot == 0 && !recursion) {
			currentPlayer = currentPlayer == AccessibilityFieldFocus::Player::PLAYER ? AccessibilityFieldFocus::Player::ENEMY_PLAYER : AccessibilityFieldFocus::Player::PLAYER;
			fieldSlotModel = GetFieldSlotModel(true);
		}
		else if(fieldSlot != 0)
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(fieldSlot, currentField);
		return fieldSlotModel;
	}
}
