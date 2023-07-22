#include "EventHandler.h"

#include <utility>
#include <fmt/format.h>
#include <fmt/printf.h>

#include "../accessibility/ScreenReader/ScreenReader.h"
#include "../accessibility/ScreenReader/StringBuilder.h"

#include "../gframe/data_manager.h"
#include "../accessibility/Models/CardModel.h"
#include "../accessibility/ScreenReader/Messages/AccessibilityStringDictionary.h"
#include "../Configuration/Keyboard/KeyboardConfiguration.h"
#include "Duel/CardDisplayController.h"
#include "Duel/DuelController.h"
#include "Duel/DuelMenuController.h"
#include "Duel/FieldController.h"

namespace ygo {
	IEventHandler* EventHandler::eventHandler = nullptr;
	unsigned int EventHandler::indexLookedUpCard = 0;
	int EventHandler::battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
	bool EventHandler::effectResolver = false;
	bool EventHandler::mudConfiguration = false;
	bool EventHandler::selectZone = false;
	bool EventHandler::rockPaperScissor = false;
	static AccessibilityFieldFocus::Field lookupFieldLocId;

	static inline void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
		irr::SEvent event;
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		event.GUIEvent.Caller->setVisible(true);
		mainGame->fadingList.clear();
		mainGame->device->postEventFromUser(event);
	}

	static inline void FocusAndReadCheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (!mainGame->env->hasFocus(chkbox))
			mainGame->env->setFocus(chkbox);
		const std::wstring nvdaString = fmt::format(L"{}", chkbox->getText());
		ScreenReader::getReader()->readScreen(nvdaString, false);
	}

	static inline void FocusAndReadGuiElement(irr::gui::IGUIElement* target, int stringCode, bool saveHistory = false) {
		if (!mainGame->env->hasFocus(target))
			mainGame->env->setFocus(target);
		ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(stringCode).data(), saveHistory);
	}

	static inline void FocusAndReadGuiElement(irr::gui::IGUIElement* target, std::wstring message, bool saveHistory = false) {
		if (!mainGame->env->hasFocus(target))
			mainGame->env->setFocus(target);
		ScreenReader::getReader()->readScreen(std::move(message), saveHistory);
	}

	IEventHandler* EventHandler::getEventHandler()
	{
		if (eventHandler == nullptr)
			eventHandler = new EventHandler();
		return eventHandler;
	}

	void EventHandler::SetKeyboardConfiguration()
	{
		if(mudConfiguration)
			KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Mud);
		else
			KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Default);
	}

	void EventHandler::TriggerEndPhase()
	{
		TriggerEvent(mainGame->btnEP, irr::gui::EGET_BUTTON_CLICKED);
		battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		cardType = AccessibilityFieldFocus::CardType::MONSTER;
	}

	void EventHandler::TriggerBattlePhase()
	{
		TriggerEvent(mainGame->btnBP, irr::gui::EGET_BUTTON_CLICKED);
		battlePhase = AccessibilityFieldFocus::BattleStep::BP;
	}

	void EventHandler::TriggerMainPhase2()
	{
		TriggerEvent(mainGame->btnM2, irr::gui::EGET_BUTTON_CLICKED);
		battlePhase = AccessibilityFieldFocus::BattleStep::MP2;
	}

	void EventHandler::DisplaySpellField(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_SPELLS;
			cardType = AccessibilityFieldFocus::CardType::SPELL;
			DisplayCards(mainGame->dField.szone[displayed_field], fmt::format(gDataManager->GetAccessibilityString(66).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::ActivateCard(const irr::SEvent& event)
	{
		if (std::find(mainGame->dField.spsummonable_cards.begin(), mainGame->dField.spsummonable_cards.end(), mainGame->dField.clicked_card) == mainGame->dField.spsummonable_cards.end())
			EffectResolver(event);
		ChangeFieldByCard();
		UseCard(AccessibilityFieldFocus::UseType::ACTIVATE, event);
	}

	void EventHandler::DisplayGraveyard(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD;
			cardType = AccessibilityFieldFocus::CardType::GRAVEYARD;
			DisplayCards(mainGame->dField.grave[displayed_field], fmt::format(gDataManager->GetAccessibilityString(93).data()));
			SelectFieldSlotHandAllowed(SearchFieldSlot(displayed_field), displayed_field);
			MouseClick(event);
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplayHand(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_HAND;
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			DisplayCards(mainGame->dField.hand[displayed_field], fmt::format(gDataManager->GetAccessibilityString(90).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::StartChat()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(88).data()), false);
		mainGame->env->setFocus(mainGame->ebChatInput);
	}

	void EventHandler::DisplayChain(const irr::SEvent& event)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::CHAIN;
			lookupFieldLocId = AccessibilityFieldFocus::Field::CHAINED_CARDS;
			DisplayCards(mainGame->dField.chains, fmt::format(gDataManager->GetAccessibilityString(89).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplayMonsterField(const irr::SEvent& event,AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			DisplayCards(mainGame->dField.mzone[displayed_field], fmt::format(gDataManager->GetAccessibilityString(95).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplayExtraDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK;
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			DisplayCards(mainGame->dField.extra[displayed_field], fmt::format(gDataManager->GetAccessibilityString(92).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplayDeck(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_DECK;
			if(!mainGame->dInfo.isReplay)
				DisplayCards(mainGame->dField.deck[displayed_field], fmt::format(gDataManager->GetAccessibilityString(94).data()));
			else
				DisplayCardsReverse(mainGame->dField.deck[displayed_field], fmt::format(gDataManager->GetAccessibilityString(94).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplaySpecialSummonableMonsters(const irr::SEvent& event)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_SPECIAL_SUMMONABLE_MONSTERS;
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
			CloseDialog();
	}

	void EventHandler::DisplayRemovedCards(const irr::SEvent& event, AccessibilityFieldFocus::Player displayed_field = AccessibilityFieldFocus::Player::PLAYER)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS;
			DisplayCards(mainGame->dField.remove[displayed_field], fmt::format(gDataManager->GetAccessibilityString(98).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplaySelectableCards(const irr::SEvent& event)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			lookupFieldLocId = AccessibilityFieldFocus::Field::SELECTABLE_CARDS;
			if (mainGame->wCardSelect->isTrulyVisible()) {
				mainGame->dField.display_cards = mainGame->dField.selectable_cards;
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(99).data(),
				                                                  mainGame->dField.display_cards.size()), false);
				mainGame->env->setFocus(mainGame->wCardSelect);
			}
			else if (!mainGame->dField.selectable_cards.empty())
				SelectCard(mainGame->dField.selectable_cards, fmt::format(gDataManager->GetAccessibilityString(100).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::DisplayActivableCards(const irr::SEvent& event)
	{
		const bool canViewCards = CheckIfCanViewCards(event);
		if (canViewCards) {
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_ACTIVABLE_CARDS;
			DisplayCards(mainGame->dField.activatable_cards, fmt::format(gDataManager->GetAccessibilityString(65).data()));
		}
		else
			CloseDialog();
	}

	void EventHandler::ClickButton(irr::gui::IGUIButton* button, int message_code, bool saveHistory = false)
	{
		if (button->isTrulyVisible())
		{
			TriggerEvent(button, irr::gui::EGET_BUTTON_CLICKED);
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(message_code).data(), mainGame->ebFileSaveName->getText());
			ScreenReader::getReader()->readScreen(nvdaString, saveHistory);
		}
	}

	void EventHandler::UseSelectedCard(const irr::SEvent& event)
	{
		if (!mainGame->dField.display_cards.empty() && indexLookedUpCard <= mainGame->dField.display_cards.size()) {
			ClientCard* _clickedCard = mainGame->dField.display_cards[indexLookedUpCard];
			mainGame->dField.clicked_card = mainGame->dField.display_cards[indexLookedUpCard];
			const std::wstring cardName = fmt::format(gDataManager->GetAccessibilityString(110).data(), gDataManager->GetName(_clickedCard->code));
			ScreenReader::getReader()->readScreen(cardName);
			if (mainGame->btnCardSelect[0]->isTrulyVisible() || _clickedCard->cmdFlag == 4 && std::find(mainGame->dField.spsummonable_cards.begin(), mainGame->dField.spsummonable_cards.end(), _clickedCard) == mainGame->dField.spsummonable_cards.end())
				UseCard(AccessibilityFieldFocus::UseType::NO_USE, event, _clickedCard);
			else
				UseCard(AccessibilityFieldFocus::UseType::SELECT_CARD, event, _clickedCard);
		}
	}

	void EventHandler::ChangeLookedUpCardIndex(irr::EKEY_CODE ekeyCode)
	{
		if (!mainGame->dField.display_cards.empty() && mainGame->dField.display_cards.size() == 1)
			indexLookedUpCard = 0;
		else if(ekeyCode == irr::KEY_LEFT && !mainGame->dField.display_cards.empty() && indexLookedUpCard <= mainGame->dField.display_cards.size() && indexLookedUpCard > 0) {
			indexLookedUpCard--;
		}
		else if (ekeyCode == irr::KEY_RIGHT && !mainGame->dField.display_cards.empty() && indexLookedUpCard < mainGame->dField.display_cards.size() - 1) {
			indexLookedUpCard++;
		}
	}

	void EventHandler::ScrollDisplayCards(unsigned int initialIndex, irr::EKEY_CODE ekeyCode)
	{
		if (initialIndex == indexLookedUpCard && !mainGame->dField.display_cards.empty() && mainGame->scrCardList->isTrulyVisible()) {
			const int pos = mainGame->scrCardList->getPos();
			if(ekeyCode == irr::KEY_RIGHT)
			{
				mainGame->scrCardList->setPos(pos + 10);
				const unsigned int cardPos = (mainGame->scrCardList->getPos() / 10) + 4;
				ScrollCardList();
				if (mainGame->dField.display_cards.back() != mainGame->dField.selectable_cards.back() && cardPos < mainGame->dField.selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
					mainGame->dField.display_cards.push_back(mainGame->dField.selectable_cards[cardPos]);
					mainGame->dField.display_cards.erase(mainGame->dField.display_cards.begin());
				}
			}
			else if (ekeyCode == irr::KEY_LEFT) {
				mainGame->scrCardList->setPos(pos - 10);
				const unsigned int cardPos = (mainGame->scrCardList->getPos() / 10);
				ScrollCardList();
				if (mainGame->dField.display_cards.front() != mainGame->dField.selectable_cards.front() && cardPos < mainGame->dField.selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
					mainGame->dField.display_cards.insert(mainGame->dField.display_cards.begin(), mainGame->dField.selectable_cards[cardPos]);
					mainGame->dField.display_cards.pop_back();
				}
			}
		}
	}

	void EventHandler::ShowCardInfo()
	{
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->ShowCardInfo(mainGame->dField.display_cards[indexLookedUpCard]->code);
			ReadCardName();
		}
	}

	void EventHandler::ChangeLookedUpField(const irr::SEvent& event, AccessibilityFieldFocus::Player _displayedField, int messageCode)
	{
		displayedField = _displayedField;
		const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(messageCode).data());
		ScreenReader::getReader()->readScreen(nvdaString);
		CloseDialog();
		MouseClick(event, true);
		ChangeFieldAndLook();
	}

	void EventHandler::SetSlot(const irr::SEvent& event, int slot)
	{
		if(mainGame->btnHand[0]->isTrulyVisible() || mainGame->btnOption[0]->isTrulyVisible())
			return;
		if (mainGame->btnDisplayOK->isTrulyVisible())
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		if (!AccessibilityFieldFocus::IsInMainTable(lookupFieldLocId))
			lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
		SelectFieldSlot(slot, displayedField);
		MouseClick(event);
	}

	void EventHandler::RockPaperScissors(irr::EKEY_CODE ekeyCode)
	{
		if (mainGame->btnHand[0]->isTrulyVisible()) {
			int eventCode = 0;
			int messageCode = 0;
			if(ekeyCode == irr::KEY_KEY_1) //Scissors
			{
				eventCode = 0;
				messageCode = 116;
			}
			else if(ekeyCode == irr::KEY_KEY_2) //Rock
			{
				eventCode = 1;
				messageCode = 117;
			}
			else if(ekeyCode == irr::KEY_KEY_3) //Paper
			{
				eventCode = 2;
				messageCode = 118;
			}
			TriggerEvent(mainGame->btnHand[eventCode], irr::gui::EGET_BUTTON_CLICKED);
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(messageCode).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
		}
	}

	void EventHandler::ReplayCommands(const irr::SEvent& event)
	{

		if(event.KeyInput.Key == irr::KEY_KEY_0 || event.KeyInput.Key == irr::KEY_NUMPAD0)
		{
			if (mainGame->btnReplayExit->isTrulyVisible()) {
				TriggerEvent(mainGame->btnReplayExit, irr::gui::EGET_BUTTON_CLICKED);
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(326).data()), false);
			}
		}
		// else if (mainGame->btnReplayStart->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayStart, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(327).data()), false);
		// }
		// else if (mainGame->btnReplaySwap->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplaySwap, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(328).data()), false);
		// }
		// else if (mainGame->btnReplayCancel->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayCancel, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(329).data()), false);
		// }
		// else if (mainGame->btnReplayPause->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayPause, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(330).data()), false);
		// }
		// else if (mainGame->btnReplayStep->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayStep, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(331).data()), false);
		// }
		// else if (mainGame->btnReplayBackward->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayBackward, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(332).data()), false);
		// }
		// else if (mainGame->btnReplayForward->isTrulyVisible()) {
		// 	TriggerEvent(mainGame->btnReplayForward, irr::gui::EGET_BUTTON_CLICKED);
		// 	ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(333).data()), false);
		// }
		// else if (mainGame->btnReplaySwap->isTrulyVisible()) {
		// 	Trigger
	};

	void EventHandler::ReadCardInfo()
	{
		if(mainGame->dField.display_cards.size() <= indexLookedUpCard)
			return;
		const auto selectedCard = mainGame->dField.display_cards[indexLookedUpCard];
		CardModel* card = new CardModel(selectedCard);
		card->SetFieldSlot(SearchFieldSlot(displayedField, selectedCard));
		card->ReadCardInfo();
	};

	void EventHandler::RotateField()
	{
		if (cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE ||
			cardType == AccessibilityFieldFocus::CardType::LINK ||
			cardType == AccessibilityFieldFocus::CardType::GRAVEYARD) {
			ChangeField(AccessibilityFieldFocus::CardType::MONSTER);
			}
		else if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
			ChangeField(AccessibilityFieldFocus::CardType::SPELL);
		}
		else {
			ChangeField(AccessibilityFieldFocus::CardType::LINK);
		}
	}

	void EventHandler::SetCard(const irr::SEvent& event)
	{
		ChangeFieldByCard();
		UseCard(AccessibilityFieldFocus::UseType::SET_CARD, event);
	};

	void EventHandler::PlayerInformation()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(85).data(),mainGame->dInfo.lp[AccessibilityFieldFocus::Player::PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(86).data(), mainGame->dInfo.lp[AccessibilityFieldFocus::Player::ENEMY_PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(87).data(), mainGame->dInfo.time_left[AccessibilityFieldFocus::Player::PLAYER]), false);
	};

	void EventHandler::ConfirmCard(const irr::SEvent& event)
	{
		if (mainGame->btnBP->isEnabled() && battlePhase != AccessibilityFieldFocus::BattleStep::MP1)
			battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		TriggerOk();
		if (mainGame->btnOption[0]->isTrulyVisible()) {
			SetResponseSelectedOption();
		}
		else
			UseSelectedCard(event);

		CloseDialog();
	};

	void EventHandler::ConfirmOnFieldCard(const irr::SEvent& event){
		ChangeFieldByCard();
		MouseClick(event);
	};

	void EventHandler::SeeTurn(){
		if (mainGame->btnEP->isVisible() && mainGame->btnEP->isEnabled() && !mainGame->dInfo.selfnames.empty())
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(83).data(), mainGame->dInfo.selfnames.at(0)), false);
		else if (!mainGame->dInfo.opponames.empty())
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(84).data(), mainGame->dInfo.opponames.at(0)), false);
	};

	void EventHandler::SelectableCards(const irr::SEvent& event)
	{
		if (mainGame->scrCardList->isTrulyVisible())
			SetSelectableCards();
		else
			DisplaySelectableCards(event);
	};

	void EventHandler::ChangeBattlePosition(const irr::SEvent& event)
	{
		cardType = AccessibilityFieldFocus::CardType::MONSTER;
		UseCard(AccessibilityFieldFocus::UseType::CHANGE_MODE, event);
	};

	void EventHandler::DisplayTable(const irr::SEvent& event, AccessibilityFieldFocus::Field fieldLooker, AccessibilityFieldFocus::Player displayedField)
	{
		if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_MONSTERS)
			DisplayMonsterField(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			DisplaySpellField(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS)
			DisplayRemovedCards(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_HAND)
			DisplayHand(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD)
			DisplayGraveyard(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK)
			DisplayExtraDeck(event, displayedField);
		else if(fieldLooker == AccessibilityFieldFocus::Field::PLAYER_DECK)
			DisplayDeck(event, displayedField);
	};

	void EventHandler::ChangeBattlePhase(AccessibilityFieldFocus::BattleStep bp)
	{
		if(bp == AccessibilityFieldFocus::BattleStep::BP && battlePhase != AccessibilityFieldFocus::BattleStep::BP && mainGame->btnBP->isEnabled())
			TriggerBattlePhase();
		else if(bp == AccessibilityFieldFocus::BattleStep::MP2 && battlePhase != AccessibilityFieldFocus::BattleStep::MP2 && mainGame->btnM2->isEnabled())
			TriggerMainPhase2();
		else if(bp == AccessibilityFieldFocus::BattleStep::ED && mainGame->btnEP->isEnabled())
			TriggerEndPhase();

	}

	void EventHandler::SelectOption(const int i)
	{
		if (mainGame->btnOption[i]->isTrulyVisible()) {
			mainGame->dField.selected_option = i;
			SetResponseSelectedOption();
		}
	};

	void EventHandler::NumberKeyEvents(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == irr::KEY_KEY_1 || event.KeyInput.Key == irr::KEY_NUMPAD1)
		{
			if(selectZone)
				SetSlot(event, 1);
			else
				RockPaperScissors(irr::KEY_KEY_1);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_2 || event.KeyInput.Key == irr::KEY_NUMPAD2)
		{
			if(selectZone)
				SetSlot(event, 2);
			else if(rockPaperScissor)
				RockPaperScissors(irr::KEY_KEY_2);
			SelectOption(1);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_3 || event.KeyInput.Key == irr::KEY_NUMPAD3)
		{
			if(selectZone)
				SetSlot(event, 3);
			else if(rockPaperScissor)
				RockPaperScissors(irr::KEY_KEY_3);
			SelectOption(2);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_4 || event.KeyInput.Key == irr::KEY_NUMPAD4)
		{
			if(selectZone)
				SetSlot(event, 4);
			SelectOption(3);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_5 || event.KeyInput.Key == irr::KEY_NUMPAD5)
		{
			if(selectZone)
				SetSlot(event, 5);
			SelectOption(4);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_6 || event.KeyInput.Key == irr::KEY_NUMPAD6)
		{
			if(selectZone)
				SetSlot(event, 6);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_7 || event.KeyInput.Key == irr::KEY_NUMPAD7)
		{
			if(selectZone)
				SetSlot(event, 7);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_0 || event.KeyInput.Key == irr::KEY_NUMPAD0)
			ClickButton(mainGame->btnLeaveGame, Accessibility::Dict::Menu::LEAVE_GAME);

		if(selectZone)
			selectZone = false;
		else if(rockPaperScissor)
			rockPaperScissor = false;
	}

	void EventHandler::DuelCommandsOld(const irr::SEvent& event)
	{

		if(event.KeyInput.Key == KeyboardConfiguration::Chat)
			StartChat();
		else if(event.KeyInput.Key == KeyboardConfiguration::RotateField)
			RotateField();
		else if(event.KeyInput.Key == KeyboardConfiguration::Attack && battlePhase == AccessibilityFieldFocus::BattleStep::BP)
			UseCard(AccessibilityFieldFocus::UseType::MONSTER_ATTACK, event);

		else if(event.KeyInput.Key == KeyboardConfiguration::ActivateCard)
			ActivateCard(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::PlayerInformation)
			PlayerInformation();
		else if(event.KeyInput.Key == KeyboardConfiguration::SelectCard)
			ConfirmCard(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::ConfirmCard)
			ConfirmOnFieldCard(event);
		// else if(event.KeyInput.Key == KeyboardConfiguration::Help)
		// 	ActivateCard(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::SeeTurn)
			SeeTurn();
		else if(event.KeyInput.Key == KeyboardConfiguration::SelectableCards)
			SelectableCards(event);
		else if(event.KeyInput.Key == KeyboardConfiguration::ChangeBattlePosition)
			ChangeBattlePosition(event);
	};

	void EventHandler::MenuCommands(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonYes && mainGame->btnFileSaveYes->isTrulyVisible())
			ClickButton(mainGame->btnFileSaveYes, Accessibility::Dict::Menu::YES, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonYes && mainGame->btnYes->isTrulyVisible())
			ClickButton(mainGame->btnYes, Accessibility::Dict::Menu::YES, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonFirstTurn && mainGame->btnFirst->isTrulyVisible())
			ClickButton(mainGame->btnFirst, Accessibility::Dict::Duel::FIRST_TURN, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonAttackUp && mainGame->btnPSAU->isTrulyVisible())
			ClickButton(mainGame->btnPSAU, Accessibility::Dict::Duel::ATTACK_UP, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonAttackDown && mainGame->btnPSAD->isTrulyVisible())
			ClickButton(mainGame->btnPSAD, Accessibility::Dict::Duel::ATTACK_DOWN, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MouseRightClick)
			MouseClick(event, true);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonNo && mainGame->btnFileSaveNo->isTrulyVisible())
			ClickButton(mainGame->btnFileSaveNo, Accessibility::Dict::Menu::NO, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonNo && mainGame->btnNo->isTrulyVisible())
			ClickButton(mainGame->btnNo, Accessibility::Dict::Menu::NO, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonSecondTurn && mainGame->btnSecond->isTrulyVisible())
			ClickButton(mainGame->btnSecond, Accessibility::Dict::Duel::SECOND_TURN, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonDefenseUp && mainGame->btnPSDU->isTrulyVisible())
			ClickButton(mainGame->btnPSDU, Accessibility::Dict::Duel::DEFENSE_UP, false);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonDefenseDown && mainGame->btnPSDD->isTrulyVisible())
			ClickButton(mainGame->btnPSDD, Accessibility::Dict::Duel::DEFENSE_DOWN, false);
	};

	void EventHandler::FocusOnMenus(){
		if (mainGame->cbANNumber->isTrulyVisible()) {
			FocusAndReadGuiElement(mainGame->cbANNumber, fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected())));
		}
		else if (mainGame->ebANCard->isTrulyVisible()) {
			FocusAndReadGuiElement(mainGame->ebANCard, 111);
		}
		else if (mainGame->wANRace->isTrulyVisible()) {
			FocusAndReadGuiElement(mainGame->wANRace, 112);
		}
		else if (mainGame->wANAttribute->isTrulyVisible()) {
			FocusAndReadGuiElement(mainGame->wANAttribute, 113);
		}
	};

	void EventHandler::MovementCommands(const irr::SEvent& event)
	{
		FocusOnMenus();
		if(event.KeyInput.Key == irr::KEY_UP){
			if (mainGame->cbANNumber->isTrulyVisible())
				AnnounceNumber();
			else if (mainGame->lstANCard->isTrulyVisible())
				AnnounceCard();
			else if (selectAttribute < selectAttributeMax && CheckAttributeSelector())
				AttributeSelector(true);
			else if (selectType < selectTypeMax && CheckTypeSelector())
				RaceSelector(true);
			else if (mainGame->btnOptionn->isTrulyVisible())
				TriggerEvent(mainGame->btnOptionn, irr::gui::EGET_BUTTON_CLICKED);
			else if (mainGame->btnOption[0]->isTrulyVisible() && mainGame->dField.selected_option >= 0 && mainGame->dField.selected_option - 1 < mainGame->dField.select_options.size()) {
				mainGame->dField.selected_option--;
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			}
			else if (mainGame->btnOption[0]->isTrulyVisible())
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			else if (displayedField != AccessibilityFieldFocus::Player::ENEMY_PLAYER) {
				ChangeLookedUpField(event, AccessibilityFieldFocus::Player::ENEMY_PLAYER, 114);
			}
		}
		else if(event.KeyInput.Key == irr::KEY_DOWN){
			if (mainGame->cbANNumber->isTrulyVisible())
				AnnounceNumber();
			else if (selectAttribute > 0 && CheckAttributeSelector())
				AttributeSelector(false);
			else if (selectType > 0 && CheckTypeSelector())
				RaceSelector(false);
			else if (mainGame->btnOptionp->isTrulyVisible())
				TriggerEvent(mainGame->btnOptionp, irr::gui::EGET_BUTTON_CLICKED);
			else if (mainGame->btnOption[0]->isTrulyVisible() && mainGame->dField.selected_option + 1 < mainGame->dField.select_options.size()) {
				mainGame->dField.selected_option++;
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			}
			else if (mainGame->btnOption[0]->isTrulyVisible())
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			else if (mainGame->lstANCard->isTrulyVisible())
				AnnounceCard();
			else if (displayedField != AccessibilityFieldFocus::Player::PLAYER) {
				ChangeLookedUpField(event, AccessibilityFieldFocus::Player::PLAYER, 115);
			}
		}
	}

	void EventHandler::KeyInputEvent(const irr::SEvent& event)
	{
		if(!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX) && mainGame->dInfo.isReplay)
			ReplayCommands(event);
		else if(!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
		{
			DuelMenuController::GetInstance()->KeyInputEvent(event);
			FieldController::GetInstance()->KeyInputEvent(event);
			DuelController::GetInstance()->KeyInputEvent(event);
			CardDisplayController::GetInstance()->KeyInputEvent(event);
			CardController::GetInstance()->KeyInputEvent(event);
			DuelCommandsOld(event);
			MovementCommands(event);
		}
	}

	bool EventHandler::CheckAttributeSelector() {
		const bool isVisible = std::any_of(std::begin(mainGame->chkAttribute), std::end(mainGame->chkAttribute), [](auto& i){return i->isTrulyVisible();});
		// for (auto& i : mainGame->chkAttribute)
		// {
		// 	if (i->isTrulyVisible())
		// 		return true;
		// }
		return isVisible;
	}

	bool EventHandler::CheckTypeSelector() {
		const bool isVisible = std::any_of(std::begin(mainGame->chkRace), std::end(mainGame->chkRace), [](auto& i){return i->isTrulyVisible();});
		// for (auto& i : mainGame->chkRace)
		// {
		// 	if (i->isTrulyVisible())
		// 		return true;
		// }
		return isVisible;
	}

	void EventHandler::AnnounceNumber() {
		if (!mainGame->env->hasFocus(mainGame->cbANNumber))
			mainGame->env->setFocus(mainGame->cbANNumber);
		const std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
		ScreenReader::getReader()->readScreen(nvdaString, false);
	}

	void EventHandler::AnnounceCard() {
		if (!mainGame->env->hasFocus(mainGame->lstANCard))
			mainGame->env->setFocus(mainGame->lstANCard);
		if (mainGame->lstANCard->getSelected() != -1) {
			const std::wstring nvdaString = fmt::format(L"{}", mainGame->lstANCard->getListItem(mainGame->lstANCard->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString, false);
		}
	}

	void EventHandler::AttributeSelector(bool up) {
		if (up) {
			for (int i = selectAttribute + 1; i < selectAttributeMax; i++) {
				if (mainGame->chkAttribute[i]->isVisible()) {
					FocusAndReadCheckBox(mainGame->chkAttribute[i]);
					selectAttribute = i;
					break;
				}
			}
		}
		else {
			for (int i = selectAttribute - 1; i >= 0; i--) {
				if (mainGame->chkAttribute[i]->isVisible()) {
					FocusAndReadCheckBox(mainGame->chkAttribute[i]);
					selectAttribute = i;
					break;
				}
			}
		}
	}

	void EventHandler::RaceSelector(bool up) {
		if (up) {
			for (int i = selectType + 1; i < selectTypeMax; i++) {
				if (mainGame->chkRace[i]->isVisible()) {
					FocusAndReadCheckBox(mainGame->chkRace[i]);
					selectType = i;
					break;
				}
			}
		}
		else {
			for (int i = selectType - 1; i >= 0; i--) {
				if (mainGame->chkRace[i]->isVisible()) {
					FocusAndReadCheckBox(mainGame->chkRace[i]);
					selectType = i;
					break;
				}
			}
		}
	}

	void EventHandler::SpecialSummon(const irr::SEvent& event)
	{
		lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
		cardType = AccessibilityFieldFocus::CardType::MONSTER;
		displayedField = AccessibilityFieldFocus::Player::PLAYER;
		UseCard(AccessibilityFieldFocus::UseType::SPECIAL_SUMMON, event);
	}

	void EventHandler::CloseDialog() {
		if (mainGame->wCardDisplay->isVisible()) {
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		}
	}

	void EventHandler::ScrollCardList() {
		if (mainGame->btnCardSelect[0]->isTrulyVisible()) {
			irr::SEvent newEvent{};
			newEvent.EventType = irr::EEVENT_TYPE::EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = mainGame->scrCardList;
			newEvent.GUIEvent.Element = 0;
			newEvent.GUIEvent.EventType = irr::gui::EGUI_EVENT_TYPE::EGET_SCROLL_BAR_CHANGED;
			mainGame->scrCardList->OnEvent(newEvent);
		}
	}

	void EventHandler::TriggerOk() {
		//if (mainGame->btnCardSelect[indexLookedUpCard]->isTrulyVisible())
		//	TriggerEvent(mainGame->btnCardSelect[indexLookedUpCard], irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnMsgOK->isTrulyVisible())
			TriggerEvent(mainGame->btnMsgOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnOptionOK->isVisible())
			TriggerEvent(mainGame->btnOptionOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnANNumberOK->isTrulyVisible())
			TriggerEvent(mainGame->btnANNumberOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnANCardOK->isTrulyVisible())
			TriggerEvent(mainGame->btnANCardOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnSelectOK->isTrulyVisible())
			TriggerEvent(mainGame->btnSelectOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnDisplayOK->isTrulyVisible())
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnSideOK->isTrulyVisible())
			TriggerEvent(mainGame->btnSideOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnCategoryOK->isTrulyVisible())
			TriggerEvent(mainGame->btnCategoryOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->btnMarksOK->isTrulyVisible())
			TriggerEvent(mainGame->btnMarksOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->chkAttribute[selectAttribute]->isTrulyVisible()) {
			mainGame->chkAttribute[selectAttribute]->setChecked(!mainGame->chkAttribute[selectAttribute]->isChecked());
			TriggerEvent(mainGame->chkAttribute[selectAttribute], irr::gui::EGET_CHECKBOX_CHANGED);
		}
		if (mainGame->chkRace[selectType]->isTrulyVisible()) {
			mainGame->chkRace[selectType]->setChecked(!mainGame->chkRace[selectType]->isChecked());
			TriggerEvent(mainGame->chkRace[selectType], irr::gui::EGET_CHECKBOX_CHANGED);
		}
	}

	void EventHandler::EffectResolver(irr::SEvent event) {
		constexpr float effectResolverXPosition = 0.36f;
		constexpr float effectResolverYPosition = 0.6f;
		const auto cursor = mainGame->device->getCursorControl();
		auto pos = cursor->getRelativePosition();
		pos.X = effectResolverXPosition;
		pos.Y = effectResolverYPosition;
		auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
		clamp(pos.X);
		clamp(pos.Y);
		cursor->setPosition(pos.X, pos.Y);
		MouseClick(event);
		if(mainGame->btnOperation->isTrulyVisible())
			TriggerEvent(mainGame->btnOperation, irr::gui::EGET_BUTTON_CLICKED);
	}

	void EventHandler::GetCardLocation(ClientCard* card) {
		if (card->location == LOCATION_EXTRA)
			mainGame->dField.command_location = LOCATION_EXTRA;
		else if (card->location == LOCATION_DECK)
			mainGame->dField.command_location = LOCATION_DECK;
		else if (card->location == LOCATION_GRAVE)
			mainGame->dField.command_location = LOCATION_GRAVE;
		else if (card->location == LOCATION_REMOVED)
			mainGame->dField.command_location = LOCATION_REMOVED;
	}

	std::wstring EventHandler::GetCardLocationName(ClientCard* card) {
		std::wstring locationName;
		if (card->location == LOCATION_EXTRA)
			locationName = gDataManager->GetAccessibilityString(120).data();
		else if (card->location == LOCATION_DECK)
			locationName = gDataManager->GetAccessibilityString(121).data();
		else if (card->location == LOCATION_GRAVE)
			locationName = gDataManager->GetAccessibilityString(122).data();
		else if (card->location == LOCATION_REMOVED)
			locationName = gDataManager->GetAccessibilityString(123).data();
		else if (card->location == LOCATION_HAND)
			locationName = gDataManager->GetAccessibilityString(124).data();
		else if (card->location == LOCATION_MZONE)
			locationName = gDataManager->GetAccessibilityString(125).data();
		else if (card->location == LOCATION_SZONE)
			locationName = gDataManager->GetAccessibilityString(126).data();
		return locationName;
	}

	bool EventHandler::CheckIfCanViewCards(irr::SEvent event) {
		event.KeyInput.PressedDown = false;
		bool canViewCards = false;
		if (!event.KeyInput.PressedDown && mainGame->dInfo.player_type != 7 && mainGame->dInfo.isInDuel
			&& !mainGame->wCardDisplay->isVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
			canViewCards = true;
		return canViewCards;
	}

	void EventHandler::DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text = L"") {
		mainGame->dField.display_cards.clear();
		indexLookedUpCard = 0;
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
			CloseDialog();
		}
	}

	void EventHandler::DisplayCardsReverse(const std::vector<ClientCard*>& field, const std::wstring& text = L"") {
		mainGame->dField.display_cards.clear();
		indexLookedUpCard = 0;
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
			CloseDialog();
		}
	}

	void EventHandler::SelectCard(const std::vector<ClientCard*>& field, const std::wstring& text = L"") {
		indexLookedUpCard = 0;
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
			CloseDialog();
		}
	}

	void EventHandler::ShowSelectCard() {
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

	void EventHandler::ShowMenu(int flag, int x, int y) {
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
			if (!(mainGame->dField.clicked_card->type & TYPE_MONSTER))
				mainGame->btnSSet->setText(gDataManager->GetSysString(1153).data());
			else
				mainGame->btnSSet->setText(gDataManager->GetSysString(1159).data());
			mainGame->btnSSet->setVisible(true);
			mainGame->btnSSet->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSSet->setVisible(false);
		if (flag & COMMAND_REPOS) {
			if (mainGame->dField.clicked_card->position & POS_FACEDOWN)
				mainGame->btnRepos->setText(gDataManager->GetSysString(1154).data());
			else if (mainGame->dField.clicked_card->position & POS_ATTACK)
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

	bool EventHandler::UseCard(const AccessibilityFieldFocus::UseType& useType, irr::SEvent event, ClientCard* card) {
		bool canUse = false;
		std::wstring command;
		SetLookUpField();
		if (mainGame->wCardDisplay->isVisible())
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		if (mainGame->dField.clicked_card) {
			ShowMenu(card->cmdFlag, 0, 0);
			switch (useType)
			{
			case AccessibilityFieldFocus::UseType::MONSTER_ATTACK: {
				if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_MONSTERS &&
					displayedField == AccessibilityFieldFocus::Player::ENEMY_PLAYER) {
					displayedField = AccessibilityFieldFocus::Player::PLAYER;
					MouseClick(event);
					displayedField = AccessibilityFieldFocus::Player::PLAYER;
					std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(129).data());
					ChangeFieldAndLook(true);
				}
				else {
					ShowMenu(64, 500, 500);
					if (mainGame->btnAttack->isVisible()) {
						TriggerEvent(mainGame->btnAttack, irr::gui::EGET_BUTTON_CLICKED);
						canUse = true;
					}
					else
						command = CommandMessages::ATTACK;
				}
				break;
			}
			case AccessibilityFieldFocus::UseType::CHANGE_MODE: {
				if (mainGame->btnRepos->isVisible()) {
					TriggerEvent(mainGame->btnRepos, irr::gui::EGET_BUTTON_CLICKED);
					canUse = true;
				}
				else
					command = CommandMessages::CHANGE_MODE;
				break;
			}
			case AccessibilityFieldFocus::UseType::SELECT_CARD: {
				SelectFieldSlotHandAllowed(SearchFieldSlot(displayedField), displayedField);
				MouseClick(event);
				canUse = true;
				break;
			}
			default:
				canUse = true;
				if (indexLookedUpCard < mainGame->dField.display_cards.size() && mainGame->btnCardSelect[indexLookedUpCard]->isTrulyVisible()) {
					TriggerEvent(mainGame->btnCardSelect[indexLookedUpCard], irr::gui::EGET_BUTTON_CLICKED);
				}
				break;
			}
		}
		if (!canUse)
			ScreenReader::getReader()->readScreen(AccessibilityMessages::getCommandNotAvaliableMessage(command));
		ShowOptions();
		indexLookedUpCard = 0;
		return canUse;
	}

	void EventHandler::DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text = L"") {
		mainGame->dField.display_cards.clear();
		indexLookedUpCard = 0;
		for (auto it = field.begin(); it != field.end(); ++it) {
			mainGame->dField.display_cards.push_back(it._Ptr->chain_card);
		}
		if (!mainGame->dField.display_cards.empty()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", gDataManager->GetSysString(lookupFieldLocId), mainGame->dField.display_cards.size()).data());
			mainGame->dField.ShowLocationCard();
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
	}

	void EventHandler::SetSelectableCards() {
		indexLookedUpCard = 0;
		if (!mainGame->dField.selectable_cards.empty()) {
			mainGame->dField.display_cards.clear();
			for (int i = 0; i < 5; ++i) {
				if (mainGame->dField.selectable_cards.size() > i)
					mainGame->dField.display_cards.push_back(mainGame->dField.selectable_cards[i]);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[indexLookedUpCard]->code);
		}
		else
		{
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(128).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
			CloseDialog();
		}
	}

	void EventHandler::SelectFieldSlot(int slot, const AccessibilityFieldFocus::Player& player) {
		if (slot == 0) slot = 1;
		const auto cursor = mainGame->device->getCursorControl();
		auto pos = cursor->getRelativePosition();
		const int fieldSlot = GetFieldSlot(slot, player);
		pos.X = GetXPosition(fieldSlot, player);
		pos.Y = GetYPosition(player);
		auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
		clamp(pos.X);
		clamp(pos.Y);
		cursor->setPosition(pos.X, pos.Y);
	}

	void EventHandler::SelectFieldSlotHandAllowed(int slot, const AccessibilityFieldFocus::Player& player) {
		if (slot == 0) slot = 1;
		const auto cursor = mainGame->device->getCursorControl();
		if (GetCardField() == AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND)
			cursor->setPosition(mainGame->dField.clicked_card->hand_collision.getCenter());
		else {
			auto pos = cursor->getRelativePosition();
			const int fieldSlot = GetFieldSlot(slot, player);
			pos.X = GetXPosition(fieldSlot, player);
			pos.Y = GetYPosition(player);
			auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
			clamp(pos.X);
			clamp(pos.Y);
			cursor->setPosition(pos.X, pos.Y);
		}
	}

	float EventHandler::GetXPosition(int slot, const AccessibilityFieldFocus::Player& player) {
		float posX = 0.f;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::LINK_ZONE)
			posX = GetXPositionLink(slot);
		else if (player == AccessibilityFieldFocus::Player::PLAYER)
			posX = GetXPositionPlayer(slot);
		else if (player == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			posX = GetXPositionEnemy(slot);
		return posX;
	}

	float EventHandler::GetXPositionPlayer(int slot) {
		float posX = 0.f;
		constexpr auto fieldSlotSize = 0.08;
		constexpr float startPosition = 0.40f;
		if (slot > 5 && lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			slot = -0.5;//041
		float localSlot = slot;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS)
			localSlot = 6;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD)
			localSlot = 6.3;
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_DECK)
			localSlot = 6.5f;
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK)
			localSlot = -0.5;
		posX = startPosition + (localSlot * fieldSlotSize);
		return posX;
	}

	float EventHandler::GetXPositionEnemy(int slot) {
		float posX = 0.f;
		constexpr auto fieldSlotSize = 0.073f;
		constexpr float startPosition = 0.43f;
		if (slot == 0 && lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS) {
			slot = 6;//041
		}
		int localSlot = slot;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD || lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_DECK) {
			localSlot = 6;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS) {
			localSlot = 0;
		}
		posX = startPosition + (localSlot * fieldSlotSize);
		return posX;
	}

	float EventHandler::GetXPositionLink(int slot) {
		cardType = AccessibilityFieldFocus::CardType::LINK;

		float posX = 0.f;
		constexpr auto fieldSlotSize = 0.08;
		switch (slot)
		{
		case 1: {
			posX = 0.40 + (2 * fieldSlotSize);
			break;
		}
		case 2:
		case 4:
		case 5:
		case 6: {
			posX = 0.40 + (4 * fieldSlotSize);
			break;
		}
		default:
			posX = 0.60;
			break;
		}
		return posX;
	}

	float EventHandler::GetXPosition(const AccessibilityFieldFocus::Scroll& position) {
		float posX = 0.f;
		switch (position)
		{
		case ygo::AccessibilityFieldFocus::Scroll::RIGHT: {
			posX = 0.94f;
			break;
		}
		case ygo::AccessibilityFieldFocus::Scroll::LEFT: {
			posX = 0.36f;
			break;
		}
		default:
			break;
		}
		return posX;
	}


	float EventHandler::GetYPosition(const AccessibilityFieldFocus::Player& player) {
		float posX = 0.f;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::LINK_ZONE)
			posX = GetYPositionLink();
		else if (player == AccessibilityFieldFocus::Player::PLAYER)
			posX = GetYPositionPlayer();
		else if (player == AccessibilityFieldFocus::Player::ENEMY_PLAYER)
			posX = GetYPositionEnemy();
		return posX;
	}

	float EventHandler::GetYPositionPlayer() {
		float posY = 0.f;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_MONSTERS) {
			posY = 0.64f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD) {
			posY = 0.68f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS) {
			posY = 0.72f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_DECK || lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK) {
			posY = 0.8f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS) {
			posY = 0.55f;
		}
		return posY;
	}

	float EventHandler::GetYPositionEnemy() {
		float posY = 0.f;
		float startSpellPosY = 0.f;
		float LinkSummonZoneY = 0.515f;
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_MONSTERS) {
			posY = 0.41f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS) {
			posY = 0.43f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD) {
			posY = 0.39f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS) {
			posY = 0.35f;
		}
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_DECK || lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK) {
			posY = 0.30f;
		}
		return posY;
	}

	float EventHandler::GetYPositionLink() {
		constexpr float linkSummonZoneY = 0.515f;
		return linkSummonZoneY;
	}

	void EventHandler::ChangeFieldByCard() {
		bool selected = false;
		if (!mainGame->dField.clicked_card)
			return;
		for (int i = 0; i < 6; i++) {
			if (mainGame->dField.mzone[0][i] && mainGame->dField.mzone[0][i] == mainGame->dField.clicked_card) {
				cardType = AccessibilityFieldFocus::CardType::MONSTER;
				lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
				selected = true;
				break;
			}
			else if (mainGame->dField.szone[0][i] && mainGame->dField.szone[0][i] == mainGame->dField.clicked_card) {
				cardType = AccessibilityFieldFocus::CardType::SPELL;
				lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
				selected = true;
				break;
			}
		}
		if (!selected) {
			const std::wstring cardTypeString = fmt::format(L"{}", gDataManager->FormatType(mainGame->dField.clicked_card->type));
			if (cardTypeString.find(gDataManager->GetAccessibilityString(76).data()) == std::string::npos && cardTypeString.find(gDataManager->GetAccessibilityString(77).data()) == std::string::npos) {
				lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
				cardType = AccessibilityFieldFocus::CardType::MONSTER;
			}
			else {
				lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
				cardType = AccessibilityFieldFocus::CardType::SPELL;
			}
		}
	}

	AccessibilityFieldFocus::DisplayedCards EventHandler::GetCardField() {
		for (int i = 0; i < mainGame->dField.hand[0].size(); i++) {
			if (mainGame->dField.hand[0].size() > i && mainGame->dField.hand[0][i] == mainGame->dField.clicked_card) {
				return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
			}
			else if (mainGame->dField.hand[1].size() > i && mainGame->dField.hand[1][i] == mainGame->dField.clicked_card) {
				return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
			}
		}
		return AccessibilityFieldFocus::DisplayedCards::DISPLAY_FIELD;
	}

	int EventHandler::GetFieldSlot(const int& slot, const AccessibilityFieldFocus::Player& player, const AccessibilityFieldFocus::CardType& cardType) {
		if (player == AccessibilityFieldFocus::Player::PLAYER && cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE)
			return slot;
		else if (player == AccessibilityFieldFocus::Player::ENEMY_PLAYER && cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE) {
			return 6 - slot;
		}
		int fieldSlot = 1;
		for (int i = 0; i < 5; i++) {
			if (mainGame->dField.mzone[1][i] && mainGame->dField.mzone[1][i] == mainGame->dField.clicked_card) {
				fieldSlot = 5 - i;
				break;
			}
		}
		return fieldSlot;
	}

	void EventHandler::CheckFreeSlots(const AccessibilityFieldFocus::Player& player, const int& cardType, bool isLink) {
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

	void EventHandler::SetLookUpField() {
		//if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_DECK) {
		//	lookupFieldLocId = AccessibilityFieldFocus::PLAYER_DECK;
		//	cardType = AccessibilityFieldFocus::CardType::DECK;
		//}
		//else
		if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_MONSTERS) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
			cardType = AccessibilityFieldFocus::CardType::MONSTER;
			//ChangeField(AccessibilityFieldFocus::CardType::MONSTER);
		}
		else if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_SPELLS) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
			cardType = AccessibilityFieldFocus::CardType::SPELL;
			//ChangeField(AccessibilityFieldFocus::CardType::SPELL);
		}
		else if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_GRAVEYARD) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_GRAVEYARD;
			cardType = AccessibilityFieldFocus::CardType::GRAVEYARD;
		}
		//else if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_BANNED_CARDS) {
		//	lookupFieldLocId = AccessibilityFieldFocus::PLAYER_BANNED_CARDS;
		//	cardType = AccessibilityFieldFocus::CardType::BANNED;
		//}
		else if (mainGame->dField.clicked_card && mainGame->dField.clicked_card->location == AccessibilityFieldFocus::PLAYER_EXTRA_DECK) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_EXTRA_DECK;
			cardType = AccessibilityFieldFocus::CardType::EXTRA_DECK;
		}
	}

	void EventHandler::ReadCardName() {
		std::wstring nvdaString;
		SetLookUpField();
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_MONSTERS || lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS) {
			if (mainGame->dField.display_cards[indexLookedUpCard]->code != 0) {
				const int slot = SearchFieldSlot(displayedField, mainGame->dField.display_cards[indexLookedUpCard]);
				nvdaString = fmt::format(gDataManager->GetAccessibilityString(136).data(), gDataManager->GetName(mainGame->dField.display_cards[indexLookedUpCard]->code), mainGame->dField.display_cards[indexLookedUpCard]->attack, mainGame->dField.display_cards[indexLookedUpCard]->defense);
				if (mainGame->dField.display_cards[indexLookedUpCard]->is_selected)
					nvdaString.append(gDataManager->GetAccessibilityString(137).data());
				if (slot != 0)
					nvdaString.append(fmt::format(L" {} {}", GetCardLocationName(mainGame->dField.display_cards[indexLookedUpCard]), mainGame->dField.display_cards[indexLookedUpCard]->position));
			}
			else
				nvdaString = fmt::format(gDataManager->GetAccessibilityString(138).data(), SearchFieldSlot(displayedField, mainGame->dField.display_cards[indexLookedUpCard]));
		}
		else {
			if (mainGame->dField.display_cards[indexLookedUpCard]->code != 0) {
				nvdaString = fmt::format(gDataManager->GetAccessibilityString(139).data(), gDataManager->GetName(mainGame->dField.display_cards[indexLookedUpCard]->code), indexLookedUpCard);
				if (mainGame->dField.display_cards[indexLookedUpCard]->is_selected)
					nvdaString.append(gDataManager->GetAccessibilityString(137).data());
				else
					nvdaString.append(gDataManager->GetAccessibilityString(140).data());

				nvdaString.append(fmt::format(L" {} {}", GetCardLocationName(mainGame->dField.display_cards[indexLookedUpCard]), mainGame->dField.display_cards[indexLookedUpCard]->sequence));
			}
			else
				nvdaString = fmt::format(gDataManager->GetAccessibilityString(141).data(), indexLookedUpCard);
		}
		ScreenReader::getReader()->readScreen(nvdaString);
	}

	void EventHandler::ChangeFieldAndLook(bool click)
	{
		if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_HAND)
			DisplayCards(mainGame->dField.hand[displayedField], fmt::format(gDataManager->GetAccessibilityString(124).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_MONSTERS)
			DisplayCards(mainGame->dField.mzone[displayedField], fmt::format(gDataManager->GetAccessibilityString(125).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_SPELLS)
			DisplayCards(mainGame->dField.szone[displayedField], fmt::format(gDataManager->GetAccessibilityString(66).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_EXTRA_DECK)
			DisplayCards(mainGame->dField.extra[displayedField], fmt::format(gDataManager->GetAccessibilityString(92).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_GRAVEYARD)
			DisplayCards(mainGame->dField.grave[displayedField], fmt::format(gDataManager->GetAccessibilityString(93).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_BANNED_CARDS)
			DisplayCards(mainGame->dField.remove[displayedField], fmt::format(gDataManager->GetAccessibilityString(142).data()));
		else if (lookupFieldLocId == AccessibilityFieldFocus::Field::PLAYER_DECK)
			DisplayCards(mainGame->dField.deck[displayedField], fmt::format(gDataManager->GetAccessibilityString(143).data()));
	}

	int EventHandler::SearchFieldSlot(const int& localDisplayedField, ClientCard* card, bool looped) {
		SetLookUpField();
		const auto selectedCard = card == NULL ? mainGame->dField.clicked_card : card;
		int fieldSlot = 0;
		//Busca a carta no campo selecionado;
		if (lookupFieldLocId != AccessibilityFieldFocus::PLAYER_GRAVEYARD &&
			lookupFieldLocId != AccessibilityFieldFocus::PLAYER_EXTRA_DECK &&
			lookupFieldLocId != AccessibilityFieldFocus::PLAYER_BANNED_CARDS) {
			for (int i = 0; i < 7; i++) {
				if ((mainGame->dField.mzone[localDisplayedField][i] && mainGame->dField.mzone[localDisplayedField][i] == selectedCard) || (mainGame->dField.szone[localDisplayedField][i] && mainGame->dField.szone[localDisplayedField][i] == selectedCard)) {
					if (localDisplayedField == AccessibilityFieldFocus::Player::PLAYER && i < 5)
						fieldSlot = i + 1;
					else if (i < 5)
						fieldSlot = 5 - i;
					else if (mainGame->dField.szone[localDisplayedField][i] == selectedCard)
						fieldSlot = i + 1;
					else {
						lookupFieldLocId = AccessibilityFieldFocus::Field::LINK_ZONE;
						if (localDisplayedField == AccessibilityFieldFocus::Player::PLAYER)
							fieldSlot = i - 4;
						else {
							if (i == 5)
								fieldSlot = 2;
							else
								fieldSlot = 1;
						}
					}
					break;
				}
			}
		}
		if (fieldSlot != 0) {
			displayedField = localDisplayedField == AccessibilityFieldFocus::Player::PLAYER ? AccessibilityFieldFocus::Player::PLAYER : AccessibilityFieldFocus::Player::ENEMY_PLAYER;
			if (fieldSlot < 6)
				fieldSlot = GetFieldSlot(fieldSlot, displayedField);
		}
		//Caso não encontre a carta, busca no outro campo;
		if (fieldSlot == 0 && !looped) {
			const AccessibilityFieldFocus::Player newDisplayedField = localDisplayedField == AccessibilityFieldFocus::Player::PLAYER ? AccessibilityFieldFocus::Player::ENEMY_PLAYER : AccessibilityFieldFocus::Player::PLAYER;
			fieldSlot = SearchFieldSlot(newDisplayedField, selectedCard, true);
		}
		return fieldSlot;
	}

	void EventHandler::ShowOptions()
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

	void EventHandler::ChangeField(const AccessibilityFieldFocus::CardType& cardField) {
		std::wstring nvdaString;
		cardType = cardField;
		if (cardType == AccessibilityFieldFocus::CardType::LINK) {
			lookupFieldLocId = AccessibilityFieldFocus::LINK_ZONE;
			cardType = AccessibilityFieldFocus::LINK;
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(144).data());
		}
		else if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(145).data());
		}
		else if (cardType == AccessibilityFieldFocus::CardType::SPELL) {
			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
			nvdaString = fmt::format(gDataManager->GetAccessibilityString(146).data());
		}
		ScreenReader::getReader()->readScreen(nvdaString);
	}

	void EventHandler::SetResponseSelectedOption() const {
		if (mainGame->dInfo.curMsg == MSG_SELECT_OPTION) {
			DuelClient::SetResponseI(mainGame->dField.selected_option);
		}
		else {
			int index = 0;
			while (mainGame->dField.activatable_cards[index] != mainGame->dField.command_card || mainGame->dField.activatable_descs[index].first != mainGame->dField.select_options[mainGame->dField.selected_option]) index++;
			if (mainGame->dInfo.curMsg == MSG_SELECT_IDLECMD) {
				DuelClient::SetResponseI((index << 16) + 5);
			}
			else if (mainGame->dInfo.curMsg == MSG_SELECT_BATTLECMD) {
				DuelClient::SetResponseI(index << 16);
			}
			else {
				DuelClient::SetResponseI(index);
			}
		}
		mainGame->HideElement(mainGame->wOptions, true);
	}

	void EventHandler::MouseClick(const irr::SEvent& event, bool rightClick) {
		auto cursor = mainGame->device->getCursorControl();
		auto pos = cursor->getRelativePosition();

		auto& jevent = event.JoystickEvent;
		static irr::u32 buttonstates = 0;
		buttonstates |= irr::E_MOUSE_BUTTON_STATE_MASK::EMBSM_LEFT;
		irr::SEvent simulated{};
		simulated.EventType = irr::EET_MOUSE_INPUT_EVENT;
		simulated.MouseInput.ButtonStates = buttonstates;
		simulated.MouseInput.Control = false;
		simulated.MouseInput.Shift = false;
		simulated.MouseInput.X = irr::core::round32(pos.X * mainGame->window_size.Width);
		simulated.MouseInput.Y = irr::core::round32(pos.Y * mainGame->window_size.Height);

		buttonstates |= (simulated.MouseInput.Control) ? 1 << 30 : 0;
		buttonstates |= (simulated.MouseInput.Shift) ? 1 << 29 : 0;

		auto& changed = jevent.POV;

		auto CheckAndPost = [device = mainGame->device, &simulated, &changed, &states = jevent.ButtonStates](int button, irr::EMOUSE_INPUT_EVENT type) {
			simulated.MouseInput.Event = (states & button) ? type : (irr::EMOUSE_INPUT_EVENT)(type + 3);
			device->postEventFromUser(simulated);
		};

		CheckAndPost(JWrapper::Buttons::A, rightClick ? irr::EMIE_RMOUSE_PRESSED_DOWN : irr::EMIE_LMOUSE_PRESSED_DOWN);
	}

	void EventHandler::CancelOrFinish()
	{
		DuelClient::SetResponseI(0);
	}

	void EventHandler::GuiEvent(const irr::SEvent& event)
	{
		const int id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED: {
				switch (id) {
					case BUTTON_ANCARD_OK: {
						if (AccessibilityConfiguration::accessibilityShortcuts) {
							if (mainGame->lstANCard->getSelected() != -1) {
								const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(147).data(), mainGame->lstANCard->getListItem(mainGame->lstANCard->getSelected()));
								ScreenReader::getReader()->readScreen(nvdaString, false);
							}
						}
						break;
					}
					case BUTTON_CMD_ATTACK: {
						//This changes the cards to the enemy field when attacking a monster, so the player doesn't have to do this manually
						if (AccessibilityConfiguration::accessibilityShortcuts) {
							bool hasMonster = false;
							for (auto it = mainGame->dField.mzone[AccessibilityFieldFocus::Player::ENEMY_PLAYER].begin(); it != mainGame->dField.mzone[AccessibilityFieldFocus::Player::ENEMY_PLAYER].end(); ++it) {
								if (*it) {
									hasMonster = true;
									break;
								}
							}
							if (hasMonster) {
								displayedField = AccessibilityFieldFocus::Player::ENEMY_PLAYER;
								if (CheckIfCanViewCards(event)) {
									lookupFieldLocId = AccessibilityFieldFocus::Field::PLAYER_MONSTERS;
									cardType = AccessibilityFieldFocus::CardType::MONSTER;
									SelectCard(mainGame->dField.mzone[displayedField], fmt::format(gDataManager->GetAccessibilityString(95).data()));
								}
							}
							else
								displayedField = AccessibilityFieldFocus::Player::PLAYER;
						}
						break;
					}
				}
			}
			case irr::gui::EGET_CHECKBOX_CHANGED: {
				switch (id) {
					case CHECK_ATTRIBUTE: {
						if (AccessibilityConfiguration::accessibilityShortcuts) {
							const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(148).data(), mainGame->chkAttribute[selectAttribute]->getText());
							ScreenReader::getReader()->readScreen(nvdaString, false);
							selectAttribute = 0;
						}
					}
					case CHECK_RACE: {
						if (AccessibilityConfiguration::accessibilityShortcuts) {
							const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(149).data(), mainGame->chkRace[selectType]->getText());
							ScreenReader::getReader()->readScreen(nvdaString, false);
							selectType = 0;
						}
						break;
					}
				}
			}
		}
	}
}
