#pragma once
#include <string>
#include <vector>
#include "../accessibility/ScreenReader/ScreenReader.h"
#include "../gframe/data_manager.h"

/**
 * \brief Used to store card data during a Battle or in the Deck Editor
 */
class CardModel
{
public:
	std::wstring cardName;
	std::wstring cardType;
	std::wstring cardAttribute;
	std::wstring cardLevel;
	std::wstring cardRace;
	std::wstring cardAttack;
	std::wstring cardDefense;
	std::wstring cardEffect;
	std::wstring position;
	std::wstring leftScale;
	std::wstring rightScale;
	std::wstring fieldSlot;
	std::wstring linkMarks;
	std::wstring overlayedCards;
	std::wstring location;
	std::wstring limited;
	std::wstring cardFace;
	uint8_t selectedPosition;
	bool isLink = false;
	bool isSelected = false;
	bool isFaceUp = false;

	/**
	 * \brief Used to store card data during a Battle
	 * \param selectedCard - Selected card to read data
	 */
	CardModel(ygo::ClientCard* selectedCard)
	{
		cardName = fmt::format(L"{}", ygo::gDataManager->GetName(selectedCard->code));
		cardType = fmt::format(L"{}", ygo::gDataManager->FormatType(selectedCard->type));
		cardAttribute = fmt::format(L"{}", ygo::gDataManager->FormatAttribute(selectedCard->attribute));
		SetLevel(selectedCard);
		cardRace = fmt::format(L"{}", ygo::gDataManager->FormatRace(selectedCard->race));
		cardAttack = fmt::format(ygo::gDataManager->GetAccessibilityString(69).data(), selectedCard->attack);
		cardDefense = fmt::format(ygo::gDataManager->GetAccessibilityString(70).data(), selectedCard->defense);
		cardEffect = fmt::format(L"{}", ygo::gDataManager->GetText(selectedCard->code));
		leftScale = fmt::format(ygo::gDataManager->GetAccessibilityString(73).data(), selectedCard->lscstring);
		rightScale = fmt::format(ygo::gDataManager->GetAccessibilityString(74).data(), selectedCard->rscstring);
		linkMarks = GetLinkMarks(selectedCard);
		overlayedCards = GetOverlayedCards(selectedCard);
		location = fmt::format(L"{}[{}]", ygo::gDataManager->FormatLocation(selectedCard->location, selectedCard->sequence), selectedCard->sequence + 1);
		selectedPosition = 0;
		isSelected = ygo::gDataManager->GetAccessibilityString(selectedCard->is_selected ? 137 : 140).data();
		isFaceUp = selectedCard->code != 0 ? true : false;
		cardFace = fmt::format(L"Face {}", isFaceUp ? L"Up" : L"Down");
	}

	/**
	 * \brief Used to store card data in the deck editor menu
	 * \param selectedCard - Selected card to read data
	 */
	CardModel(const ygo::CardDataC* selectedCard)
	{
		cardName = fmt::format(L"{}", ygo::gDataManager->GetName(selectedCard->code));
		cardType = fmt::format(L"{}", ygo::gDataManager->FormatType(selectedCard->type));
		cardAttribute = fmt::format(L"{}", ygo::gDataManager->FormatAttribute(selectedCard->attribute));
		SetLevel(selectedCard);
		cardRace = fmt::format(L"{}", ygo::gDataManager->FormatRace(selectedCard->race));
		cardAttack = fmt::format(ygo::gDataManager->GetAccessibilityString(69).data(), selectedCard->attack);
		cardDefense = fmt::format(ygo::gDataManager->GetAccessibilityString(70).data(), selectedCard->defense);
		cardEffect = fmt::format(L"{}", ygo::gDataManager->GetText(selectedCard->code));
		leftScale = fmt::format(ygo::gDataManager->GetAccessibilityString(73).data(), selectedCard->lscale);
		rightScale = fmt::format(ygo::gDataManager->GetAccessibilityString(74).data(), selectedCard->rscale);
		linkMarks = GetLinkMarks(selectedCard);
		limited = GetCardLimit(selectedCard);
		selectedPosition = 0;
	}

	static bool IsLink(const ygo::ClientCard* selectedCard)
	{
		const std::wstring cardType = fmt::format(L"{}", ygo::gDataManager->FormatType(selectedCard->type));
		return cardType.find(L"Link") != std::wstring::npos;
	}

	void SetFieldSlot(int slot)
	{
		fieldSlot = fmt::format(ygo::gDataManager->GetAccessibilityString(75).data(), slot);
	}


	/**
	 * \brief Read all available information about this card
	 */
	void ReadCardInfo()
	{
		ScreenReader::getReader()->readScreen(cardName, false);
		if(!location.empty())
			ScreenReader::getReader()->readScreen(location, false);
		if (fieldSlot != fmt::format(ygo::gDataManager->GetAccessibilityString(75).data(), 0))
			ScreenReader::getReader()->readScreen(fieldSlot, false);
		if (selectedPosition != 10)
			ScreenReader::getReader()->readScreen(position, false);
		ScreenReader::getReader()->readScreen(cardType, false);
		ScreenReader::getReader()->readScreen(cardAttribute, false);
		if (cardType.find(ygo::gDataManager->GetAccessibilityString(76).data()) == std::string::npos &&
			cardType.find(ygo::gDataManager->GetAccessibilityString(77).data()) == std::string::npos) {
			ScreenReader::getReader()->readScreen(cardLevel, false);
			ScreenReader::getReader()->readScreen(cardRace, false);
			ScreenReader::getReader()->readScreen(cardAttack, false);
			ScreenReader::getReader()->readScreen(cardDefense, false);
		}
		if (!linkMarks.empty())
			ScreenReader::getReader()->readScreen(fmt::format(ygo::gDataManager->GetAccessibilityString(78).data(), linkMarks), false);
		if (!overlayedCards.empty())
			ScreenReader::getReader()->readScreen(fmt::format(ygo::gDataManager->GetAccessibilityString(79).data(), overlayedCards), false);
		if (leftScale != ygo::gDataManager->GetAccessibilityString(80).data())
			ScreenReader::getReader()->readScreen(leftScale, false);
		if (rightScale != ygo::gDataManager->GetAccessibilityString(81).data())
			ScreenReader::getReader()->readScreen(rightScale, false);
		ScreenReader::getReader()->readScreen(cardEffect, false);
		if (!limited.empty())
			ScreenReader::getReader()->readScreen(limited, false);
	}

	/**
	 * \brief Read resumed some info about this card, like name, type, level, race, attack, defense and limit number when making a deck
	 */
	void ReadCardResumedInfo()
	{
		ScreenReader::getReader()->readScreen(cardName, false);
		ScreenReader::getReader()->readScreen(cardType, false);
		if (cardType.find(ygo::gDataManager->GetAccessibilityString(76).data()) == std::string::npos &&
			cardType.find(ygo::gDataManager->GetAccessibilityString(77).data()) == std::string::npos) {
			ScreenReader::getReader()->readScreen(cardLevel, false);
			ScreenReader::getReader()->readScreen(cardRace, false);
			ScreenReader::getReader()->readScreen(cardAttack, false);
			ScreenReader::getReader()->readScreen(cardDefense, false);
		}
		if (!limited.empty())
			ScreenReader::getReader()->readScreen(limited, false);
	}

	/**
	 * \brief Read basic info about this card, like name, type, level, race, attack, defense and limit number when making a deck
	 */
	void ReadCardBasicInfo()
	{
		ScreenReader::getReader()->readScreen(cardName, false);
		if (cardType.find(ygo::gDataManager->GetAccessibilityString(76).data()) == std::string::npos &&
			cardType.find(ygo::gDataManager->GetAccessibilityString(77).data()) == std::string::npos) {
			ScreenReader::getReader()->readScreen(cardAttack, false);
			ScreenReader::getReader()->readScreen(cardDefense, false);
		}
		ScreenReader::getReader()->readScreen(location, false);
		if (selectedPosition != 10)
			ScreenReader::getReader()->readScreen(position, false);
		ScreenReader::getReader()->readScreen(cardFace, false);
	}

	int GetCardType()
	{
		int type = ygo::AccessibilityFieldFocus::CardType::MONSTER;
		if(cardType.find(ygo::gDataManager->GetAccessibilityString(ygo::AccessibilityFieldFocus::CardType::SPELL).data()) != std::string::npos)
			type = ygo::AccessibilityFieldFocus::CardType::SPELL;
		else if(cardType.find(ygo::gDataManager->GetAccessibilityString(ygo::AccessibilityFieldFocus::CardType::TRAP).data()) != std::string::npos)
			type = ygo::AccessibilityFieldFocus::CardType::TRAP;
		return type;
	}

private:
	void SetLevel(const ygo::ClientCard* selectedCard)
	{
		cardLevel = selectedCard->link_marker != 0 ?
			fmt::format(ygo::gDataManager->GetAccessibilityString(67).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level) :
			fmt::format(ygo::gDataManager->GetAccessibilityString(68).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level);
	}


	void SetLevel(const ygo::CardDataC* selectedCard)
	{
		cardLevel = selectedCard->link_marker != 0 ?
			fmt::format(ygo::gDataManager->GetAccessibilityString(67).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level) :
			fmt::format(ygo::gDataManager->GetAccessibilityString(68).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level);
	}

	void SetPosition(const ygo::ClientCard* selectedCard)
	{
		selectedPosition = selectedCard->position;
		position = selectedCard->position == 1 ? fmt::format(ygo::gDataManager->GetAccessibilityString(71).data()) : fmt::format(ygo::gDataManager->GetAccessibilityString(72).data());
	}

	std::wstring GetLinkMarks(const ygo::ClientCard* selectedCard)
	{
		std::wstring _linkMark = std::wstring();
		const uint32_t mark = selectedCard->link_marker;
		if (mark & LINK_MARKER_BOTTOM_LEFT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(130).data();
		}
		if (mark & LINK_MARKER_BOTTOM) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(131).data();
		}
		if (mark & LINK_MARKER_BOTTOM_RIGHT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(132).data();
		}
		if (mark & LINK_MARKER_TOP_LEFT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(133).data();
		}
		if (mark & LINK_MARKER_TOP) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(134).data();
		}
		if (mark & LINK_MARKER_TOP_RIGHT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(135).data();
		}
		if(!_linkMark.empty())
			isLink = true;
		return _linkMark;
	}

	std::wstring GetLinkMarks(const ygo::CardDataC* selectedCard)
	{
		std::wstring _linkMark = std::wstring();
		const uint32_t mark = selectedCard->link_marker;
		if (mark & LINK_MARKER_BOTTOM_LEFT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(130).data();
		}
		if (mark & LINK_MARKER_BOTTOM) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(131).data();
		}
		if (mark & LINK_MARKER_BOTTOM_RIGHT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(132).data();
		}
		if (mark & LINK_MARKER_TOP_LEFT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(133).data();
		}
		if (mark & LINK_MARKER_TOP) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(134).data();
		}
		if (mark & LINK_MARKER_TOP_RIGHT) {
			_linkMark += ygo::gDataManager->GetAccessibilityString(135).data();
		}
		if(!_linkMark.empty())
			isLink = true;
		return _linkMark;
	}

	std::wstring GetOverlayedCards(ygo::ClientCard* selectedCard)
	{
		std::wstring _overlayedCards = std::wstring();
		if (!selectedCard->overlayed.empty()) {
			for (auto it = selectedCard->overlayed.begin(); it != selectedCard->overlayed.end(); ++it) {
				if (*it) {
					_overlayedCards += fmt::format(L"{}, ", ygo::gDataManager->GetName((*it)->code));
				}
			}
		}
		return _overlayedCards;
	}

	std::wstring GetCardLimit(const ygo::CardDataC* selectedCard)
	{
		std::wstring limited = std::wstring();
		// int limit = ygo::mainGame->deckBuilder.filterList->whitelist ? 0 : 3;
		// auto endit = ygo::mainGame->deckBuilder.filterList->content.end();
		// auto it = ygo::mainGame->deckBuilder.filterList->GetLimitationIterator(selectedCard);
		// if (it != endit)
		// 	limit = it->second;
		// if (limit == 0)
		// 	limited = ygo::gDataManager->GetAccessibilityString(167).data();
		// else if (limit != 0)
		// 	limited = fmt::format(ygo::gDataManager->GetAccessibilityString(168).data(), limit);
		return limited;
	}
};
