#include "DuelController.h"

#include "CardController.h"
#include "CardDisplayController.h"
#include "DuelMenuController.h"
#include "FieldController.h"
#include "IGUIButton.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Helper/ButtonHelper.h"
#include "Models/UseCardModel.h"
#include "ScreenReader/ScreenReader.h"
#include "../gframe/game.h"
#include "Helper/MouseHelper.h"
#include "Models/CardModel.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"

namespace ygo {
	IEventHandler* DuelController::_duelController = nullptr;

	IEventHandler* DuelController::GetInstance()
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
		auto* duelController = static_cast<DuelMenuController *>(DuelMenuController::GetInstance());
		if(event.KeyInput.Key == KeyboardConfiguration::NormalSummon &&  duelController->GetBattleStep() != AccessibilityFieldFocus::BattleStep::BP)
			Command(AccessibilityFieldFocus::UseType::NORMAL_SUMMON, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SetSummon)
			Command(AccessibilityFieldFocus::UseType::SET_CARD, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SpecialSummon)
			Command(AccessibilityFieldFocus::UseType::SPECIAL_SUMMON, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::ActivateCard)
			Command(AccessibilityFieldFocus::UseType::ACTIVATE, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::Attack)
			Command(AccessibilityFieldFocus::UseType::ATTACK, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::ChangeBattlePosition)
			Command(AccessibilityFieldFocus::UseType::CHANGE_BATTLE_POSITION, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SelectCard)
			Command(AccessibilityFieldFocus::UseType::SELECT_CARD, event, mainGame->dField.display_cards[CardDisplayController::GetInstance()->currentCardIndex]);
	}

	void DuelController::Command(AccessibilityFieldFocus::UseType useType, const irr::SEvent& event, ClientCard* card)
	{
		CardController* cardController = CardController::GetInstance();
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
				case AccessibilityFieldFocus::UseType::ATTACK: {
					Attack(useCardModel, event);
					break;
				}
				case AccessibilityFieldFocus::UseType::CHANGE_BATTLE_POSITION: {
					ChangeBattlePosition(useCardModel);
					break;
				}
				case AccessibilityFieldFocus::UseType::SELECT_CARD: {
					SelectCard(card, event);
					break;
				}
				default:{
					break;
				}
			}
		}
		useCardModel->ReadCommand();
		cardController->ReadAvailableCommands();
	}

	void DuelController::NormalSummon(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetInstance();
		useCardModel->command = CommandMessages::NORMAL_SUMMON;
		FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
		if (mainGame->btnSummon->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::PLAYER, AccessibilityFieldFocus::CardType::MONSTER);
		}
	}

	void DuelController::SetCard(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetInstance();
		fieldController->SetSelectedCardField();
		useCardModel->command = CommandMessages::SET_CARD;
		FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_SPELLS;
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
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::PLAYER, cardType);
		}
	}

	void DuelController::SpecialSummon(UseCardModel* useCardModel, const ClientCard* card)
	{
		const auto fieldController = FieldController::GetInstance();
		useCardModel->command = CommandMessages::SPECIAL_SUMMON;
		FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
		if (mainGame->btnSPSummon->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnSPSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::PLAYER, AccessibilityFieldFocus::CardType::MONSTER, CardModel::IsLink(card));
		}
	}

	void DuelController::ActivateCardEffect(UseCardModel* useCardModel)
	{
		const auto fieldController = FieldController::GetInstance();
		useCardModel->command = CommandMessages::ACTIVATE;
		if(fieldController->currentField != AccessibilityFieldFocus::Field::PLAYER_MONSTERS && fieldController->currentField != AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			fieldController->currentField = AccessibilityFieldFocus::Field::SELECTABLE_CARDS;

		if (mainGame->btnActivate->isTrulyVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnActivate);
		}
		else if (mainGame->btnOperation->isTrulyVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnOperation);
		}
	}

	void DuelController::Attack(UseCardModel* useCardModel, const irr::SEvent& event)
	{
		const auto fieldController = FieldController::GetInstance();
		useCardModel->command = CommandMessages::ATTACK;
		if(fieldController->currentField != AccessibilityFieldFocus::Field::PLAYER_MONSTERS && fieldController->currentField != AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			fieldController->currentField = AccessibilityFieldFocus::Field::SELECTABLE_CARDS;

		if (mainGame->btnAttack->isTrulyVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnAttack);
		}
		else if(fieldController->currentField == AccessibilityFieldFocus::Field::PLAYER_MONSTERS && fieldController->currentPlayer == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			MouseHelper::Click(event);
	}

	void DuelController::ChangeBattlePosition(UseCardModel* useCardModel)
	{
		useCardModel->command = CommandMessages::CHANGE_MODE;
		FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
		if (mainGame->btnRepos->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnRepos);
		}
	}

	void DuelController::SelectCard(ClientCard* card, const irr::SEvent& event)
	{
		ClientCard* clickedCard = CardDisplayController::GetInstance()->GetSelectedCard();
		mainGame->dField.clicked_card = clickedCard;
		const std::wstring cardName = fmt::format(gDataManager->GetAccessibilityString(110).data(), gDataManager->GetName(clickedCard->code));
		ScreenReader::getReader()->readScreen(cardName);
		// if (mainGame->btnCardSelect[0]->isTrulyVisible() || clickedCard->cmdFlag == 4 && std::find(mainGame->dField.spsummonable_cards.begin(), mainGame->dField.spsummonable_cards.end(), clickedCard) == mainGame->dField.spsummonable_cards.end())
		if (mainGame->btnCardSelect[0]->isTrulyVisible())
			CardDisplayController::GetInstance()->TryClickCard();
		else
		{
			FieldController::GetInstance()->SetMousePositionOnCardOnFieldOrHand(card);
			MouseHelper::Click(event);
		}
	}
}
