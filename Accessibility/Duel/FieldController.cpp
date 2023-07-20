#include "FieldController.h"

#include <Control/EventHandler.h>

#include "card.h"
#include "FieldSlotController.h"
#include "Helper/MouseHelper.h"
#include "Models/Card.h"
#include "ScreenReader/ScreenReader.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"

namespace ygo {
	FieldController* FieldController::GetFieldController()
	{
		if (_fieldController == nullptr)
			_fieldController = new FieldController();
		return _fieldController;
	}

	void FieldController::SetSelectedCardField()
	{
		_cardController = CardController::GetCardController();
		const ClientCard* card = _cardController->GetSelectedCard();
		if (!_cardController->GetSelectedCard())
			return;

		const bool foundCard = IsOnField(card);

		if (!foundCard) {
			const auto cardData = new Card(_cardController->GetSelectedCard());
			const int cardType = cardData->GetCardType();
			if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
				currenField = AccessibilityFieldFocus::PLAYER_MONSTERS;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			}
			else {
				currenField = AccessibilityFieldFocus::PLAYER_SPELLS;
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
			}
		}
	}

	void FieldController::SelectFieldSlot(const irr::SEvent& event, const int slot, const int& field)
	{
		SetCursorOnSlot(slot, field);
		MouseHelper::Click(event);
	}

	void FieldController::ReadFreeSlots(const AccessibilityFieldFocus::DisplayedField& player, const int& cardType,
		bool isLink)
	{
		constexpr int maxCommonSlots = 5;
		std::wstring freeSlots = gDataManager->GetAccessibilityString(Accessibility::Dict::Duel::FREE_SLOTS).data();
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

	void FieldController::SetCursorOnSlot(int slot, const int& field)
	{
		if (slot == 0) slot = 1;
		const auto cursor = mainGame->device->getCursorControl();
		auto pos = cursor->getRelativePosition();
		const FieldSlotModel* fieldSlot = GetSlotPosition(slot, field);
		pos.X = fieldSlot->xPosition;
		pos.Y = fieldSlot->yPosition;
		auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
		clamp(pos.X);
		clamp(pos.Y);
		cursor->setPosition(pos.X, pos.Y);
	}

	bool FieldController::IsOnField(const ClientCard* card, const int& player)
	{
		_cardController = CardController::GetCardController();
		for (int i = 0; i < 6; i++) {
			if (mainGame->dField.mzone[player][i] && mainGame->dField.mzone[player][i] == card) {
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
				_cardController->isSelected = true;
				currenField = AccessibilityFieldFocus::PLAYER_MONSTERS;
				return true;
			}
			if (mainGame->dField.szone[player][i] && mainGame->dField.szone[player][i] == card) {
				_cardController->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
				_cardController->isSelected = true;
				currenField = AccessibilityFieldFocus::PLAYER_SPELLS;
				return true;
			}
		}
		return false;
	}

	FieldSlotModel* FieldController::GetSlotPosition(const int& slot, const int& field)
	{
		const auto fieldSlotController = new FieldSlotController();
		return fieldSlotController->GetFieldSlotData(slot, field);
	}
}
