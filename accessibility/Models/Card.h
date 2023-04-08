#pragma once
#include <string>

class Card
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
	uint8_t selectedPosition;
	bool isLink = false;

	Card(ygo::ClientCard* selectedCard)
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

	void ReadCardInfo()
	{
		ScreenReader::getReader()->readScreen(cardName, false);
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
	}

private:
	void SetLevel(ygo::ClientCard* selectedCard)
	{
		cardLevel = selectedCard->link_marker != 0 ?
			fmt::format(ygo::gDataManager->GetAccessibilityString(67).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level) :
			fmt::format(ygo::gDataManager->GetAccessibilityString(68).data(), ygo::gDataManager->GetCardData(selectedCard->code)->level);
	}

	void SetPosition(ygo::ClientCard* selectedCard)
	{
		selectedPosition = selectedCard->position;
		position = selectedCard->position == 1 ? fmt::format(ygo::gDataManager->GetAccessibilityString(71).data()) : fmt::format(ygo::gDataManager->GetAccessibilityString(72).data());
	}

	std::wstring GetLinkMarks(ygo::ClientCard* selectedCard)
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
};
