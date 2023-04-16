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
		switch (event.KeyInput.Key) {
			case irr::KEY_KEY_A: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::MENU;
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(150).data());
				}
				break;
			}
			case irr::KEY_KEY_D: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnDeleteDeck);
					TriggerEvent(mainGame->btnDeleteDeck, irr::gui::EGET_BUTTON_CLICKED);
				}
				break;
			}
			case irr::KEY_KEY_E: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(151).data(), mainGame->deckBuilder.GetCurrentDeck().side.size()));
				}
				break;
			}
			case irr::KEY_KEY_F: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					epro::wstringview dname(mainGame->ebDeckname->getText());
					if (dname.empty()) {
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(152).data());
						break;
					}
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(153).data(), dname.data()));
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (deckEditor == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						deckEditor = AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK;
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(154).data());
					}
					else{
						deckEditor = AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK;
						ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(155).data());
					}
				}
				break;
			}
			case irr::KEY_KEY_G: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->btnClearDeck);
					TriggerEvent(mainGame->btnClearDeck, irr::gui::EGET_BUTTON_CLICKED);
					newDeck = true;
				}
				break;
			}
			case irr::KEY_KEY_I: {
				if (!mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					std::wstring cardName;
					std::wstring limit;
					std::wstring cardType;
					std::wstring cardAttribute;
					std::wstring cardLevel;
					std::wstring cardRace;
					std::wstring cardAttack;
					std::wstring cardDefense;
					std::wstring cardEffect;
					std::wstring leftScale;
					std::wstring rightScale;
					//TODO - Transformar isso em função
					if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code);
						bool limited = mainGame->deckBuilder.check_limit(pointer);
						limit = GetCardLimit(pointer);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(gDataManager->GetAccessibilityString(67).data(), gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code)->level) :
								fmt::format(gDataManager->GetAccessibilityString(68).data(), gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->race));
							cardAttack = fmt::format(gDataManager->GetAccessibilityString(69).data(), mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->attack);
							cardDefense = fmt::format(gDataManager->GetAccessibilityString(70).data(), mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->code));
							leftScale = fmt::format(gDataManager->GetAccessibilityString(73).data(), mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->lscale);
							rightScale = fmt::format(gDataManager->GetAccessibilityString(74).data(), mainGame->deckBuilder.GetCurrentDeck().main[indexLookedUpCard]->rscale);
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(gDataManager->GetAccessibilityString(67).data(), gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code)->level) :
								fmt::format(gDataManager->GetAccessibilityString(68).data(), gDataManager->GetCardData(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->race));
							cardAttack = fmt::format(gDataManager->GetAccessibilityString(69).data(), mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->attack);
							cardDefense = fmt::format(gDataManager->GetAccessibilityString(70).data(), mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->code));
							leftScale = fmt::format(gDataManager->GetAccessibilityString(73).data(), mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->lscale);
							rightScale = fmt::format(gDataManager->GetAccessibilityString(74).data(), mainGame->deckBuilder.GetCurrentDeck().extra[indexLookedUpCard]->rscale);
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
							cardAttack = fmt::format(gDataManager->GetAccessibilityString(69).data(), mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->attack);
							cardDefense = fmt::format(gDataManager->GetAccessibilityString(70).data(), mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->code));
							leftScale = fmt::format(gDataManager->GetAccessibilityString(73).data(), mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->lscale);
							rightScale = fmt::format(gDataManager->GetAccessibilityString(74).data(), mainGame->deckBuilder.GetCurrentDeck().side[indexLookedUpCard]->rscale);
						}
					}
					else if (deckLooker == AccessibilityDeckFocus::DeckLookerLocId::SEARCH) {
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code);
						if (pointer) {
							cardName = fmt::format(L"{}", gDataManager->GetName(mainGame->deckBuilder.results[indexLookedUpCard]->code));
							cardType = fmt::format(L"{}", gDataManager->FormatType(mainGame->deckBuilder.results[indexLookedUpCard]->type));
							cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(mainGame->deckBuilder.results[indexLookedUpCard]->attribute));
							cardLevel = mainGame->deckBuilder.results[indexLookedUpCard]->link_marker != 0 ?
								fmt::format(gDataManager->GetAccessibilityString(67).data(), gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code)->level) :
								fmt::format(gDataManager->GetAccessibilityString(68).data(), gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code)->level);
							cardRace = fmt::format(L"{}", gDataManager->FormatRace(mainGame->deckBuilder.results[indexLookedUpCard]->race));
							cardAttack = fmt::format(gDataManager->GetAccessibilityString(69).data(), mainGame->deckBuilder.results[indexLookedUpCard]->attack);
							cardDefense = fmt::format(gDataManager->GetAccessibilityString(70).data(), mainGame->deckBuilder.results[indexLookedUpCard]->defense);
							cardEffect = fmt::format(L"{}", gDataManager->GetText(mainGame->deckBuilder.results[indexLookedUpCard]->code));
							leftScale = fmt::format(gDataManager->GetAccessibilityString(73).data(), mainGame->deckBuilder.results[indexLookedUpCard]->lscale);
							rightScale = fmt::format(gDataManager->GetAccessibilityString(74).data(), mainGame->deckBuilder.results[indexLookedUpCard]->rscale);
						}
					}

					ScreenReader::getReader()->readScreen(cardName.c_str(), false);
					if(!limit.empty())
						ScreenReader::getReader()->readScreen(limit.c_str(), false);
					ScreenReader::getReader()->readScreen(cardType.c_str(), false);
					ScreenReader::getReader()->readScreen(cardAttribute.c_str(), false);
					if (cardType.find(gDataManager->GetAccessibilityString(76).data()) == std::string::npos && cardType.find(gDataManager->GetAccessibilityString(77).data()) == std::string::npos) {
						ScreenReader::getReader()->readScreen(cardLevel.c_str(), false);
						ScreenReader::getReader()->readScreen(cardRace.c_str(), false);
						ScreenReader::getReader()->readScreen(cardAttack.c_str(), false);
						ScreenReader::getReader()->readScreen(cardDefense.c_str(), false);
					}
					if (leftScale.compare(gDataManager->GetAccessibilityString(80).data()) != 0)
						ScreenReader::getReader()->readScreen(leftScale.c_str(), false);
					if (rightScale.compare(gDataManager->GetAccessibilityString(81).data()) != 0)
						ScreenReader::getReader()->readScreen(rightScale.c_str(), false);
					ScreenReader::getReader()->readScreen(cardEffect.c_str(), false);
				}
				break;
			}
			case irr::KEY_KEY_Q: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(156).data(), mainGame->deckBuilder.GetCurrentDeck().main.size()));
				}
				break;
			}
			case irr::KEY_KEY_R: {
				if (event.KeyInput.Control && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					mainGame->env->setFocus(mainGame->ebDeckname);
					ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(157).data());
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::SEARCH;
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(158).data(), mainGame->deckBuilder.results.size()));
				}
				break;
			}
			case irr::KEY_KEY_S: {
				if (event.KeyInput.Control) {
					epro::wstringview dname(mainGame->ebDeckname->getText());
					if (dname.empty()) {
						TriggerEvent(mainGame->btnSaveDeck, irr::gui::EGET_BUTTON_CLICKED);
						mainGame->env->setFocus(mainGame->btnSaveDeck);
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(159).data(), mainGame->cbDBDecks->getItem(mainGame->cbDBDecks->getSelected())));
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(160).data()));
					}
					else{
						TriggerEvent(mainGame->btnSaveDeckAs, irr::gui::EGET_BUTTON_CLICKED);
						mainGame->env->setFocus(mainGame->btnSaveDeckAs);
						ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(161).data(), dname));
					}
				}
				break;
			}
			case irr::KEY_KEY_W: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					indexLookedUpCard = 0;
					deckLooker = AccessibilityDeckFocus::DeckLookerLocId::EXTRA_DECK;
					ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(162).data(), mainGame->deckBuilder.GetCurrentDeck().extra.size()));
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
						if (mainGame->deckBuilder.results.size() < indexLookedUpCard)
							break;
						auto pointer = gDataManager->GetCardData(mainGame->deckBuilder.results[indexLookedUpCard]->code);
						if (!pointer || !mainGame->deckBuilder.check_limit(pointer)) {
							ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(163).data());
							break;
						}
						if (deckEditor == AccessibilityDeckFocus::DeckLookerLocId::SIDE_DECK) {
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
					if (mainGame->cbDBDecks->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SELECT_DECK) {
						ReadComboBox(mainGame->cbDBDecks);
						newDeck = false;
					}
					else if(mainGame->cbCardType->isTrulyVisible() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CATEGORY)
						ReadComboBox(mainGame->cbCardType);
					else if (mainGame->cbCardType2->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SUB_CATEGORY)
						ReadComboBox(mainGame->cbCardType2);
					else if (mainGame->cbRace->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_TYPE)
						ReadComboBox(mainGame->cbRace);
					else if (mainGame->cbAttribute->isTrulyVisible() && mainGame->cbCardType2->isEnabled() && menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTRIBUTE)
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
			case irr::KEY_COMMA: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnYes->isTrulyVisible()) {
						TriggerEvent(mainGame->btnYes, irr::gui::EGET_BUTTON_CLICKED);
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(102).data());
						ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
					}
				}
				break;
			}
			case irr::KEY_PERIOD: {
				if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					if (mainGame->btnNo->isTrulyVisible()) {
						TriggerEvent(mainGame->btnNo, irr::gui::EGET_BUTTON_CLICKED);
						std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(106).data());
						ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
					}
				}
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
		if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SELECT_DECK && mainGame->cbDBDecks->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SEARCH && mainGame->ebCardName->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CATEGORY && mainGame->cbCardType->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SUB_CATEGORY && mainGame->cbCardType2->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTRIBUTE && mainGame->cbAttribute->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_TYPE && mainGame->cbRace->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_LEVEL && mainGame->ebStar->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_SCALE && mainGame->ebScale->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_LIMIT && mainGame->cbLimit->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_ATTACK && mainGame->ebAttack->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_DEFENSE && mainGame->ebDefense->isTrulyVisible()) {
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
		else if (menuSelectCounter == MenuType::DeckOptionsMenu::DECKOP_CLEAR_SEARCH && mainGame->btnClearFilter->isEnabled()) {
			ClickButton(mainGame->btnClearFilter);
		}
	}
}
