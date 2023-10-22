#include "FieldController.h"

#include "CardDisplayController.h"
#include "field.h"
#include "FieldSlotController.h"
#include "Helper/MouseHelper.h"
#include "Models/CardModel.h"
#include "ScreenReader/ScreenReader.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"
#include "../gframe/data_manager.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"

namespace ygo {
	IEventHandler* FieldController::_fieldController = nullptr;

	FieldController::FieldController()
	{
		_cardController = static_cast<CardController *>(CardController::GetInstance());
		currentField = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		currentPlayer = AccessibilityFieldFocus::Player::MAIN_PLAYER;
	}

	IEventHandler* FieldController::GetInstance()
	{
		if (_fieldController == nullptr)
			_fieldController = new FieldController();
		return _fieldController;
	}

	void FieldController::SetSelectedCardField()
	{
		ClientCard* card = _cardController->GetSelectedCard();
		if (!_cardController->GetSelectedCard())
			return;

		const bool foundCard = IsOnField(card);

		if (!foundCard) {
			const auto cardData = new CardModel(_cardController->GetSelectedCard());
			const int cardType = cardData->GetCardType();
			if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
				currentField = AccessibilityFieldFocus::MONSTER_ZONE;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			}
			else {
				currentField = AccessibilityFieldFocus::SPELL_ZONE;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
			}
		}
	}

	void FieldController::KeyInputEvent(const irr::SEvent& event)
	{
		if(_cardController == nullptr)
			_cardController = static_cast<CardController *>(CardController::GetInstance());
		if(event.KeyInput.Key == KeyboardConfiguration::RotateField)
			RotateField();
		else if(event.KeyInput.Key == irr::KEY_KEY_1 || event.KeyInput.Key == irr::KEY_NUMPAD1)
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

	bool FieldController::HasEventKey(irr::EKEY_CODE key)
	{
		std::vector<int> keys = {
			irr::KEY_KEY_1, irr::KEY_NUMPAD1, irr::KEY_KEY_2, irr::KEY_NUMPAD2,irr::KEY_KEY_3, irr::KEY_NUMPAD3, irr::KEY_KEY_4, irr::KEY_NUMPAD4,
			irr::KEY_KEY_5, irr::KEY_NUMPAD5, irr::KEY_KEY_6, irr::KEY_NUMPAD6,irr::KEY_KEY_7, irr::KEY_NUMPAD7, KeyboardConfiguration::RotateField
		};
		if(std::find(keys.begin(), keys.end(), key) != keys.end())
			return true;
		return false;
	}

	void FieldController::RotateField()
	{
		if (currentField != AccessibilityFieldFocus::Field::MONSTER_ZONE && currentField != AccessibilityFieldFocus::Field::SPELL_ZONE)
			ChangeField(AccessibilityFieldFocus::Field::MONSTER_ZONE);
		else if (currentField == AccessibilityFieldFocus::Field::MONSTER_ZONE)
			ChangeField(AccessibilityFieldFocus::Field::SPELL_ZONE);
		else if (currentField == AccessibilityFieldFocus::Field::SPELL_ZONE)
			ChangeField(AccessibilityFieldFocus::Field::LINK_ZONE);
	}

	void FieldController::ChangeFocusedPlayerField()
	{
		if(currentPlayer == AccessibilityFieldFocus::Player::MAIN_PLAYER)
			currentPlayer = AccessibilityFieldFocus::Player::ENEMY_PLAYER;
		else if(currentPlayer == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			currentPlayer = AccessibilityFieldFocus::Player::MAIN_PLAYER;
	}

	void FieldController::ChangeFocusedPlayerField(AccessibilityFieldFocus::Player player)
	{
		if(player == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			currentPlayer = AccessibilityFieldFocus::Player::ENEMY_PLAYER;
		else if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
			currentPlayer = AccessibilityFieldFocus::Player::MAIN_PLAYER;
	}

	void FieldController::ChangeField(const AccessibilityFieldFocus::Field& field) {
		std::wstring nvdaString;
		currentField = field;
		if (currentField == AccessibilityFieldFocus::Field::LINK_ZONE)
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(144).data());
		else if (currentField == AccessibilityFieldFocus::Field::MONSTER_ZONE)
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(145).data());
		else if (currentField == AccessibilityFieldFocus::Field::SPELL_ZONE)
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(146).data());
		ScreenReader::getReader()->readScreen(nvdaString);
	}

	void FieldController::SelectFieldSlot(const irr::SEvent& event, int slot, AccessibilityFieldFocus::Field field)
	{
		if (slot == 0) slot = 1;
		const FieldSlotModel* fieldSlot = FieldSlotController::GetInstance()->GetFieldSlotData(slot, field);
		MouseHelper::SetCursorPosition(fieldSlot->xPosition, fieldSlot->yPosition);
		MouseHelper::Click(event);
	}

	void FieldController::SetMousePositionOnCardOnFieldOrHand(ClientCard* card)
	{
		_cardController->SetCard(card);
		if (GetField() == AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND)
			MouseHelper::SetCursorPosition(_cardController->GetSelectedCard());
		else {
			const FieldSlotModel* fieldSlot = GetFieldSlotModel();
			MouseHelper::SetCursorPosition(fieldSlot->xPosition, fieldSlot->yPosition);
		}
	}

	void FieldController::SetMousePositionOnSlot(AccessibilityFieldFocus::Field field, int slot)
	{
		const FieldSlotModel* fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(slot, field);
		MouseHelper::SetCursorPosition(fieldSlotModel->xPosition, fieldSlotModel->yPosition);
	}

	AccessibilityFieldFocus::DisplayedCards FieldController::GetField() {
		for (int i = 0; i < mainGame->dField.hand[0].size(); i++) {
			if (mainGame->dField.hand[0].size() > i && mainGame->dField.hand[0][i] == _cardController->GetSelectedCard())
				return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
			if (mainGame->dField.hand[1].size() > i && mainGame->dField.hand[1][i] == _cardController->GetSelectedCard())
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

	bool FieldController::IsOnField(ClientCard* card, const int& player)
	{
		if(std::find(mainGame->dField.mzone[player].begin(), mainGame->dField.mzone[player].end(), card) != mainGame->dField.mzone[player].end())
		{
			_cardController->SetCard(card);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::MONSTER_ZONE;
			return true;
		}
		else if(std::find(mainGame->dField.szone[player].begin(), mainGame->dField.szone[player].end(), card) != mainGame->dField.szone[player].end())
		{
			_cardController->SetCard(card);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::SPELL_ZONE;
			return true;
		}
		return false;
	}

	bool FieldController::IsInGraveyard(ClientCard* clientCard, AccessibilityFieldFocus::Player player)
	{
		if(std::find(mainGame->dField.grave[player].begin(), mainGame->dField.grave[player].end(), clientCard) != mainGame->dField.grave[player].end())
		{
			_cardController->SetCard(clientCard);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::GRAVEYARD_ZONE;
			return true;
		}
		return false;
	}

	bool FieldController::IsInExtraDeck(ClientCard* clientCard, AccessibilityFieldFocus::Player player)
	{
		if(std::find(mainGame->dField.extra[player].begin(), mainGame->dField.extra[player].end(), clientCard) != mainGame->dField.extra[player].end())
		{
			_cardController->SetCard(clientCard);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::EXTRA_DECK_ZONE;
			return true;
		}
		return false;
	}

	bool FieldController::IsRemoved(ClientCard* clientCard, AccessibilityFieldFocus::Player player)
	{
		if(std::find(mainGame->dField.remove[player].begin(), mainGame->dField.remove[player].end(), clientCard) != mainGame->dField.remove[player].end())
		{
			_cardController->SetCard(clientCard);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::REMOVED_CARDS_ZONE;
			return true;
		}
		return false;
	}

	bool FieldController::IsInDeck(ClientCard* clientCard, AccessibilityFieldFocus::Player player)
	{
		if(std::find(mainGame->dField.deck[player].begin(), mainGame->dField.deck[player].end(), clientCard) != mainGame->dField.deck[player].end())
		{
			_cardController->SetCard(clientCard);
			_cardController->SetCardType(AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
			_cardController->isSelected = true;
			currentField = AccessibilityFieldFocus::DECK_ZONE;
			return true;
		}
		return false;
	}

	FieldSlotModel* FieldController::GetFieldSlotModel(const bool recursion, AccessibilityFieldFocus::Player player) {
		FieldSlotModel* fieldSlotModel = nullptr;
		if(IsOnField(_cardController->GetSelectedCard(), player))
			fieldSlotModel = GetMonsterSpellSlotModel(player);
		if(IsInGraveyard(_cardController->GetSelectedCard(), player))
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(0,AccessibilityFieldFocus::Field::GRAVEYARD_ZONE);
		if(IsInExtraDeck(_cardController->GetSelectedCard(), player))
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(0,AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE);
		if(IsRemoved(_cardController->GetSelectedCard(), player))
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(0,AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE);
		if(IsInDeck(_cardController->GetSelectedCard(), player))
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(0,AccessibilityFieldFocus::Field::DECK_ZONE);

		//Caso não encontre a carta, busca no outro campo;
		if (!fieldSlotModel && !recursion) {
			player = player == AccessibilityFieldFocus::Player::MAIN_PLAYER ? AccessibilityFieldFocus::Player::ENEMY_PLAYER : AccessibilityFieldFocus::Player::MAIN_PLAYER;
			fieldSlotModel = GetFieldSlotModel(true, player);
		}
		return fieldSlotModel;
	}

	FieldSlotModel* FieldController::GetMonsterSpellSlotModel(AccessibilityFieldFocus::Player player)
	{
		int fieldSlot = 0;
		FieldSlotModel* fieldSlotModel = nullptr;
		//Busca a carta no campo de monstros ou spells;
		if (currentField != AccessibilityFieldFocus::GRAVEYARD_ZONE &&
			currentField != AccessibilityFieldFocus::EXTRA_DECK_ZONE &&
			currentField != AccessibilityFieldFocus::REMOVED_CARDS_ZONE) {
			for (int i = 0; i < 7; i++) {
				if ((mainGame->dField.mzone[player][i] && mainGame->dField.mzone[player][i] == _cardController->GetSelectedCard()) ||
					(mainGame->dField.szone[player][i] && mainGame->dField.szone[player][i] == _cardController->GetSelectedCard())) {
					if (i < 5)
						fieldSlot = i + 1;
					else
						currentField = AccessibilityFieldFocus::Field::LINK_ZONE;
					break;
				}
			}
		}
		if(fieldSlot != 0)
			fieldSlotModel = FieldSlotController::GetInstance()->GetFieldSlotData(fieldSlot, currentField);
		return fieldSlotModel;
	}
}
