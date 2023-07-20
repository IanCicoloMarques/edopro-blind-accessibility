#include "DuelController.h"

#include "CardController.h"
#include "CardDisplayController.h"
#include "FieldController.h"
#include "IGUIButton.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Helper/ButtonHelper.h"
#include "Models/UseCardModel.h"
#include "ScreenReader/ScreenReader.h"
#include "../gframe/game.h"
#include "Models/Card.h"

namespace ygo {
	IEventHandler* DuelController::_duelController = nullptr;
	int DuelController::_battlePhase = AccessibilityFieldFocus::BattleStep::MP1;

	IEventHandler* DuelController::GetDuelController()
	{
		if (_duelController == nullptr)
			_duelController = new DuelController();
		return _duelController;
	}

	void DuelController::KeyInputEvent(const irr::SEvent& event)
	{
		ClientCard* clickedCard = mainGame->dField.clicked_card;
		if(!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
		{
			DuelCommands(event, clickedCard);
		}
	}

	void DuelController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void DuelController::DuelCommands(const irr::SEvent& event, ClientCard* card)
	{
		if(event.KeyInput.Key == KeyboardConfiguration::NormalSummon && _battlePhase != AccessibilityFieldFocus::BattleStep::BP)
			Command(AccessibilityFieldFocus::UseType::NORMAL_SUMMON, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SetSummon)
			Command(AccessibilityFieldFocus::UseType::SET_CARD, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SpecialSummon)
			Command(AccessibilityFieldFocus::UseType::SPECIAL_SUMMON, event, card);
	}

	void DuelController::Command(AccessibilityFieldFocus::UseType useType, const irr::SEvent& event, ClientCard* card)
	{
		CardController* cardController = CardController::GetCardController();
		cardController->SetCard(card);
		auto* useCardModel = new UseCardModel();
		CardDisplayController::CloseDisplay();
		if (card)
		{
			cardController->ShowCardOptions();
			switch (useType)
			{
				case AccessibilityFieldFocus::UseType::NORMAL_SUMMON: {
					NormalSummon(useCardModel);
					break;
				}
				case AccessibilityFieldFocus::UseType::SET_CARD: {
					SetCard(useCardModel);
					break;
				}
				case AccessibilityFieldFocus::UseType::SPECIAL_SUMMON: {
					SpecialSummon(useCardModel, card);
					break;
				}
				case AccessibilityFieldFocus::UseType::ACTIVATE: {
					ActivateCardEffect(useCardModel);
					break;
				}
			}
		}
		useCardModel->ReadCommand();
	}

	void DuelController::NormalSummon(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetFieldController();
		useCardModel->command = CommandMessages::NORMAL_SUMMON;
		if (mainGame->btnSummon->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::DisplayedField::PLAYER, AccessibilityFieldFocus::CardType::MONSTER);
		}
	}

	void DuelController::SetCard(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetFieldController();
		fieldController->SetSelectedCardField();
		useCardModel->command = CommandMessages::SET_CARD;
		irr::gui::IGUIButton* button = nullptr;
		int cardType;
		if (mainGame->btnMSet->isVisible()) {
			button = mainGame->btnMSet;
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		}
		else if (mainGame->btnSSet->isVisible()) {
			button = mainGame->btnSSet;
			cardType = AccessibilityFieldFocus::CardType::SPELL;
		}

		if(button)
		{
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(button);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::DisplayedField::PLAYER, cardType);
		}
	}

	void DuelController::SpecialSummon(UseCardModel* useCardModel, const ClientCard* card)
	{
		const auto fieldController = FieldController::GetFieldController();
		useCardModel->command = CommandMessages::SPECIAL_SUMMON;
		if (mainGame->btnSPSummon->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnSPSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::DisplayedField::PLAYER, AccessibilityFieldFocus::CardType::MONSTER, Card::IsLink(card));
		}
	}

	void DuelController::ActivateCardEffect(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetFieldController();
		useCardModel->command = CommandMessages::ACTIVATE;
		if(fieldController->currenField != AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS && fieldController->currenField != AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS)
			fieldController->currenField = AccessibilityFieldFocus::FieldLookerLocId::SELECTABLE_CARDS;

		if (mainGame->btnActivate->isTrulyVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnActivate);
		}
		else if (mainGame->btnOperation->isTrulyVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnOperation);
		}
	}
}
