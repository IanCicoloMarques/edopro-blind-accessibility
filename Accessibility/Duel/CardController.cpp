#include "CardController.h"

#include "CardDisplayController.h"
#include "FieldController.h"
#include "IGUIButton.h"
#include "IGUIWindow.h"
#include "../gframe/game.h"
#include "../gframe/data_manager.h"
#include "Configuration/AccessibilityConfiguration.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Models/CardModel.h"
#include "Models/FieldSlotModel.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"

namespace ygo {
	IEventHandler* CardController::_cardController = nullptr;

	CardController::CardController()
	{
		_selectedCard = nullptr;
	}

	IEventHandler* CardController::GetInstance()
	{
		if (_cardController == nullptr)
			_cardController = new CardController();
		return _cardController;
	}

	void CardController::KeyInputEvent(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == KeyboardConfiguration::CardInformation)
		{
			const int currentCardIndex = static_cast<CardDisplayController *>(CardDisplayController::GetInstance())->currentCardIndex;
			if(mainGame->dField.display_cards.size() <= currentCardIndex)
				return;
			SetCard(mainGame->dField.display_cards[currentCardIndex]);
			ReadCardInfo();
		}
	}

	void CardController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	bool CardController::HasEventKey(irr::EKEY_CODE key)
	{
		std::vector<int> keys = { KeyboardConfiguration::CardInformation };
		if(std::find(keys.begin(), keys.end(), key) != keys.end())
			return true;
		return false;
	}

	void CardController::SetCard(ClientCard* card)
	{
		if (!card)
			return;
		_selectedCard = card;
	}

	void CardController::ReadCardInfo()
	{
		auto* card = new CardModel(_selectedCard);
		auto* fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		const FieldSlotModel* fieldSlotModel = fieldController->GetFieldSlotModel();
		if(fieldSlotModel != nullptr)
			card->SetFieldSlot(fieldSlotModel->slotNumber);
		card->ReadCardInfo();
	};

	void CardController::ReadCardBasicInfo()
	{
		auto* card = new CardModel(_selectedCard);
		auto* fieldController = static_cast<FieldController *>(FieldController::GetInstance());
		const FieldSlotModel* fieldSlotModel = fieldController->GetFieldSlotModel();
		if(fieldSlotModel != nullptr)
			card->SetFieldSlot(fieldSlotModel->slotNumber);
		card->ReadCardBasicInfo();
	};

	void CardController::ShowCardOptions(int x, int y)
	{
		const int flag = _selectedCard->cmdFlag;
		if (!flag) {
			mainGame->wCmdMenu->setVisible(false);
			return;
		}
		int height = mainGame->Scale(1);
		const auto increase = mainGame->Scale(21);
		if (flag & COMMAND_ACTIVATE) {
			mainGame->btnActivate->setVisible(true);
			mainGame->btnActivate->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnActivate->setVisible(false);
		if (flag & COMMAND_SUMMON) {
			mainGame->btnSummon->setVisible(true);
			mainGame->btnSummon->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSummon->setVisible(false);
		if (flag & COMMAND_SPSUMMON) {
			mainGame->btnSPSummon->setVisible(true);
			mainGame->btnSPSummon->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSPSummon->setVisible(false);
		if (flag & COMMAND_MSET) {
			mainGame->btnMSet->setVisible(true);
			mainGame->btnMSet->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnMSet->setVisible(false);
		if (flag & COMMAND_SSET) {
			if (!(_selectedCard->type & TYPE_MONSTER))
				mainGame->btnSSet->setText(gDataManager->GetSysString(1153).data());
			else
				mainGame->btnSSet->setText(gDataManager->GetSysString(1159).data());
			mainGame->btnSSet->setVisible(true);
			mainGame->btnSSet->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSSet->setVisible(false);
		if (flag & COMMAND_REPOS) {
			if (_selectedCard->position & POS_FACEDOWN)
				mainGame->btnRepos->setText(gDataManager->GetSysString(1154).data());
			else if (_selectedCard->position & POS_ATTACK)
				mainGame->btnRepos->setText(gDataManager->GetSysString(1155).data());
			else
				mainGame->btnRepos->setText(gDataManager->GetSysString(1156).data());
			mainGame->btnRepos->setVisible(true);
			mainGame->btnRepos->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnRepos->setVisible(false);
		if (flag & COMMAND_ATTACK) {
			mainGame->btnAttack->setVisible(true);
			mainGame->btnAttack->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnAttack->setVisible(false);
		if (flag & COMMAND_LIST) {
			mainGame->btnShowList->setVisible(true);
			mainGame->btnShowList->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnShowList->setVisible(false);
		if (flag & COMMAND_OPERATION) {
			mainGame->btnOperation->setVisible(true);
			mainGame->btnOperation->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnOperation->setVisible(false);
		if (flag & COMMAND_RESET) {
			mainGame->btnReset->setVisible(true);
			mainGame->btnReset->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnReset->setVisible(false);
		mainGame->dField.panel = mainGame->wCmdMenu;
		mainGame->wCmdMenu->setVisible(true);
		const irr::core::vector2di mouse = mainGame->Resize(x, y);
		x = mouse.X;
		y = mouse.Y;
		mainGame->wCmdMenu->setRelativePosition(irr::core::recti(x - mainGame->Scale(20), y - mainGame->Scale(20) - height, x + mainGame->Scale(80), y - mainGame->Scale(20)));
	}

	void CardController::ReadAvailableCommands()
	{
		std::wstring options = std::wstring();
		if(mainGame->btnSummon->isTrulyVisible())
			options += fmt::format(L"{}, {}, ",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::SUMMON).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::NormalSummon));
		if(mainGame->btnMSet->isTrulyVisible() || mainGame->btnSSet->isTrulyVisible())
			options += fmt::format(L"{}, {}, ",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::SET).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::SetSummon));
		if(mainGame->btnSPSummon->isTrulyVisible())
			options += fmt::format(L"{}, {}, ",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::SPECIAL_SUMMON).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::SpecialSummon));
		if(mainGame->btnActivate->isTrulyVisible() || mainGame->btnOperation->isTrulyVisible())
			options += fmt::format(L"{}, {}, ",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::ACTIVATE).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::ActivateCard));
		if(mainGame->btnAttack->isTrulyVisible())
			options += fmt::format(L"{}, {}, ",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::ATTACK).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::Attack));
		if(mainGame->btnRepos->isTrulyVisible())
			options += fmt::format(L"{}, {}",gDataManager->GetAccessibilityString(Accessibility::Dict::CardUses::CHANGE_MODE).data(),AccessibilityConfiguration::GetKeyString(KeyboardConfiguration::ChangeBattlePosition));
		if(!options.empty())
			ScreenReader::getReader()->readScreen(options, false);
	}

	ClientCard* CardController::GetSelectedCard()
	{
		if(_selectedCard == nullptr)
			return nullptr;
		return _selectedCard;
	}

	void CardController::SetCardType(const AccessibilityFieldFocus::CardType type)
	{
		_cardType = type;
	}

	AccessibilityFieldFocus::Field CardController::GetCardLocation(const ClientCard* card) {
		AccessibilityFieldFocus::Field location = AccessibilityFieldFocus::Field::UNKNOWN_ZONE;
		if (card->location == LOCATION_EXTRA)
			location = AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE;
		else if (card->location == LOCATION_DECK)
			location = AccessibilityFieldFocus::Field::DECK_ZONE;
		else if (card->location == LOCATION_GRAVE)
			location = AccessibilityFieldFocus::Field::GRAVEYARD_ZONE;
		else if (card->location == LOCATION_REMOVED)
			location = AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE;
		else if (card->location == LOCATION_HAND)
			location = AccessibilityFieldFocus::Field::HAND_ZONE;
		else if (card->location == LOCATION_MZONE)
			location = AccessibilityFieldFocus::Field::MONSTER_ZONE;
		else if (card->location == LOCATION_SZONE)
			location = AccessibilityFieldFocus::Field::SPELL_ZONE;
		return location;
	}
}
