#include "DeckHandler.h"
#include <fmt/format.h>
#include <fmt/printf.h>
#include "../gframe/data_manager.h"
#include "../ScreenReader/StringBuilder.h"
#include "../ScreenReader/ScreenReader.h"

namespace ygo {
	IEventHandler* DeckHandler::deckHandler = nullptr;
	int DeckHandler::indexLookedUpCard = 0;

	static inline void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
		irr::SEvent event;
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		ygo::mainGame->device->postEventFromUser(event);
		if(target == mainGame->btnSaveDeck)
			mainGame->env->removeFocus(mainGame->env->getFocus());
	}

	static inline void ReadComboBox(irr::gui::IGUIComboBox* comboBox) {
		if (comboBox->isTrulyVisible()) {
			std::wstring nvdaString = fmt::format(L"{}", comboBox->getItem(comboBox->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		}
	}

	static inline void ClickButton(irr::gui::IGUIElement* btn) {
		TriggerEvent(btn, irr::gui::EGET_BUTTON_CLICKED);
	}

	IEventHandler* DeckHandler::getDeckHandler()
	{
		if (deckHandler == nullptr)
			deckHandler = new DeckHandler();
		return deckHandler;
	}

	void DeckHandler::KeyInputEvent(const irr::SEvent& event)
	{

	}

	void DeckHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void DeckHandler::RightKeyLookCard(const std::vector<const CardDataC*>& deck) {
		if (!deck.empty() && deck.size() == 1)
			indexLookedUpCard = 0;
		else if (!deck.empty() && indexLookedUpCard < deck.size() - 1)
			indexLookedUpCard++;

		if (!deck.empty() && indexLookedUpCard < deck.size()) {
			mainGame->ShowCardInfo(deck[indexLookedUpCard]->code);
			ReadCardName(deck);
		}
	}

	void DeckHandler::LeftKeyLookCard(const std::vector<const CardDataC*>& deck) {
		if (!deck.empty() && deck.size() == 1)
			indexLookedUpCard = 0;
		else if (deck.size() && indexLookedUpCard <= deck.size() && indexLookedUpCard > 0)
			indexLookedUpCard--;
		if (!deck.empty() && indexLookedUpCard <= deck.size()) {
			mainGame->ShowCardInfo(deck[indexLookedUpCard]->code);
			ReadCardName(deck);
		}
	}

	std::wstring DeckHandler::GetCardLimit(const CardDataC* card)
	{
		std::wstring limited = std::wstring();
		int limit = mainGame->deckBuilder.filterList->whitelist ? 0 : 3;
		auto endit = mainGame->deckBuilder.filterList->content.end();
		auto it = mainGame->deckBuilder.filterList->GetLimitationIterator(card);
		if (it != endit)
			limit = it->second;
		if (limit == 0)
			limited = gDataManager->GetAccessibilityString(167).data();
		else if (limit != 0)
			limited = fmt::format(gDataManager->GetAccessibilityString(168).data(), limit);
		return limited;
	}

	void DeckHandler::ReadCardName(const std::vector<const CardDataC*> &deck) {
		std::wstring nvdaString;
		std::wstring cardType = gDataManager->FormatType(deck[indexLookedUpCard]->type);
		if (deck.size() > indexLookedUpCard && deck[indexLookedUpCard]->code != 0) {
			if (cardType.find(gDataManager->GetAccessibilityString(76).data()) == std::string::npos && cardType.find(gDataManager->GetAccessibilityString(77).data()) == std::string::npos)
				nvdaString = fmt::format(gDataManager->GetAccessibilityString(169).data(), gDataManager->GetName(deck[indexLookedUpCard]->code), gDataManager->FormatType(deck[indexLookedUpCard]->type), deck[indexLookedUpCard]->attack, deck[indexLookedUpCard]->defense);
			else
				nvdaString = fmt::format(L"{}, {}", gDataManager->GetName(deck[indexLookedUpCard]->code), gDataManager->FormatType(deck[indexLookedUpCard]->type));
		}
		ScreenReader::getReader()->readScreen(nvdaString.c_str());
	}

	void DeckHandler::DeckOptionsMenu() {
		if (menuSelectCounter == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_SELECT_DECK && mainGame->cbDBDecks->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbDBDecks);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(170).data(), mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				scrollSelected = false;
				newDeck = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_SEARCH && mainGame->ebCardName->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebCardName);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(171).data());
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(172).data(), mainGame->ebCardName->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_CATEGORY && mainGame->cbCardType->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbCardType);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(173).data(), mainGame->cbCardType->getItem(mainGame->cbCardType->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_SUB_CATEGORY && mainGame->cbCardType2->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbCardType2);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(174).data(), mainGame->cbCardType2->getItem(mainGame->cbCardType2->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTRIBUTE && mainGame->cbAttribute->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbAttribute);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(175).data(), mainGame->cbAttribute->getItem(mainGame->cbAttribute->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_TYPE && mainGame->cbRace->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbRace);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(176).data(), mainGame->cbRace->getItem(mainGame->cbRace->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_LEVEL && mainGame->ebStar->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebStar);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(177).data());
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(178).data(), mainGame->ebStar->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_SCALE && mainGame->ebScale->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebScale);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(179).data());
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(180).data(), mainGame->ebScale->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_LIMIT && mainGame->cbLimit->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbLimit);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(181).data(), mainGame->cbLimit->getItem(mainGame->cbLimit->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTACK && mainGame->ebAttack->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebAttack);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(182).data());
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(183).data(), mainGame->ebAttack->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_DEFENSE && mainGame->ebDefense->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebDefense);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(184).data());
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(185).data(), mainGame->ebDefense->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == AccessibilityDeckFocus::SearchCardMenu::SCARD_CLEAR_SEARCH && mainGame->btnClearFilter->isEnabled()) {
			ClickButton(mainGame->btnClearFilter);
		}
	}
}
