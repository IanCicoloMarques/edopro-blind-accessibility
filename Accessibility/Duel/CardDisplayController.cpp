#include "CardDisplayController.h"

#include "../gframe/game.h"
#include "../gframe/data_manager.h"
#include "../gframe/duelclient.h"
#include <IGUIWindow.h>

#include "FieldController.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Control/EventHandler.h"
#include "FieldFocus/AccessibilityFieldFocus.h"
#include "Helper/ButtonHelper.h"
#include "Helper/CardDisplayHelper.h"
#include "ScreenReader/ScreenReader.h"


namespace ygo {
	CardDisplayController* CardDisplayController::_cardDisplayController = nullptr;
	CardDisplayController* CardDisplayController::GetInstance()
	{
		if (_cardDisplayController == nullptr)
			_cardDisplayController = new CardDisplayController();
		return _cardDisplayController;
	}

	void CardDisplayController::KeyInputEvent(const irr::SEvent& event)
	{
		const AccessibilityFieldFocus::Player player = FieldController::GetInstance()->currentPlayer;
		if(event.KeyInput.Key == KeyboardConfiguration::ExtraDeck)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::Graveyard)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::Hand)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_HAND, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::RemovedZone)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::MonsterZone)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_MONSTERS, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::SpellZone)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_SPELLS, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::Deck)
			DisplayTable(event, AccessibilityFieldFocus::Field::PLAYER_DECK, player);
		else if(event.KeyInput.Key == KeyboardConfiguration::Chain)
			DisplayChain(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::SelectableCards)
			DisplaySelectableCards(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::SpecialSummonableCards)
			DisplaySpecialSummonableMonsters(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::ActivatableCards)
			DisplayActivableCards(event);
		else if(event.KeyInput.Key == irr::KEY_RIGHT){
			const unsigned int initialIndex = currentCardIndex;
			ChangeCurrentCardIndex(irr::KEY_RIGHT);
			ScrollDisplay(initialIndex, irr::KEY_RIGHT);
			ShowCardInfo();
		}
		else if(event.KeyInput.Key == irr::KEY_LEFT){
			const unsigned int initialIndex = currentCardIndex;
			ChangeCurrentCardIndex(irr::KEY_LEFT);
			ScrollDisplay(initialIndex, irr::KEY_LEFT);
			ShowCardInfo();
		}
	}

	void CardDisplayController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void CardDisplayController::ChangeCurrentCardIndex(irr::EKEY_CODE ekeyCode)
	{
		if (!mainGame->dField.display_cards.empty() && mainGame->dField.display_cards.size() == 1)
			currentCardIndex = 0;
		else if(ekeyCode == irr::KEY_LEFT && !mainGame->dField.display_cards.empty() && currentCardIndex <= mainGame->dField.display_cards.size() && currentCardIndex > 0) {
			currentCardIndex--;
		}
		else if (ekeyCode == irr::KEY_RIGHT && !mainGame->dField.display_cards.empty() && currentCardIndex < mainGame->dField.display_cards.size() - 1) {
			currentCardIndex++;
		}
	}

	void CardDisplayController::ScrollDisplay(unsigned int initialIndex, irr::EKEY_CODE ekeyCode)
	{
		if (initialIndex == currentCardIndex && !mainGame->dField.display_cards.empty() && mainGame->scrCardList->isTrulyVisible()) {
			const int pos = mainGame->scrCardList->getPos();
			if(ekeyCode == irr::KEY_RIGHT)
			{
				mainGame->scrCardList->setPos(pos + 10);
				const unsigned int cardPos = (mainGame->scrCardList->getPos() / 10) + 4;
				CardDisplayHelper::ScrollCardDisplay();
				if (mainGame->dField.display_cards.back() != mainGame->dField.selectable_cards.back() && cardPos < mainGame->dField.selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
					mainGame->dField.display_cards.push_back(mainGame->dField.selectable_cards[cardPos]);
					mainGame->dField.display_cards.erase(mainGame->dField.display_cards.begin());
				}
			}
			else if (ekeyCode == irr::KEY_LEFT) {
				mainGame->scrCardList->setPos(pos - 10);
				const unsigned int cardPos = (mainGame->scrCardList->getPos() / 10);
				CardDisplayHelper::ScrollCardDisplay();
				if (mainGame->dField.display_cards.front() != mainGame->dField.selectable_cards.front() && cardPos < mainGame->dField.selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
					mainGame->dField.display_cards.insert(mainGame->dField.display_cards.begin(), mainGame->dField.selectable_cards[cardPos]);
					mainGame->dField.display_cards.pop_back();
				}
			}
		}
	}

	void CardDisplayController::ShowCardInfo()
	{
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->ShowCardInfo(mainGame->dField.display_cards[currentCardIndex]->code);
			CardController::GetInstance()->SetCard(mainGame->dField.display_cards[currentCardIndex]);
			CardController::GetInstance()->ReadCardBasicInfo();
		}
	}

	void CardDisplayController::DisplayTable(const irr::SEvent& event, const AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player)
	{
		if(field == AccessibilityFieldFocus::Field::PLAYER_MONSTERS)
			DisplayMonsterField(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			DisplaySpellField(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS)
			DisplayRemovedCards(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_HAND)
			DisplayHand(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD)
			DisplayGraveyard(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK)
			DisplayExtraDeck(event, player);
		else if(field == AccessibilityFieldFocus::Field::PLAYER_DECK)
			DisplayDeck(event, player);
	}

	void CardDisplayController::CloseDisplay()
	{
		if (mainGame->wCardDisplay->isVisible())
			ButtonHelper::ClickButton(mainGame->btnDisplayOK);
	}

	bool CardDisplayController::CanDisplayCards(irr::SEvent event) {
		event.KeyInput.PressedDown = false;
		bool canViewCards = false;
		if (!event.KeyInput.PressedDown && mainGame->dInfo.player_type != 7 && mainGame->dInfo.isInDuel
			&& !mainGame->wCardDisplay->isVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
				canViewCards = true;
		return canViewCards;
	}

	void CardDisplayController::DisplayCards(const std::vector<ChainInfo>& field) {
		mainGame->dField.display_cards.clear();
		currentCardIndex = 0;
		for (auto it = field.begin(); it != field.end(); ++it) {
			mainGame->dField.display_cards.push_back(it._Ptr->chain_card);
		}
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", gDataManager->GetSysString(currentCardIndex), mainGame->dField.display_cards.size()).data());
			mainGame->dField.ShowLocationCard();
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
	}

	void CardDisplayController::DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text = L"") {
		mainGame->dField.display_cards.clear();
		currentCardIndex = 0;
		for (auto it = field.begin(); it != field.end(); ++it) {
			if (*it) {
				mainGame->dField.display_cards.push_back(*it);
			}
		}
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", text, mainGame->dField.display_cards.size()).data());
			mainGame->dField.ShowLocationCard();

			if (!text.empty()) {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(127).data(),
																  text, mainGame->dField.display_cards.size()), false);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
		else
		{
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(128).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
			CloseDisplay();
		}
	}

	void CardDisplayController::DisplayCardsReverse(const std::vector<ClientCard*>& field, const std::wstring& text = L"") {
		mainGame->dField.display_cards.clear();
		currentCardIndex = 0;
		mainGame->dField.display_cards.assign(field.crbegin(), field.crend());
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", text, mainGame->dField.display_cards.size()).data());
			mainGame->dField.ShowLocationCard();

			if (!text.empty()) {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(127).data(),
																  text, mainGame->dField.display_cards.size()), false);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
		else
		{
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(128).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
			CloseDisplay();
		}
	}

	void CardDisplayController::DisplayChain(const irr::SEvent& event)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::CHAIN);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::CHAINED_CARDS;
			DisplayCards(mainGame->dField.chains);
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayMonsterField(const irr::SEvent& event,AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			DisplayCards(mainGame->dField.mzone[displayed_field], fmt::format(gDataManager->GetAccessibilityString(95).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplaySpellField(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_SPELLS;
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::SPELL);
			DisplayCards(mainGame->dField.szone[displayed_field], fmt::format(gDataManager->GetAccessibilityString(66).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayExtraDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK;
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			DisplayCards(mainGame->dField.extra[displayed_field], fmt::format(gDataManager->GetAccessibilityString(92).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_DECK;
			if(!mainGame->dInfo.isReplay)
				DisplayCards(mainGame->dField.deck[displayed_field], fmt::format(gDataManager->GetAccessibilityString(94).data()));
			else
				DisplayCardsReverse(mainGame->dField.deck[displayed_field], fmt::format(gDataManager->GetAccessibilityString(94).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayHand(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_HAND;
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			DisplayCards(mainGame->dField.hand[displayed_field], fmt::format(gDataManager->GetAccessibilityString(90).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplaySpecialSummonableMonsters(const irr::SEvent& event)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_SPECIAL_SUMMONABLE_MONSTERS;
			if (mainGame->wCardSelect->isTrulyVisible()) {
				mainGame->dField.display_cards = mainGame->dField.selectable_cards;
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(96).data(),
				                                                  mainGame->dField.display_cards.size()), false);
				mainGame->env->setFocus(mainGame->wCardSelect);
			}
			else
				DisplayCards(mainGame->dField.spsummonable_cards, fmt::format(gDataManager->GetAccessibilityString(97).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayGraveyard(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD;
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::GRAVEYARD);
			DisplayCards(mainGame->dField.grave[displayed_field], fmt::format(gDataManager->GetAccessibilityString(93).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayRemovedCards(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS;
			DisplayCards(mainGame->dField.remove[displayed_field], fmt::format(gDataManager->GetAccessibilityString(98).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplaySelectableCards(const irr::SEvent& event)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::SELECTABLE_CARDS;
			if (mainGame->wCardSelect->isTrulyVisible()) {
				mainGame->dField.display_cards = mainGame->dField.selectable_cards;
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(99).data(),
				                                                  mainGame->dField.display_cards.size()), false);
				mainGame->env->setFocus(mainGame->wCardSelect);
			}
			else if (!mainGame->dField.selectable_cards.empty())
				DisplaySelectableCards(mainGame->dField.selectable_cards, fmt::format(gDataManager->GetAccessibilityString(100).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplayActivableCards(const irr::SEvent& event)
	{
		const bool canViewCards = CanDisplayCards(event);
		if (canViewCards) {
			CardController::GetInstance()->SetCardType(AccessibilityFieldFocus::CardType::MONSTER);
			FieldController::GetInstance()->currentField = AccessibilityFieldFocus::Field::PLAYER_ACTIVABLE_CARDS;
			DisplayCards(mainGame->dField.activatable_cards, fmt::format(gDataManager->GetAccessibilityString(65).data()));
		}
		else
			CloseDisplay();
	}

	void CardDisplayController::DisplaySelectableCards(const std::vector<ClientCard*>& field, const std::wstring& text) {
		currentCardIndex = 0;
		mainGame->dField.display_cards.clear();
		for (auto it = field.begin(); it != field.end(); ++it) {
			if (*it) {
				mainGame->dField.display_cards.push_back(*it);
			}
		}
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->wCardSelect->setText(fmt::format(L"{}({})", text, mainGame->dField.display_cards.size()).data());
			ShowSelectCard();

			if (!text.empty()) {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(127).data(),
																  text, mainGame->dField.display_cards.size()), false);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
		else
		{
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(128).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
			CloseDisplay();
		}
	}

	void CardDisplayController::ShowSelectCard() {
		int startpos;
		size_t ct;
		if (mainGame->dField.display_cards.size() <= 5) {
			startpos = 30 + 125 * (5 - mainGame->dField.display_cards.size()) / 2;
			ct = mainGame->dField.display_cards.size();
		}
		else {
			startpos = 30;
			ct = 5;
		}
		for (size_t i = 0; i < ct; ++i) {
			const auto& curstring = mainGame->stCardPos[i];
			const auto& curcard = mainGame->dField.display_cards[i];
			curstring->enableOverrideColor(false);
			// image
			if (curcard->code)
				mainGame->imageLoading[mainGame->btnCardSelect[i]] = curcard->code;
			else if (mainGame->dField.conti_selecting)
				mainGame->imageLoading[mainGame->btnCardSelect[i]] = curcard->chain_code;
			else
				mainGame->btnCardSelect[i]->setImage(mainGame->imageManager.tCover[curcard->controler]);
			mainGame->btnCardSelect[i]->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 55, startpos + 120 + i * 125, 225));
			mainGame->btnCardSelect[i]->setPressed(false);
			mainGame->btnCardSelect[i]->setVisible(true);
			if (mainGame->dInfo.curMsg != MSG_SORT_CHAIN && mainGame->dInfo.curMsg != MSG_SORT_CARD) {
				// text
				std::wstring text;
				if (mainGame->dField.conti_selecting)
					text = std::wstring{ DataManager::unknown_string };
				else if (curcard->location == LOCATION_OVERLAY) {
					text = fmt::format(L"{}[{}]({})", gDataManager->FormatLocation(curcard->overlayTarget->location, curcard->overlayTarget->sequence),
						curcard->overlayTarget->sequence + 1, curcard->sequence + 1);
				}
				else if (curcard->location) {
					text = fmt::format(L"{}[{}]", gDataManager->FormatLocation(curcard->location, curcard->sequence),
						curcard->sequence + 1);
				}
				curstring->setText(text.data());
				// color
				if (curcard->is_selected)
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELECTED_WINDOW_BACKGROUND_VAL);
				else {
					if (mainGame->dField.conti_selecting)
						curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
					else if (curcard->location == LOCATION_OVERLAY) {
						if (curcard->owner != curcard->overlayTarget->controler)
							curstring->setOverrideColor(skin::DUELFIELD_CARD_SELECT_WINDOW_OVERLAY_TEXT_VAL);
						if (curcard->overlayTarget->controler)
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
						else
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
					}
					else if (curcard->location == LOCATION_DECK || curcard->location == LOCATION_EXTRA || curcard->location == LOCATION_REMOVED) {
						if (curcard->position & POS_FACEDOWN)
							curstring->setOverrideColor(skin::DUELFIELD_CARD_SELECT_WINDOW_SET_TEXT_VAL);
						if (curcard->controler)
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
						else
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
					}
					else {
						if (curcard->controler)
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
						else
							curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
					}
				}
			}
			else {
				if (mainGame->dField.sort_list[i]) {
					curstring->setText(fmt::to_wstring(mainGame->dField.sort_list[i]).data());
				}
				else
					curstring->setText(L"");
				curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
			}
			curstring->setVisible(true);
			curstring->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 30, startpos + 120 + i * 125, 50));
		}
		if (mainGame->dField.display_cards.size() <= 5) {
			for (int i = mainGame->dField.display_cards.size(); i < 5; ++i) {
				mainGame->btnCardSelect[i]->setVisible(false);
				mainGame->stCardPos[i]->setVisible(false);
			}
			mainGame->scrCardList->setPos(0);
			mainGame->scrCardList->setVisible(false);
		}
		else {
			mainGame->scrCardList->setVisible(true);
			mainGame->scrCardList->setMin(0);
			mainGame->scrCardList->setMax((mainGame->dField.display_cards.size() - 5) * 10 + 9);
			mainGame->scrCardList->setPos(0);
		}
		mainGame->btnSelectOK->setVisible(true);
		mainGame->PopupElement(mainGame->wCardSelect);
	}

}
