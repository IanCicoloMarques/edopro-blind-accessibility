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
		IScreenReader* screenReader = ScreenReader::getReader();
		if (deckHandler == nullptr)
			deckHandler = new DeckHandler();
		return deckHandler;
	}

	void DeckHandler::KeyInputEvent(const irr::SEvent& event)
	{
		IScreenReader* screenReader = ScreenReader::getReader();
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_A: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::MENU;
					ScreenReader::getReader()->readScreen(L"Main Menu");
				}
				break;
			}
			case irr::KEY_KEY_E: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(L"Side Deck - {} cards", mainGame->deckBuilder.GetCurrentDeck().side.size()));
				}
				break;
			}
			case irr::KEY_KEY_F: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					epro::wstringview dname(mainGame->ebDeckname->getText());
					if (dname.empty()) {
						ScreenReader::getReader()->readScreen(L"No name");
						break;
					}
					ScreenReader::getReader()->readScreen(fmt::format(L"Deck {}", dname.data()));
				}
				break;
			}
			case irr::KEY_KEY_G: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnClearDeck);
					TriggerEvent(mainGame->btnClearDeck, irr::gui::EGET_BUTTON_CLICKED);
				}
				break;
			}
			case irr::KEY_KEY_I: {
				if (!mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					std::wstring cardName;
					std::wstring cardType;
					std::wstring cardAttribute;
					std::wstring cardLevel;
					std::wstring cardRace;
					std::wstring cardAttack;
					std::wstring cardDefense;
					std::wstring cardEffect;
					std::wstring leftScale;
					std::wstring rightScale;
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(L"Link {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code)->level) :
								fmt::format(L"Level {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->race));
							cardAttack = fmt::format(L"Attack {}", mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->attack);
							cardDefense = fmt::format(L"Defense: {}", mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code));
							leftScale = fmt::format(L"Left Scale {}", mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->lscale);
							rightScale = fmt::format(L"Right Scale {}", mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->rscale);
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(L"Link {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code)->level) :
								fmt::format(L"Level {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->race));
							cardAttack = fmt::format(L"Attack {}", mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->attack);
							cardDefense = fmt::format(L"Defense: {}", mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code));
							leftScale = fmt::format(L"Left Scale {}", mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->lscale);
							rightScale = fmt::format(L"Right Scale {}", mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->rscale);
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(L"Link {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code)->level) :
								fmt::format(L"Level {}", gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->race));
							cardAttack = fmt::format(L"Attack {}", mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->attack);
							cardDefense = fmt::format(L"Defense: {}", mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code));
							leftScale = fmt::format(L"Left Scale {}", mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->lscale);
							rightScale = fmt::format(L"Right Scale {}", mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->rscale);
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SEARCH) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.results[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.results[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.results[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.results[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(L"Link {}", gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code)->level) :
								fmt::format(L"Level {}", gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.results[indexLookedUpCard]->race));
							cardAttack = fmt::format(L"Attack {}", mainGame->deckBuilder.results[indexLookedUpCard]->attack);
							cardDefense = fmt::format(L"Defense: {}", mainGame->deckBuilder.results[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.results[indexLookedUpCard]->code));
							leftScale = fmt::format(L"Left Scale {}", mainGame->deckBuilder.results[indexLookedUpCard]->lscale);
							rightScale = fmt::format(L"Right Scale {}", mainGame->deckBuilder.results[indexLookedUpCard]->rscale);
						}

					}
					
					ScreenReader::getReader()->readScreen(cardName.c_str(), false);
					ScreenReader::getReader()->readScreen(cardType.c_str(), false);
					ScreenReader::getReader()->readScreen(cardAttribute.c_str(), false);
					if (cardType.find(L"Spell") == std::string::npos && cardType.find(L"Trap") == std::string::npos) {
						ScreenReader::getReader()->readScreen(cardLevel.c_str(), false);
						ScreenReader::getReader()->readScreen(cardRace.c_str(), false);
						ScreenReader::getReader()->readScreen(cardAttack.c_str(), false);
						ScreenReader::getReader()->readScreen(cardDefense.c_str(), false);
					}
					if (leftScale.compare(L"Left Scale ") != 0)
						ScreenReader::getReader()->readScreen(leftScale.c_str(), false);
					if (rightScale.compare(L"Right Scale ") != 0)
						ScreenReader::getReader()->readScreen(rightScale.c_str(), false);
					ScreenReader::getReader()->readScreen(cardEffect.c_str(), false);
				}
				break;
			}
			case irr::KEY_KEY_Q: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(L"Main Deck - {} cards", mainGame->deckBuilder.GetCurrentDeck().main.size()));
				}
				break;
			}
			case irr::KEY_KEY_R: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->ebDeckname);
					ScreenReader::getReader()->readScreen(L"Set deck's name");
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::SEARCH;
					ScreenReader::getReader()->readScreen(fmt::format(L"Search - {} cards", mainGame->deckBuilder.results.size()));
				}
				break;
			}
			case irr::KEY_KEY_S: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnSaveDeckAs);
					TriggerEvent(mainGame->btnSaveDeckAs, irr::gui::EGET_BUTTON_CLICKED);
				}
				break;
			}
			case irr::KEY_KEY_W: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(L"Extra Deck - {} cards", mainGame->deckBuilder.GetCurrentDeck().extra.size()));
				}
				break;
			}
			case irr::KEY_RETURN: {
				if (!event.KeyInput.PressedDown) {
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						if(mainGame->deckBuilder.GetCurrentDeck().main.size() > indexLookedUpCard)
							mainGame->deckBuilder.pop_main(indexLookedUpCard);
					}
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK) {
						if (mainGame->deckBuilder.GetCurrentDeck().extra.size() > indexLookedUpCard)
							mainGame->deckBuilder.pop_extra(indexLookedUpCard);
					}
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK) {
						if (mainGame->deckBuilder.GetCurrentDeck().side.size() > indexLookedUpCard)
							mainGame->deckBuilder.pop_side(indexLookedUpCard);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SEARCH) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code);
						if (!pointer || !mainGame->deckBuilder.check_limit(pointer)) {
							ScreenReader::getReader()->readScreen(L"Already has the limit of this card on the deck");
							break;
						}
						if (event.KeyInput.Shift) {
							mainGame->deckBuilder.push_side(pointer);
							ScreenReader::getReader()->readScreen(L"Added to the side deck");
						}
						else {
							if (mainGame->deckBuilder.push_extra(pointer))
								ScreenReader::getReader()->readScreen(L"Added to the extra deck");
							else if (mainGame->deckBuilder.push_main(pointer))
								ScreenReader::getReader()->readScreen(L"Added to the main deck");
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MENU) {
						DeckOptionsMenu();
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
						std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
						ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
					}
				}
				break;
			}
			case irr::KEY_RIGHT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						RightKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().main);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK) {
						RightKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().extra);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK) {
						RightKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().side);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SEARCH) {
						RightKeyLookCard(mainGame->deckBuilder.results);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MENU) {
						if (!scrollSelected) {
							typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							menuSelectCounter++;
							if (menuSelectCounter >= menu.size())
								menuSelectCounter = 0;
							ScreenReader::getReader()->readScreen(menu.at(menuSelectCounter).c_str());
						}
					}
				}
				break;
			}
			case irr::KEY_LEFT: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						LeftKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().main);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK) {
						LeftKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().extra);

					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK) {
						LeftKeyLookCard(mainGame->deckBuilder.GetCurrentDeck().side);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SEARCH) {
						LeftKeyLookCard(mainGame->deckBuilder.results);
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MENU) {
						if (!scrollSelected) {
							typing = false;
							mainGame->env->removeFocus(mainGame->env->getFocus());
							menuSelectCounter--;
							if (menuSelectCounter < 0)
								menuSelectCounter = menu.size() - 1;
							ScreenReader::getReader()->readScreen(menu.at(menuSelectCounter).c_str());
						}
					}
				}
				break;
			}
			case irr::KEY_DOWN:
			case irr::KEY_UP: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX) && deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MENU) {
					if (mainGame->cbDBDecks->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SELECT_DECK)
						ReadComboBox(mainGame->cbDBDecks);
					else if(mainGame->cbCardType->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CATEGORY)
						ReadComboBox(mainGame->cbCardType);
					else if (mainGame->cbCardType2->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SUB_CATEGORY)
						ReadComboBox(mainGame->cbCardType2);
					else if (mainGame->cbRace->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_TYPE)
						ReadComboBox(mainGame->cbRace);
					else if (mainGame->cbAttribute->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTRIBUTE)
						ReadComboBox(mainGame->cbAttribute);
					else if (mainGame->cbLimit->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_LIMIT)
						ReadComboBox(mainGame->cbLimit);
				}
				break;
			}
			case irr::KEY_NUMPAD0:
			case irr::KEY_KEY_0: {
				if (mainGame->btnLeaveGame->isTrulyVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
					TriggerEvent(mainGame->btnLeaveGame, irr::gui::EGET_BUTTON_CLICKED);
				break;
			}
		}
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

	void DeckHandler::ReadCardName(const std::vector<const CardDataC*> &deck) {
		std::wstring nvdaString;
		if (deck.size() > indexLookedUpCard && deck[indexLookedUpCard]->code != 0)
			nvdaString = fmt::format(L"{} {} attack {} defense", gDataManager->GetName(deck[indexLookedUpCard]->code), deck[indexLookedUpCard]->attack, deck[indexLookedUpCard]->defense);
		ScreenReader::getReader()->readScreen(nvdaString.c_str());
	}

	void DeckHandler::DeckOptionsMenu() {
		if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SELECT_DECK && mainGame->cbDBDecks->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbDBDecks);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Deck set to {}", mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				scrollSelected = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SEARCH && mainGame->ebCardName->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebCardName);
				ScreenReader::getReader()->readScreen(L"Type what to search");
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Searching for {}", mainGame->ebCardName->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CATEGORY && mainGame->cbCardType->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbCardType);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Category set to {}", mainGame->cbCardType->getItem(mainGame->cbCardType->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SUB_CATEGORY && mainGame->cbCardType2->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbCardType2);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Sub-Category set to {}", mainGame->cbCardType2->getItem(mainGame->cbCardType2->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTRIBUTE && mainGame->cbAttribute->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbAttribute);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Attribute set to {}", mainGame->cbAttribute->getItem(mainGame->cbAttribute->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_TYPE && mainGame->cbRace->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbRace);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Type set to {}", mainGame->cbRace->getItem(mainGame->cbRace->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_LEVEL && mainGame->ebStar->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebStar);
				ScreenReader::getReader()->readScreen(L"Type the card level");
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Card level set to {}", mainGame->ebStar->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SCALE && mainGame->ebScale->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebScale);
				ScreenReader::getReader()->readScreen(L"Type the card scale");
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Card scale set to {}", mainGame->ebScale->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_LIMIT && mainGame->cbLimit->isTrulyVisible()) {
			if (!scrollSelected) {
				mainGame->env->setFocus(mainGame->cbLimit);
				scrollSelected = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Limit set to {}", mainGame->cbLimit->getItem(mainGame->cbLimit->getSelected())));
				scrollSelected = false;
				mainGame->env->removeFocus(mainGame->env->getFocus());
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTACK && mainGame->ebAttack->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebAttack);
				ScreenReader::getReader()->readScreen(L"Type the card attack");
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Card attack set to {}", mainGame->ebAttack->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_DEFENSE && mainGame->ebDefense->isTrulyVisible()) {
			if (!typing) {
				mainGame->env->setFocus(mainGame->ebDefense);
				ScreenReader::getReader()->readScreen(L"Type the card defense");
				typing = true;
			}
			else {
				ScreenReader::getReader()->readScreen(fmt::format(L"Card defense set to {}", mainGame->ebDefense->getText()));
				mainGame->env->removeFocus(mainGame->env->getFocus());
				typing = false;
			}
		}
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CLEAR_SEARCH && mainGame->btnClearFilter->isEnabled()) {
			ClickButton(mainGame->btnClearFilter);
		}
	}
}
