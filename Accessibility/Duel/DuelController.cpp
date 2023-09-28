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
// #include <IGUIWindow.h>
// #include "../gframe/duelclient.h"

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

	bool DuelController::HasEventKey(irr::EKEY_CODE key)
	{
		std::vector<int> keys = {
			KeyboardConfiguration::NormalSummon, KeyboardConfiguration::SetSummon, KeyboardConfiguration::SpecialSummon, KeyboardConfiguration::ActivateCard,
			KeyboardConfiguration::Attack, KeyboardConfiguration::ChangeBattlePosition, KeyboardConfiguration::SelectCard
		};
		if(std::find(keys.begin(), keys.end(), key) != keys.end())
			return true;
		return false;
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
		else if(event.KeyInput.Key == KeyboardConfiguration::Attack && duelController->GetBattleStep() == AccessibilityFieldFocus::BattleStep::BP)
			Command(AccessibilityFieldFocus::UseType::ATTACK, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::ChangeBattlePosition)
			Command(AccessibilityFieldFocus::UseType::CHANGE_BATTLE_POSITION, event, card);
		else if(event.KeyInput.Key == KeyboardConfiguration::SelectCard)
		{
			const int currentIndex = static_cast<CardDisplayController *>(CardDisplayController::GetInstance())->currentCardIndex;
			if(mainGame->dField.display_cards.size() > currentIndex)
				Command(AccessibilityFieldFocus::UseType::SELECT_CARD, event, mainGame->dField.display_cards[currentIndex]);
		}
	}

	void DuelController::Command(AccessibilityFieldFocus::UseType useType, const irr::SEvent& event, ClientCard* card)
	{
		CardController* cardController = static_cast<CardController *>(CardController::GetInstance());
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
		const auto fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		useCardModel->command = CommandMessages::NORMAL_SUMMON;
		fieldController->currentField = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		if (mainGame->btnSummon->isVisible()) {
			useCardModel->canUse = true;
			fieldController->SetSelectedCardField();
			ButtonHelper::ClickButton(mainGame->btnSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::MAIN_PLAYER, AccessibilityFieldFocus::CardType::MONSTER);
		}
	}

	void DuelController::SetCard(UseCardModel* useCardModel)
	{
		const auto fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		fieldController->SetSelectedCardField();
		useCardModel->command = CommandMessages::SET_CARD;
		fieldController->currentField = AccessibilityFieldFocus::Field::SPELL_ZONE;
		irr::gui::IGUIButton* button = nullptr;
		int cardType;
		if (mainGame->btnMSet->isVisible()) {
			button = mainGame->btnMSet;
			fieldController->SetSelectedCardField();
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		}
		else if (mainGame->btnSSet->isVisible()) {
			button = mainGame->btnSSet;
			fieldController->SetSelectedCardField();
			cardType = AccessibilityFieldFocus::CardType::SPELL;
		}

		if(button)
		{
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(button);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::MAIN_PLAYER, cardType);
		}
	}

	void DuelController::SpecialSummon(UseCardModel* useCardModel, const ClientCard* card)
	{
		const auto fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		useCardModel->command = CommandMessages::SPECIAL_SUMMON;
		fieldController->currentField = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		if (mainGame->btnSPSummon->isVisible()) {
			useCardModel->canUse = true;
			fieldController->SetSelectedCardField();
			ButtonHelper::ClickButton(mainGame->btnSPSummon);
			fieldController->ReadFreeSlots(AccessibilityFieldFocus::Player::MAIN_PLAYER, AccessibilityFieldFocus::CardType::MONSTER, CardModel::IsLink(card));
		}
	}

	void DuelController::ExtraSpecialSummon(ClientCard* clickedCard, const irr::SEvent& event)
	{
		CardDisplayController::CloseDisplay();
		const AccessibilityFieldFocus::Field cardLocation = static_cast<CardController *>(CardController::GetInstance())->GetCardLocation(clickedCard);
		static_cast<FieldController *>(FieldController::GetInstance())->SetMousePositionOnSlot(cardLocation);
		MouseHelper::Click(event);
		if(mainGame->btnOperation->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnOperation);
		Command(AccessibilityFieldFocus::UseType::ACTIVATE, event, clickedCard);
	}

	void DuelController::ActivateCardEffect(UseCardModel* useCardModel)
	{
		const auto fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		useCardModel->command = CommandMessages::ACTIVATE;
		if(fieldController->currentField != AccessibilityFieldFocus::Field::MONSTER_ZONE && fieldController->currentField != AccessibilityFieldFocus::Field::SPELL_ZONE)
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
		const auto fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		useCardModel->command = CommandMessages::ATTACK;
		if(fieldController->currentField != AccessibilityFieldFocus::Field::MONSTER_ZONE && fieldController->currentField != AccessibilityFieldFocus::Field::SPELL_ZONE)
			fieldController->currentField = AccessibilityFieldFocus::Field::SELECTABLE_CARDS;

		if (mainGame->btnAttack->isTrulyVisible()) {
			useCardModel->canUse = true;
			fieldController->SetSelectedCardField();
			ButtonHelper::ClickButton(mainGame->btnAttack);
		}
		else if(fieldController->currentField == AccessibilityFieldFocus::Field::MONSTER_ZONE && fieldController->currentPlayer == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			MouseHelper::Click(event);
	}

	void DuelController::ChangeBattlePosition(UseCardModel* useCardModel)
	{
		useCardModel->command = CommandMessages::CHANGE_MODE;
		static_cast<FieldController *>(FieldController::GetInstance())->currentField = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		if (mainGame->btnRepos->isVisible()) {
			useCardModel->canUse = true;
			ButtonHelper::ClickButton(mainGame->btnRepos);
		}
	}

	void DuelController::SelectCard(ClientCard* card, const irr::SEvent& event)
	{
		auto* cardDisplayController = static_cast<CardDisplayController *>(CardDisplayController::GetInstance());
		ClientCard* clickedCard = cardDisplayController->GetSelectedCard();
		mainGame->dField.clicked_card = clickedCard;
		const std::wstring cardName = fmt::format(gDataManager->GetAccessibilityString(110).data(), gDataManager->GetName(clickedCard->code));
		ScreenReader::getReader()->readScreen(cardName);

		//Clicar no card selecionado dentro do display
		if (mainGame->btnCardSelect[0]->isTrulyVisible())
			cardDisplayController->TryClickCard();
		else if(CanExtraSpecialSummon(clickedCard))
			ExtraSpecialSummon(clickedCard, event);
		else
		{
			CardDisplayController::CloseDisplay();
			static_cast<FieldController *>(FieldController::GetInstance())->SetMousePositionOnCardOnFieldOrHand(card);
			MouseHelper::Click(event);
		}
	}

	bool DuelController::CanExtraSpecialSummon(const ClientCard* clickedCard)
	{
		return clickedCard->cmdFlag == 4 && std::find(mainGame->dField.spsummonable_cards.begin(), mainGame->dField.spsummonable_cards.end(), clickedCard) == mainGame->dField.spsummonable_cards.end();
	}
}
