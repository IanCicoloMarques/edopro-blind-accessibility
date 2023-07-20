#include "DeckEditorMenu.h"

#include "AccessibilityMenu.h"

#include <Control/EventHandler.h>

#include "FieldFocus/AccessibilityDeckFocus.h"
#include "Models/Card.h"

namespace ygo {
	DeckEditorMenuHandler* DeckEditorMenuHandler::_menuHandler = nullptr;
	std::vector<int> DeckEditorMenuHandler::deckEditorMenu = {
		MenuType::DeckEditorMenu::DE_VIEW_CARDS,
		MenuType::DeckEditorMenu::DE_DECK_OPTIONS, MenuType::DeckEditorMenu::DE_SEARCH_OPTIONS
	};

	std::vector<int> DeckEditorMenuHandler::viewCardsMenu = {};

	std::vector<int> DeckEditorMenuHandler::deckOptionsMenu = {
		AccessibilityDeckFocus::DeckOptionsMenu::DEOP_NEW_DECK, AccessibilityDeckFocus::DeckOptionsMenu::DEOP_DECK_NAME,
		AccessibilityDeckFocus::DeckOptionsMenu::DEOP_DELETE_DECK, AccessibilityDeckFocus::DeckOptionsMenu::DEOP_RENAME_DECK,
		AccessibilityDeckFocus::DeckOptionsMenu::DEOP_SAVE_DECK
	};

	std::vector<int> DeckEditorMenuHandler::searchCardMenu = {
		AccessibilityDeckFocus::SearchCardMenu::SCARD_CATEGORY,
		AccessibilityDeckFocus::SearchCardMenu::SCARD_SUB_CATEGORY, AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTRIBUTE,
		AccessibilityDeckFocus::SearchCardMenu::SCARD_TYPE, AccessibilityDeckFocus::SearchCardMenu::SCARD_LEVEL,
		AccessibilityDeckFocus::SearchCardMenu::SCARD_SCALE, AccessibilityDeckFocus::SearchCardMenu::SCARD_LIMIT,
		AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTACK, AccessibilityDeckFocus::SearchCardMenu::SCARD_DEFENSE,
		AccessibilityDeckFocus::SearchCardMenu::SCARD_LINK_MARKER, AccessibilityDeckFocus::SearchCardMenu::SCARD_EFFECT, AccessibilityDeckFocus::SearchCardMenu::SCARD_CLEAR_SEARCH
	};

	DeckEditorMenuHandler::DeckEditorMenuHandler(const int activeMenu, const std::vector<int>& selectedMenu): BaseMenu{ activeMenu, selectedMenu }
	{}

	BaseMenu* DeckEditorMenuHandler::GetMenu()
	{
		if (_menuHandler == nullptr)
			_menuHandler = new DeckEditorMenuHandler();
		return _menuHandler;
	}

	/**
	 * \brief Read the current value of a combo box
	 * \param comboBox the combo box to be read
	 */
	static void ReadComboBox(const irr::gui::IGUIComboBox* comboBox) {
		if (comboBox->isTrulyVisible()) {
			const std::wstring nvdaString = fmt::format(L"{}", comboBox->getItem(comboBox->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString);
		}
	}

	void DeckEditorMenuHandler::ReadMenuAndValue()
	{
		std::wstring menuValue = std::wstring();
		if(_activeMenu == _selectedMenu)
		{
			if(_currentMenu == Accessibility::Dict::Menu::OK)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::OK).data();
			else if(_currentMenu == Accessibility::Dict::Menu::CANCEL)
				menuValue = gDataManager->GetAccessibilityString(Accessibility::Dict::Menu::CANCEL).data();
		}
		if(!menuValue.empty())
			ScreenReader::getReader()->readScreen(menuValue);
	}

	void DeckEditorMenuHandler::SetStack(AccessibilityDeckFocus::CardStack cardStack)
	{
		_selectedCardIndex = 0;
		_selectedCardStack = cardStack;
		const std::wstring cardStackName =fmt::format(gDataManager->GetAccessibilityString(cardStack).data(), mainGame->deckBuilder.GetCurrentDeck().side.size());
		ScreenReader::getReader()->readScreen(cardStackName);

	}

	void DeckEditorMenuHandler::KeyInputEvent(const irr::SEvent& event)
	{
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_D: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnDeleteDeck);
					ClickButton(mainGame->btnDeleteDeck);
				}
				break;
			}
			case irr::KEY_KEY_E: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					SetStack(AccessibilityDeckFocus::CardStack::SIDE_DECK);
				break;
			}
			case irr::KEY_KEY_F: {
				std::wstring message = std::wstring();
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					epro::wstringview dname(mainGame->ebDeckname->getText());
					if (dname.empty())
						message = gDataManager->GetAccessibilityString(AccessibilityDeckFocus::DeckEditorMessages::NO_DECK).data();
					else
						message = fmt::format(gDataManager->GetAccessibilityString(AccessibilityDeckFocus::DeckEditorMessages::DECK_NAME).data(), dname.data());
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (_selectedCardStack == AccessibilityDeckFocus::CardStack::MAIN_DECK) {
						_selectedCardStack = AccessibilityDeckFocus::CardStack::SIDE_DECK;
						message = gDataManager->GetAccessibilityString(AccessibilityDeckFocus::DeckEditorMessages::ADD_CARD_SIDE_DECK).data();
					}
					else{
						_selectedCardStack = AccessibilityDeckFocus::CardStack::MAIN_DECK;
						message = gDataManager->GetAccessibilityString(AccessibilityDeckFocus::DeckEditorMessages::ADD_CARD_MAIN_DECK).data();
					}
				}
				if(!message.empty())
					ScreenReader::getReader()->readScreen(message);
				break;
			}
			case irr::KEY_KEY_G: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnClearDeck);
					ClickButton(mainGame->btnClearDeck);
					_newDeck = true;
				}
				break;
			}
			case irr::KEY_KEY_I: {
				if (!mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					ReadCardInfo();
				break;
			}
			case irr::KEY_KEY_Q: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					SetStack(AccessibilityDeckFocus::CardStack::MAIN_DECK);
				break;
			}
			case irr::KEY_KEY_R: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->ebDeckname);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(157).data());
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					SetStack(AccessibilityDeckFocus::CardStack::SEARCH);
				break;
			}
			case irr::KEY_KEY_S: {
				if (event.KeyInput.Control) {
					epro::wstringview dname(mainGame->ebDeckname->getText());
					if (dname.empty()) {
						ClickButton(mainGame->btnSaveDeck);
						mainGame->env->setFocus(mainGame->btnSaveDeck);
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(159).data(), mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(160).data()));
					}
					else{
						ClickButton(mainGame->btnSaveDeckAs);
						mainGame->env->setFocus(mainGame->btnSaveDeckAs);
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(161).data(), dname));
					}
				}
				break;
			}
			case irr::KEY_KEY_W: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					SetStack(AccessibilityDeckFocus::CardStack::EXTRA_DECK);
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if(_currentMenu == MenuType::DeckEditorMenu::DE_VIEW_CARDS)
						AddOrRemoveCardsFromDeck();
					else if (_currentMenu == MenuType::DeckEditorMenu::DE_DECK_OPTIONS)
						DeckOptionsMenu();
					else if (_currentMenu == MenuType::DeckEditorMenu::DE_SEARCH_OPTIONS)
						SearchOptionsMenu();
					else
					{
						_currentMenu = MenuType::DeckEditorMenu::DE_MENU;
						_selectedMenu = deckEditorMenu;
					}
				}
				break;
			}
			case irr::KEY_SPACE: {
				if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					StringBuilder::cleanBuiltMessage();
					StringBuilder::AddLine(gDataManager->GetAccessibilityString(38).data());
					StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(9).data());
					ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->cbANNumber->isTrulyVisible()) {
						if (!mainGame->env->hasFocus(mainGame->cbANNumber))
							mainGame->env->setFocus(mainGame->cbANNumber);
						const std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString, false);
					}
				}
				break;
			}
			case irr::KEY_LEFT:
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if(_currentMenu == MenuType::DeckEditorMenu::DE_VIEW_CARDS){
						if (_selectedMenu != viewCardsMenu)
						{
							_selectedMenu = viewCardsMenu;
							SetMenu();
						}
						SelectCard(event.KeyInput.Key);
					}
					else if (_currentMenu == MenuType::DeckEditorMenu::DE_DECK_OPTIONS) {
						if (_selectedMenu != deckOptionsMenu)
							_selectedMenu = deckOptionsMenu;
						SetSelectedMenu(event.KeyInput.Key);
					}
					else if (_currentMenu == MenuType::DeckEditorMenu::DE_SEARCH_OPTIONS) {
						if (_selectedMenu != searchCardMenu)
							_selectedMenu = searchCardMenu;
						SetSelectedMenu(event.KeyInput.Key);
					}
					else if (_currentMenu == MenuType::DeckEditorMenu::DE_MENU) {
						if (_selectedMenu != deckEditorMenu)
							_selectedMenu = deckEditorMenu;
						SetSelectedMenu(event.KeyInput.Key);
					}
				}
				break;
			}
			case irr::KEY_DOWN:
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX) && _currentMenu == MenuType::DeckEditorMenu::DE_DECK_OPTIONS) {
					if (mainGame->cbDBDecks->isTrulyVisible() && _currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_SELECT_DECK) {
						ReadComboBox(mainGame->cbDBDecks);
						_newDeck = false;
					}
				}
				else if(!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX) && _currentMenu == MenuType::DeckEditorMenu::DE_SEARCH_OPTIONS)
				{
					if(mainGame->cbCardType->isTrulyVisible() && _currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_CATEGORY)
						ReadComboBox(mainGame->cbCardType);
					else if (mainGame->cbCardType2->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && _currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_SUB_CATEGORY)
						ReadComboBox(mainGame->cbCardType2);
					else if (mainGame->cbRace->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && _currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_TYPE)
						ReadComboBox(mainGame->cbRace);
					else if (mainGame->cbAttribute->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && _currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTRIBUTE)
						ReadComboBox(mainGame->cbAttribute);
					else if (mainGame->cbLimit->isTrulyVisible() && _currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_LIMIT)
						ReadComboBox(mainGame->cbLimit);
				}
				break;
			}
			case irr::KEY_NUMPAD0:
			case irr::KEY_KEY_0: {
				if(_currentMenu == MenuType::DeckEditorMenu::DE_VIEW_CARDS){
					if (_selectedMenu != deckEditorMenu)
						_selectedMenu = deckEditorMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				else if (_currentMenu == MenuType::DeckEditorMenu::DE_DECK_OPTIONS) {
					if (_selectedMenu != deckEditorMenu)
						_selectedMenu = deckEditorMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				else if (_currentMenu == MenuType::DeckEditorMenu::DE_SEARCH_OPTIONS) {
					if (_selectedMenu != deckEditorMenu)
						_selectedMenu = deckEditorMenu;
					SetSelectedMenu(event.KeyInput.Key);
				}
				else if (_currentMenu == MenuType::DeckEditorMenu::DE_MENU && mainGame->btnLeaveGame->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
						ClickButton(mainGame->btnLeaveGame);
				break;
			}
			case irr::KEY_COMMA: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnYes->isTrulyVisible()) {
						ClickButton(mainGame->btnYes);
						const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(102).data());
						ScreenReader::getReader()->readScreen(nvdaString, false);
					}
				}
				break;
			}
			case irr::KEY_PERIOD: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnNo->isTrulyVisible()) {
						ClickButton(mainGame->btnNo);
						const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(106).data());
						ScreenReader::getReader()->readScreen(nvdaString, false);
					}
				}
				break;
			}
		}
	}

	void DeckEditorMenuHandler::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	void DeckEditorMenuHandler::ReadCardInfo()
	{
		if (_selectedCardStack == AccessibilityDeckFocus::CardStack::MAIN_DECK) {
			const auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[_selectedCardIndex]->code);
			if (pointer) {
				const auto selectedCard = mainGame->deckBuilder.GetCurrentDeck().main[_selectedCardIndex];
				Card* card = new Card(selectedCard);
				card->ReadCardInfo();
			}
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::EXTRA_DECK) {
			const auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[_selectedCardIndex]->code);
			if (pointer) {
				const auto selectedCard = mainGame->deckBuilder.GetCurrentDeck().extra[_selectedCardIndex];
				Card* card = new Card(selectedCard);
				card->ReadCardInfo();
			}
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SIDE_DECK) {
			const auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().side[_selectedCardIndex]->code);
			if (pointer) {
				const auto selectedCard = mainGame->deckBuilder.GetCurrentDeck().side[_selectedCardIndex];
				Card* card = new Card(selectedCard);
				card->ReadCardInfo();
			}
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SEARCH) {
			const auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[_selectedCardIndex]->code);
			if (pointer) {
				const auto selectedCard = mainGame->deckBuilder.GetCurrentDeck().side[_selectedCardIndex];
				Card* card = new Card(selectedCard);
				card->ReadCardInfo();
			}
		}
	}

	void DeckEditorMenuHandler::AddOrRemoveCardsFromDeck()
	{
		if (_selectedCardStack == AccessibilityDeckFocus::CardStack::MAIN_DECK) {
			if(mainGame->deckBuilder.GetCurrentDeck().main.size() > _selectedCardIndex)
				mainGame->deckBuilder.pop_main(_selectedCardIndex);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::EXTRA_DECK) {
			if (mainGame->deckBuilder.GetCurrentDeck().extra.size() > _selectedCardIndex)
				mainGame->deckBuilder.pop_extra(_selectedCardIndex);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SIDE_DECK) {
			if (mainGame->deckBuilder.GetCurrentDeck().side.size() > _selectedCardIndex)
				mainGame->deckBuilder.pop_side(_selectedCardIndex);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SEARCH) {
			if (mainGame->deckBuilder.results.size() < _selectedCardIndex)
				return;
			const auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[_selectedCardIndex]->code);
			if (!pointer || !mainGame->deckBuilder.check_limit(pointer)) {
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(163).data());
			}
			else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SIDE_DECK) {
				mainGame->deckBuilder.push_side(pointer);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(164).data());
			}
			else {
				if (mainGame->deckBuilder.push_extra(pointer))
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(165).data());
				else if (mainGame->deckBuilder.push_main(pointer))
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(166).data());
			}
		}
	}

	void DeckEditorMenuHandler::SelectCard(irr::EKEY_CODE key)
	{
		if (_selectedCardStack == AccessibilityDeckFocus::CardStack::MAIN_DECK) {
			SelectCard(key, mainGame->deckBuilder.GetCurrentDeck().main);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::EXTRA_DECK) {
			SelectCard(key, mainGame->deckBuilder.GetCurrentDeck().extra);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SIDE_DECK) {
			SelectCard(key, mainGame->deckBuilder.GetCurrentDeck().side);
		}
		else if (_selectedCardStack == AccessibilityDeckFocus::CardStack::SEARCH) {
			SelectCard(key, mainGame->deckBuilder.results);
		}
	}

	void DeckEditorMenuHandler::SelectCard(irr::EKEY_CODE key, const Deck::Vector& deck)
	{
		if(key == irr::KEY_RIGHT)
		{
			if (!deck.empty() && deck.size() == 1)
				_selectedCardIndex = 0;
			else if (!deck.empty() && _selectedCardIndex < deck.size() - 1)
				_selectedCardIndex++;
		}
		else if(key == irr::KEY_LEFT)
		{
			if (!deck.empty() && deck.size() == 1)
				_selectedCardIndex = 0;
			else if (!deck.empty() && _selectedCardIndex <= deck.size() && _selectedCardIndex > 0)
				_selectedCardIndex--;
		}
		if (!deck.empty() && _selectedCardIndex <= deck.size())
		{
			mainGame->ShowCardInfo(deck[_selectedCardIndex]->code);
			const auto selectedCard = mainGame->deckBuilder.GetCurrentDeck().main[_selectedCardIndex];
			Card* card = new Card(selectedCard);
			card->ReadCardResumedInfo();
		}
	}

	void DeckEditorMenuHandler::DeckOptionsMenu()
	{
		if (_selectedMenu != deckOptionsMenu)
		{
			_selectedMenu = deckOptionsMenu;
			SetMenu();
		}
		else
		{
			if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_SELECT_DECK && mainGame->cbDBDecks->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbDBDecks);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(170).data(), mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_scrolling = false;
					_newDeck = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_NEW_DECK && mainGame->btnClearDeck->isTrulyVisible()) {
				mainGame->ebDeckname->setText(L"");
				ClickButton(mainGame->btnClearDeck);
			}
			else if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_DELETE_DECK && mainGame->btnDeleteDeck->isTrulyVisible())
				ClickButton(mainGame->btnDeleteDeck);
			else if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_RENAME_DECK) {
				mainGame->env->setFocus(mainGame->ebDeckname);
				ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(157).data());
			}
			else if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_SAVE_DECK) {
				epro::wstringview dname(mainGame->ebDeckname->getText());
				if (dname.empty()) {
					ClickButton(mainGame->btnSaveDeck);
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(159).data(), mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(160).data()));
				}
				else{
					ClickButton(mainGame->btnSaveDeckAs);
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(161).data(), dname));
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::DeckOptionsMenu::DEOP_DECK_NAME) {
				const epro::wstringview dname(mainGame->ebDeckname->getText());
				if (dname.empty())
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(152).data());
				else
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(153).data(), dname.data()));
			}
		}
	}

	void DeckEditorMenuHandler::SearchOptionsMenu()
	{
		if (_selectedMenu != searchCardMenu)
		{
			_selectedMenu = searchCardMenu;
			SetMenu();
		}
		else
		{
			if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_SEARCH && mainGame->ebCardName->isTrulyVisible()) {
				if (!_typing) {
					mainGame->env->setFocus(mainGame->ebCardName);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(171).data());
					_typing = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(172).data(), mainGame->ebCardName->getText()));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_typing = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_CATEGORY && mainGame->cbCardType->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbCardType);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(173).data(), mainGame->cbCardType->getItem(mainGame->cbCardType->getSelected())));
					_scrolling = false;
					mainGame->env->removeFocus(mainGame->env->getFocus());
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_SUB_CATEGORY && mainGame->cbCardType2->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbCardType2);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(174).data(), mainGame->cbCardType2->getItem(mainGame->cbCardType2->getSelected())));
					_scrolling = false;
					mainGame->env->removeFocus(mainGame->env->getFocus());
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTRIBUTE && mainGame->cbAttribute->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbAttribute);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(175).data(), mainGame->cbAttribute->getItem(mainGame->cbAttribute->getSelected())));
					_scrolling = false;
					mainGame->env->removeFocus(mainGame->env->getFocus());
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_TYPE && mainGame->cbRace->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbRace);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(176).data(), mainGame->cbRace->getItem(mainGame->cbRace->getSelected())));
					_scrolling = false;
					mainGame->env->removeFocus(mainGame->env->getFocus());
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_LEVEL && mainGame->ebStar->isTrulyVisible()) {
				if (!_typing) {
					mainGame->env->setFocus(mainGame->ebStar);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(177).data());
					_typing = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(178).data(), mainGame->ebStar->getText()));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_typing = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_SCALE && mainGame->ebScale->isTrulyVisible()) {
				if (!_typing) {
					mainGame->env->setFocus(mainGame->ebScale);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(179).data());
					_typing = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(180).data(), mainGame->ebScale->getText()));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_typing = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_LIMIT && mainGame->cbLimit->isTrulyVisible()) {
				if (!_scrolling) {
					mainGame->env->setFocus(mainGame->cbLimit);
					_scrolling = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(181).data(), mainGame->cbLimit->getItem(mainGame->cbLimit->getSelected())));
					_scrolling = false;
					mainGame->env->removeFocus(mainGame->env->getFocus());
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_ATTACK && mainGame->ebAttack->isTrulyVisible()) {
				if (!_typing) {
					mainGame->env->setFocus(mainGame->ebAttack);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(182).data());
					_typing = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(183).data(), mainGame->ebAttack->getText()));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_typing = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_DEFENSE && mainGame->ebDefense->isTrulyVisible()) {
				if (!_typing) {
					mainGame->env->setFocus(mainGame->ebDefense);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(184).data());
					_typing = true;
				}
				else {
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(185).data(), mainGame->ebDefense->getText()));
					mainGame->env->removeFocus(mainGame->env->getFocus());
					_typing = false;
				}
			}
			else if (_currentMenu == AccessibilityDeckFocus::SearchCardMenu::SCARD_CLEAR_SEARCH && mainGame->btnClearFilter->isEnabled()) {
				ClickButton(mainGame->btnClearFilter);
			}
		}

	}
}
