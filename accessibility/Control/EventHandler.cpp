#include "EventHandler.h"
#include <fmt/format.h>
#include <fmt/printf.h>
#include "../gframe/data_manager.h"
#include "../ScreenReader/StringBuilder.cpp"
#include "../ScreenReader/ScreenReader.cpp"
//#include "../gframe/materials.h"
//#include "../gframe/utils.h"
//#include "../gframe/game_config.h"
#include "../gframe/client_field.h"
//#include "../gframe/client_card.h"
//#include "../gframe/network.h"
#include "../gframe/game.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/custom_skin_enum.h"
#include <IGUIWindow.h>
#include <IrrlichtDevice.h>
#include <IGUIStaticText.h>
#include <IGUIScrollBar.h>
//#include "../gframe/duelclient.h"
//#include "../gframe/data_manager.h"
//#include "../gframe/image_manager.h"
//#include "../gframe/replay_mode.h"
//#include "../gframe/single_mode.h"
//#include "../gframe/materials.h"
//#include "../gframe/progressivebuffer.h"
//#include "../gframe/utils_gui.h"
//#include "../gframe/sound_manager.h"

namespace ygo {
	static AccessibilityFieldFocus::FieldLookerLocId lookupFieldLocId;
	//irr::core::vector3df MouseToPlane(const irr::core::vector2d<irr::s32>& mouse, const irr::core::plane3d<irr::f32>& plane) {
	//	const auto collmanager = ygo::mainGame->smgr->getSceneCollisionManager();
	//	irr::core::line3df line = collmanager->getRayFromScreenCoordinates(mouse);
	//	irr::core::vector3d<irr::f32> startintersection;
	//	plane.getIntersectionWithLimitedLine(line.start, line.end, startintersection);
	//	return startintersection;
	//}

	static inline void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
		irr::SEvent event;
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		ygo::mainGame->device->postEventFromUser(event);
	}

	void EventHandler::PushKey(const irr::SEvent& event)
	{
		IScreenReader* screenReader = ScreenReader::getReader();
		switch (event.KeyInput.Key) {
		case irr::KEY_KEY_Q: {
				if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					StringBuilder::cleanBuiltMessage();
					StringBuilder::AddLine(gDataManager->GetAccessibilityString(13).data());
					ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
				}
				else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
					bool canViewCards = CheckIfCanViewCards(event);
					if (canViewCards) {
						lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_HAND;
						cardType = AccessibilityFieldFocus::CardType::MONSTER;
						DisplayCards(CardsDTO::_hand[displayedField], fmt::format(L"Hand"));
					}
					else
						CloseDialog();
				}
				break;
		}	
		}
		//switch (event.KeyInput.Key) {
		//case irr::KEY_KEY_Q: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(13).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	/*else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_HAND;
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			DisplayCards(CardsDTO::_hand[displayedField], fmt::format(L"Hand"));
		//		}
		//		else
		//			CloseDialog();
		//	}*/
		//	break;
		//}
		//case irr::KEY_KEY_W: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(14).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	/*else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS;
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			DisplayCards(CardsDTO::_mzone[displayedField], fmt::format(L"Monster Zone"));
		//		}
		//		else
		//			CloseDialog();
		//	}*/
		//	break;
		//}
		//case irr::KEY_KEY_E: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(15).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS;
		//			cardType = AccessibilityFieldFocus::CardType::SPELL;
		//			DisplayCards(szone[displayedField], fmt::format(L"Spells"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_R: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(16).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_EXTRA_DECK;
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			DisplayCards(extra[displayedField], fmt::format(L"Extra Deck"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_T: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(17).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_GRAVEYARD;
		//			cardType = AccessibilityFieldFocus::CardType::GRAVEYARD;
		//			DisplayCards(grave[displayedField], fmt::format(L"Graveyard"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_Y: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(18).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_BANNED_CARDS;
		//			DisplayCards(remove[displayedField], fmt::format(L"Removed Cards"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_U: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(19).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_DECK;
		//			DisplayCards(deck[displayedField], fmt::format(L"Deck"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_A: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(20).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(43).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(0).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(4).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (battlePhase == AccessibilityFieldFocus::BattleStep::BP)
		//			UseCard(AccessibilityFieldFocus::UseType::MONSTER_ATTACK, event);
		//		else
		//			UseCard(AccessibilityFieldFocus::UseType::NORMAL_SUMMON, event);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_S: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(21).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(3).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ChangeFieldByCard();
		//		UseCard(AccessibilityFieldFocus::UseType::SET_CARD, event);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_D: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(22).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(2).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
		//		cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//		UseCard(AccessibilityFieldFocus::UseType::SPECIAL_SUMMON, event);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_F: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(23).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(5).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ChangeFieldByCard();
		//		UseCard(AccessibilityFieldFocus::UseType::ACTIVATE, event);
		//	}

		//	break;
		//}
		//case irr::KEY_KEY_G: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(24).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(6).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//		UseCard(AccessibilityFieldFocus::UseType::CHANGE_MODE, event);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_Z: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(34).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (mainGame->scrCardList->isTrulyVisible())
		//			SetSelectableCards();
		//		else if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::SELECTABLE_CARDS;
		//			if (mainGame->wCardSelect->isTrulyVisible()) {
		//				mainGame->dField.display_cards = selectable_cards;
		//				ScreenReader::getReader()->readScreen(fmt::format(L"Selectable Cards {} cards", mainGame->dField.display_cards.size()).data(), false);
		//				mainGame->env->setFocus(mainGame->wCardSelect);
		//			}
		//			else if (selectable_cards.size() != 0) {
		//				DisplayCards(selectable_cards, fmt::format(L"Selectable Cards"));
		//			}
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_X: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(35).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPECIAL_SUMMONABLE_MONSTERS;
		//			if (mainGame->wCardSelect->isTrulyVisible()) {
		//				mainGame->dField.display_cards = selectable_cards;
		//				ScreenReader::getReader()->readScreen(fmt::format(L"Special Summonable Cards {} cards", mainGame->dField.display_cards.size()).data(), false);
		//				mainGame->env->setFocus(mainGame->wCardSelect);
		//			}
		//			else
		//				DisplayCards(spsummonable_cards, fmt::format(L"Special Summonable Cards"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_C: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(36).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_ACTIVABLE_CARDS;
		//			DisplayCards(activatable_cards, fmt::format(L"Activable Cards"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_V: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(37).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(7).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (cardType == AccessibilityFieldFocus::CardType::LINK ||
		//			cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE ||
		//			cardType == AccessibilityFieldFocus::CardType::GRAVEYARD) {
		//			ChangeField(AccessibilityFieldFocus::CardType::MONSTER);
		//		}
		//		else if (cardType == AccessibilityFieldFocus::CardType::MONSTER) {
		//			ChangeField(AccessibilityFieldFocus::CardType::SPELL);
		//		}
		//		else {
		//			ChangeField(AccessibilityFieldFocus::CardType::LINK);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_COMMA: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(5).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(6).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(7).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(8).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnYes->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnYes, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Yes");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnFirst->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnFirst, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"First turn");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		//		}
		//		else if (mainGame->btnPSAU->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnPSAU, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Attack Up");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnPSAD->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnPSAU, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Attack Down");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else {
		//			MouseClick(event, true);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_PERIOD: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(9).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(10).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(11).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnFileSaveNo->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnFileSaveNo, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"No");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnNo->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnNo, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"No");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnSecond->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnSecond, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Second Turn");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		//		}
		//		else if (mainGame->btnPSDU->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnPSDU, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Defense Up");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnPSDD->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnPSDD, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Defense Down");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_I: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(25).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (!mainGame->dField.display_cards.empty() && indexLookedUpCard <= mainGame->dField.display_cards.size() && mainGame->dField.display_cards[indexLookedUpCard]->code != 0) {
		//			//Talvez fosse melhor montar um objeto e mandar para uma função de leitura. Posso até fazer usando o messageBuilder
		//			auto selectedCard = mainGame->dField.display_cards[indexLookedUpCard];
		//			std::wstring cardName = fmt::format(L"{}", gDataManager->GetName(selectedCard->code));
		//			std::wstring cardType = fmt::format(L"{}", gDataManager->FormatType(selectedCard->type));
		//			std::wstring cardAttribute = fmt::format(L"{}", gDataManager->FormatAttribute(selectedCard->attribute));
		//			std::wstring cardLevel = selectedCard->link_marker != 0 ?
		//				fmt::format(L"Link {}", gDataManager->GetCardData(selectedCard->code)->level) :
		//				fmt::format(L"Level {}", gDataManager->GetCardData(selectedCard->code)->level);
		//			std::wstring cardRace = fmt::format(L"{}", gDataManager->FormatRace(selectedCard->race));
		//			std::wstring cardAttack = fmt::format(L"Attack {}", selectedCard->attack);
		//			std::wstring cardDefense = fmt::format(L"Defense: {}", selectedCard->defense);
		//			std::wstring cardEffect = fmt::format(L"{}", gDataManager->GetText(selectedCard->code));
		//			std::wstring position = selectedCard->position == 1 ? fmt::format(L"Attack Position") : fmt::format(L"Defense Position");
		//			std::wstring leftScale = fmt::format(L"Left Scale {}", selectedCard->lscstring);
		//			std::wstring rightScale = fmt::format(L"Right Scale {}", selectedCard->rscstring);
		//			std::wstring fieldSlot = fmt::format(L"Zone {}", SearchFieldSlot(displayedField, selectedCard));
		//			std::wstring linkMarks = GetLinkMarks(selectedCard);
		//			std::wstring overlayedCards = GetOverlayedCards(selectedCard);
		//			std::wstring location = fmt::format(L"{}[{}]", gDataManager->FormatLocation(selectedCard->location, selectedCard->sequence), selectedCard->sequence + 1);
		//			ScreenReader::getReader()->readScreen(cardName.c_str(), false);
		//			ScreenReader::getReader()->readScreen(location.c_str(), false);
		//			if (fieldSlot.compare(L"Zone 0") != 0)
		//				ScreenReader::getReader()->readScreen(fieldSlot.c_str(), false);
		//			if (selectedCard->position != 10)
		//				ScreenReader::getReader()->readScreen(position.c_str(), false);
		//			ScreenReader::getReader()->readScreen(cardType.c_str(), false);
		//			ScreenReader::getReader()->readScreen(cardAttribute.c_str(), false);
		//			if (cardType.find(L"Spell") == std::string::npos && cardType.find(L"Trap") == std::string::npos) {
		//				ScreenReader::getReader()->readScreen(cardLevel.c_str(), false);
		//				ScreenReader::getReader()->readScreen(cardRace.c_str(), false);
		//				ScreenReader::getReader()->readScreen(cardAttack.c_str(), false);
		//				ScreenReader::getReader()->readScreen(cardDefense.c_str(), false);
		//			}
		//			if (!linkMarks.empty())
		//				ScreenReader::getReader()->readScreen(fmt::format(L"Link Marks: {}", linkMarks), false);
		//			if (!overlayedCards.empty())
		//				ScreenReader::getReader()->readScreen(fmt::format(L"Overlayed Cards: {}", overlayedCards), false);
		//			if (leftScale.compare(L"Left Scale ") != 0)
		//				ScreenReader::getReader()->readScreen(leftScale.c_str(), false);
		//			if (rightScale.compare(L"Right Scale ") != 0)
		//				ScreenReader::getReader()->readScreen(rightScale.c_str(), false);
		//			ScreenReader::getReader()->readScreen(cardEffect.c_str(), false);
		//		}
		//		else if (!mainGame->dField.display_cards.empty() && indexLookedUpCard <= mainGame->dField.display_cards.size() && mainGame->dField.display_cards[indexLookedUpCard]->code == 0)
		//			ScreenReader::getReader()->readScreen(fmt::format(L"Face-down Zone {}", SearchFieldSlot(displayedField, mainGame->dField.display_cards[indexLookedUpCard])), false);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_L: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(26).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ScreenReader::getReader()->readScreen(fmt::format(L"Player: {} LP", mainGame->dInfo.lp[AccessibilityFieldFocus::DisplayedField::PLAYER]).c_str(), false);
		//		ScreenReader::getReader()->readScreen(fmt::format(L"Enemy: {} LP", mainGame->dInfo.lp[AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER]).c_str(), false);
		//		ScreenReader::getReader()->readScreen(fmt::format(L"{} seconds left to play", mainGame->dInfo.time_left[AccessibilityFieldFocus::DisplayedField::PLAYER]).c_str(), false);

		//	}
		//	break;
		//}
		//case irr::KEY_KEY_H: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(32).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ScreenReader::getReader()->readScreen(ScreenReader::getReader()->getBuiltMessage(), false);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_J: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(33).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnEP->isVisible() && mainGame->btnEP->isEnabled() && mainGame->dInfo.selfnames.size() > 0)
		//			ScreenReader::getReader()->readScreen(fmt::format(L"Your turn {}", mainGame->dInfo.selfnames.at(0)), false);
		//		else if (mainGame->dInfo.opponames.size() > 0)
		//			ScreenReader::getReader()->readScreen(fmt::format(L"Opponent turn {}", mainGame->dInfo.opponames.at(0)), false);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_P: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(28).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ChangeFieldByCard();
		//		MouseClick(event);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_N: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(30).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(8).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		bool canViewCards = CheckIfCanViewCards(event);
		//		if (canViewCards) {
		//			cardType = AccessibilityFieldFocus::CardType::CHAIN;
		//			lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::CHAINED_CARDS;
		//			DisplayCards(chains, fmt::format(L"Chained Cards"));
		//		}
		//		else
		//			CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_M: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(31).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ScreenReader::getReader()->readScreen(fmt::format(L"Chat active"), false);
		//		mainGame->env->setFocus(mainGame->ebChatInput);
		//	}
		//	break;
		//}
		//case irr::KEY_KEY_B: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(29).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		ScreenReader::getReader()->readLastMessage();
		//	}
		//	break;
		//}
		//case irr::KEY_RETURN: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(27).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
		//		mainGame->env->removeFocus(mainGame->env->getFocus());
		//	else if (!event.KeyInput.PressedDown) {
		//		if (mainGame->btnBP->isEnabled() && battlePhase != AccessibilityFieldFocus::BattleStep::MP1)
		//			battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		//		//Criar função de trigger ok vai quebrar algo?
		//		if (mainGame->btnMsgOK->isTrulyVisible())
		//			TriggerEvent(mainGame->btnMsgOK, irr::gui::EGET_BUTTON_CLICKED);
		//		if (mainGame->btnOptionOK->isVisible())
		//			TriggerEvent(mainGame->btnOptionOK, irr::gui::EGET_BUTTON_CLICKED);
		//		if (mainGame->btnANNumberOK->isTrulyVisible())
		//			TriggerEvent(mainGame->btnANNumberOK, irr::gui::EGET_BUTTON_CLICKED);
		//		if (mainGame->btnOption[0]->isTrulyVisible()) {
		//			SetResponseSelectedOption();
		//		}
		//		else if (!mainGame->dField.display_cards.empty() && indexLookedUpCard <= mainGame->dField.display_cards.size()) {
		//			clicked_card = mainGame->dField.display_cards[indexLookedUpCard];
		//			std::wstring cardName = fmt::format(L"Selected {}", gDataManager->GetName(clicked_card->code));
		//			ScreenReader::getReader()->readScreen(cardName.c_str());
		//			if (mainGame->btnCardSelect[0]->isTrulyVisible() || clicked_card->cmdFlag == 4)
		//				UseCard(AccessibilityFieldFocus::UseType::NO_USE, event);
		//			else
		//				UseCard(AccessibilityFieldFocus::UseType::SELECT_CARD, event);
		//		}
		//		CloseDialog();
		//	}
		//	break;
		//}
		//case irr::KEY_SPACE: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(38).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(9).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->cbANNumber->isTrulyVisible()) {
		//			if (!mainGame->env->hasFocus(mainGame->cbANNumber))
		//				mainGame->env->setFocus(mainGame->cbANNumber);
		//			std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_RIGHT: {
		//	if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (!mainGame->dField.display_cards.empty() && mainGame->dField.display_cards.size() == 1)
		//			indexLookedUpCard = 0;
		//		else if (!mainGame->dField.display_cards.empty() && indexLookedUpCard < mainGame->dField.display_cards.size() - 1)
		//			indexLookedUpCard++;
		//		else if (!mainGame->dField.display_cards.empty() && mainGame->scrCardList->isTrulyVisible()) {
		//			int pos = mainGame->scrCardList->getPos();
		//			mainGame->scrCardList->setPos(pos + 10);
		//			int cardPos = (mainGame->scrCardList->getPos() / 10) + 4;
		//			ScrollCardList();
		//			if (mainGame->dField.display_cards.back() != selectable_cards.back() && cardPos < selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
		//				mainGame->dField.display_cards.push_back(selectable_cards[cardPos]);
		//				mainGame->dField.display_cards.erase(mainGame->dField.display_cards.begin());
		//			}
		//		}
		//		if (!mainGame->dField.display_cards.empty()) {
		//			mainGame->ShowCardInfo(mainGame->dField.display_cards[indexLookedUpCard]->code);
		//			ReadCardName();
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_LEFT: {
		//	if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (!mainGame->dField.display_cards.empty() && mainGame->dField.display_cards.size() == 1)
		//			indexLookedUpCard = 0;
		//		else if (mainGame->dField.display_cards.size() && indexLookedUpCard <= mainGame->dField.display_cards.size() && indexLookedUpCard > 0)
		//			indexLookedUpCard--;
		//		else if (!mainGame->dField.display_cards.empty() && mainGame->scrCardList->isTrulyVisible()) {
		//			int pos = mainGame->scrCardList->getPos();
		//			mainGame->scrCardList->setPos(pos - 10);
		//			int cardPos = (mainGame->scrCardList->getPos() / 10);
		//			ScrollCardList();
		//			if (mainGame->dField.display_cards.front() != selectable_cards.front() && cardPos < selectable_cards.size() && !mainGame->dField.display_cards.empty()) {
		//				mainGame->dField.display_cards.insert(mainGame->dField.display_cards.begin(), selectable_cards[cardPos]);
		//				mainGame->dField.display_cards.pop_back();
		//			}
		//		}
		//		if (!mainGame->dField.display_cards.empty()) {
		//			mainGame->ShowCardInfo(mainGame->dField.display_cards[indexLookedUpCard]->code);
		//			ReadCardName();
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_UP: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(39).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->cbANNumber->isTrulyVisible()) {
		//			if (!mainGame->env->hasFocus(mainGame->cbANNumber))
		//				mainGame->env->setFocus(mainGame->cbANNumber);
		//			std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnOptionn->isTrulyVisible())
		//			TriggerEvent(mainGame->btnOptionn, irr::gui::EGET_BUTTON_CLICKED);
		//		else if (mainGame->btnOption[0]->isTrulyVisible() && selected_option - 1 >= 0 && selected_option - 1 < select_options.size()) {
		//			selected_option--;
		//			ScreenReader::getReader()->readScreen(gDataManager->GetDesc(select_options[selected_option], mainGame->dInfo.compat_mode).data(), false);
		//		}
		//		else if (displayedField != AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER) {
		//			displayedField = AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER;
		//			std::wstring nvdaString = fmt::format(L"Enemy Player Field");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		//			CloseDialog();
		//			MouseClick(event, true);
		//			ChangeFieldAndLook();
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_DOWN: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(40).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->cbANNumber->isTrulyVisible()) {
		//			if (!mainGame->env->hasFocus(mainGame->cbANNumber))
		//				mainGame->env->setFocus(mainGame->cbANNumber);
		//			std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnOptionp->isTrulyVisible())
		//			TriggerEvent(mainGame->btnOptionp, irr::gui::EGET_BUTTON_CLICKED);
		//		else if (mainGame->btnOption[0]->isTrulyVisible() && selected_option + 1 < select_options.size()) {
		//			selected_option++;
		//			ScreenReader::getReader()->readScreen(gDataManager->GetDesc(select_options[selected_option], mainGame->dInfo.compat_mode).data(), false);
		//		}
		//		else if (displayedField != AccessibilityFieldFocus::DisplayedField::PLAYER) {
		//			displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
		//			std::wstring nvdaString = fmt::format(L"Player Field");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str());
		//			CloseDialog();
		//			MouseClick(event, true);
		//			ChangeFieldAndLook();
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD1:
		//case irr::KEY_KEY_1: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(1).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(2).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnDisplayOK->isTrulyVisible())
		//			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//		if (mainGame->btnHand[0]->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnHand[0], irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"SCISSORS");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else
		//		{
		//			SelectFieldSlot(1, displayedField);
		//			MouseClick(event);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD2:
		//case irr::KEY_KEY_2: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(1).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(3).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnHand[1]->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnHand[1], irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"ROCK");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnOption[1]->isTrulyVisible()) {
		//			selected_option = 1;
		//			SetResponseSelectedOption();
		//		}
		//		else
		//		{
		//			if (mainGame->btnDisplayOK->isTrulyVisible())
		//				TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//			SelectFieldSlot(2, displayedField);
		//			MouseClick(event);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD3:
		//case irr::KEY_KEY_3: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(1).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(4).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnHand[2]->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnHand[2], irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Paper");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//		else if (mainGame->btnOption[2]->isTrulyVisible()) {
		//			selected_option = 2;
		//			SetResponseSelectedOption();
		//		}
		//		else
		//		{
		//			if (mainGame->btnDisplayOK->isTrulyVisible())
		//				TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//			SelectFieldSlot(3, displayedField);
		//			MouseClick(event);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD4:
		//case irr::KEY_KEY_4: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnOption[3]->isTrulyVisible()) {
		//			selected_option = 3;
		//			SetResponseSelectedOption();
		//		}
		//		else {
		//			if (mainGame->btnDisplayOK->isTrulyVisible())
		//				TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//			SelectFieldSlot(4, displayedField);
		//			MouseClick(event);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD5:
		//case irr::KEY_KEY_5: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnOption[4]->isTrulyVisible()) {
		//			selected_option = 4;
		//			SetResponseSelectedOption();
		//		}
		//		else {
		//			if (mainGame->btnDisplayOK->isTrulyVisible())
		//				TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//			SelectFieldSlot(5, displayedField);
		//			MouseClick(event);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD6:
		//case irr::KEY_KEY_6: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnDisplayOK->isTrulyVisible())
		//			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//		SelectFieldSlot(6, displayedField);
		//		MouseClick(event);
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD7:
		//case irr::KEY_KEY_7: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(41).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnDisplayOK->isTrulyVisible())
		//			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
		//		SelectFieldSlot(7, displayedField);
		//		MouseClick(event);
		//	}
		//	break;
		//}
		//case irr::KEY_NUMPAD0:
		//case irr::KEY_KEY_0: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(44).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnLeaveGame->isTrulyVisible()) {
		//			TriggerEvent(mainGame->btnLeaveGame, irr::gui::EGET_BUTTON_CLICKED);
		//			std::wstring nvdaString = fmt::format(L"Surrender");
		//			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
		//		}
		//	}
		//	break;
		//}
		//case irr::KEY_BACK: {
		//	if (event.KeyInput.Control && !event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		StringBuilder::cleanBuiltMessage();
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityString(45).data());
		//		StringBuilder::AddLine(gDataManager->GetAccessibilityTipsString(10).data());
		//		ScreenReader::getReader()->readScreen(StringBuilder::getBuiltMessage(), false);
		//	}
		//	else if (!event.KeyInput.PressedDown && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX)) {
		//		if (mainGame->btnBP->isVisible() && mainGame->btnBP->isEnabled()) {
		//			TriggerEvent(mainGame->btnBP, irr::gui::EGET_BUTTON_CLICKED);
		//			battlePhase = AccessibilityFieldFocus::BattleStep::BP;
		//		}
		//		else if (mainGame->btnM2->isVisible() && mainGame->btnM2->isEnabled()) {
		//			TriggerEvent(mainGame->btnM2, irr::gui::EGET_BUTTON_CLICKED);
		//			battlePhase = AccessibilityFieldFocus::BattleStep::MP2;
		//		}
		//		else /*if (!mainGame->btnBP->isEnabled() && !mainGame->btnM2->isEnabled())*/ {
		//			TriggerEvent(mainGame->btnEP, irr::gui::EGET_BUTTON_CLICKED);
		//			battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
		//		}
		//	}
		//	break;
		//}
	}
	void EventHandler::CloseDialog() {
		if (mainGame->wCardDisplay->isVisible()) {
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
			if (!mainGame->dField.display_cards.empty())
				mainGame->dField.display_cards.clear();
		}
	}
	/*

	void EventHandler::ScrollCardList() {
		if (mainGame->btnCardSelect[0]->isTrulyVisible()) {
			irr::SEvent newEvent;
			newEvent.EventType = irr::EEVENT_TYPE::EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = mainGame->scrCardList;
			newEvent.GUIEvent.Element = 0;
			newEvent.GUIEvent.EventType = irr::gui::EGUI_EVENT_TYPE::EGET_SCROLL_BAR_CHANGED;
			mainGame->scrCardList->OnEvent(newEvent);
		}
	}*/

	bool EventHandler::CheckIfCanViewCards(irr::SEvent event) {
		event.KeyInput.PressedDown = false;
		bool canViewCards = false;
		if (!event.KeyInput.PressedDown && !mainGame->dInfo.isReplay && mainGame->dInfo.player_type != 7 && mainGame->dInfo.isInDuel
			&& !mainGame->wCardDisplay->isVisible() && !mainGame->HasFocus(irr::gui::EGUIET_EDIT_BOX))
			canViewCards = true;
		return canViewCards;
	}

	void EventHandler::DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text) {
		mainGame->dField.display_cards.clear();
		indexLookedUpCard = 0;
		for (auto it = field.begin(); it != field.end(); ++it) {
			if (*it) {
				mainGame->dField.display_cards.push_back(*it);
			}
		}
		if (mainGame->dField.display_cards.size()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", text, mainGame->dField.display_cards.size()).data());
			ShowLocationCard();
			if (text.compare(L"") != 0) {
				ScreenReader::getReader()->readScreen(fmt::format(L"{}{} cards", text, mainGame->dField.display_cards.size()).data(), false);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
		else
		{
			std::wstring nvdaString = fmt::format(L"There are no cards to display");
			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
			CloseDialog();
		}
	}
	void EventHandler::ShowLocationCard() {
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
			auto& curstring = mainGame->stDisplayPos[i];
			auto& curcard = mainGame->dField.display_cards[i];
			curstring->enableOverrideColor(false);
			if (curcard->code)
				mainGame->imageLoading[mainGame->btnCardDisplay[i]] = curcard->code;
			else
				mainGame->btnCardDisplay[i]->setImage(mainGame->imageManager.tCover[curcard->controler]);
			mainGame->btnCardDisplay[i]->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 55, startpos + 120 + i * 125, 225));
			mainGame->btnCardDisplay[i]->setPressed(false);
			mainGame->btnCardDisplay[i]->setVisible(true);
			std::wstring text;
			if (curcard->location == LOCATION_OVERLAY) {
				text = fmt::format(L"{}[{}]({})", gDataManager->FormatLocation(curcard->overlayTarget->location, curcard->overlayTarget->sequence),
					curcard->overlayTarget->sequence + 1, curcard->sequence + 1);
			}
			else if (curcard->location) {
				text = fmt::format(L"{}[{}]", gDataManager->FormatLocation(curcard->location, curcard->sequence),
					curcard->sequence + 1);
			}
			curstring->setText(text.data());
			if (curcard->location == LOCATION_OVERLAY) {
				if (curcard->owner != curcard->overlayTarget->controler)
					curstring->setOverrideColor(skin::DUELFIELD_CARD_SELECT_WINDOW_OVERLAY_TEXT_VAL);
				if (curcard->overlayTarget->controler)
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
				else
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
			}
			else if (curcard->location == LOCATION_EXTRA || curcard->location == LOCATION_REMOVED) {
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
			curstring->setVisible(true);
			curstring->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 30, startpos + 120 + i * 125, 50));
		}
		if (mainGame->dField.display_cards.size() <= 5) {
			for (int i = mainGame->dField.display_cards.size(); i < 5; ++i) {
				mainGame->btnCardDisplay[i]->setVisible(false);
				mainGame->stDisplayPos[i]->setVisible(false);
			}
			mainGame->scrDisplayList->setPos(0);
			mainGame->scrDisplayList->setVisible(false);
		}
		else {
			mainGame->scrDisplayList->setVisible(true);
			mainGame->scrDisplayList->setMin(0);
			mainGame->scrDisplayList->setMax((mainGame->dField.display_cards.size() - 5) * 10 + 9);
			mainGame->scrDisplayList->setPos(0);
		}
		mainGame->btnDisplayOK->setVisible(true);
		mainGame->PopupElement(mainGame->wCardDisplay);
	}
	//void EventHandler::DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text) {
	//	mainGame->dField.display_cards.clear();
	//	indexLookedUpCard = 0;
	//	for (auto it = field.begin(); it != field.end(); ++it) {
	//		mainGame->dField.display_cards.push_back(it._Ptr->chain_card);
	//	}
	//	if (mainGame->dField.display_cards.size()) {
	//		mainGame->wCardDisplay->setText(fmt::format(L"{}({})", gDataManager->GetSysString(lookupFieldLocId), mainGame->dField.display_cards.size()).data());
	//		ShowLocationCard();
	//		mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
	//	}
	//}

	//void EventHandler::SetSelectableCards() {
	//	indexLookedUpCard = 0;
	//	if (selectable_cards.size()) {
	//		mainGame->dField.display_cards.clear();
	//		for (int i = 0; i < 5; ++i) {
	//			if (selectable_cards.size() > i)
	//				mainGame->dField.display_cards.push_back(selectable_cards[i]);
	//		}
	//		mainGame->ShowCardInfo(mainGame->dField.display_cards[indexLookedUpCard]->code);
	//	}
	//	else
	//	{
	//		std::wstring nvdaString = fmt::format(L"There are no cards to display");
	//		ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
	//		CloseDialog();
	//	}
	//}

	//void EventHandler::SelectFieldSlot(int slot, const AccessibilityFieldFocus::DisplayedField& player, const AccessibilityFieldFocus::CardType& cardType) {
	//	if (slot == 0) slot = 1;
	//	auto cursor = mainGame->device->getCursorControl();
	//	auto pos = cursor->getRelativePosition();
	//	int fieldSlot = GetFieldSlot(slot, player);
	//	pos.X = GetXPosition(fieldSlot, player);
	//	pos.Y = GetYPosition();
	//	auto test = matManager.vFieldMzone[1][0][2].Pos.X;
	//	auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
	//	clamp(pos.X);
	//	clamp(pos.Y);
	//	cursor->setPosition(pos.X, pos.Y);
	//}

	//void EventHandler::SelectFieldSlotNoPlayer(int slot) {
	//	if (slot == 0) slot = 1;
	//	auto cursor = mainGame->device->getCursorControl();
	//	auto pos = cursor->getRelativePosition();
	//	pos.X = GetXPosition(slot);
	//	pos.Y = GetYPosition(slot);
	//	auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
	//	clamp(pos.X);
	//	clamp(pos.Y);
	//	if (GetCardField() == AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND)
	//		cursor->setPosition(clicked_card->hand_collision.getCenter());
	//	else
	//		cursor->setPosition(pos.X, pos.Y);
	//}

	//void EventHandler::ChangeFieldByCard() {
	//	bool selected = false;
	//	if (!clicked_card)
	//		return;
	//	for (int i = 0; i < 5; i++) {
	//		if (mzone[0][i] && mzone[0][i] == clicked_card) {
	//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
	//			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
	//			selected = true;
	//			break;
	//		}
	//		else if (szone[0][i] && szone[0][i] == clicked_card) {
	//			cardType = AccessibilityFieldFocus::CardType::SPELL;
	//			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
	//			selected = true;
	//			break;
	//		}
	//	}
	//	if (!selected) {
	//		std::wstring cardTypeString = fmt::format(L"{}", gDataManager->FormatType(clicked_card->type));
	//		if (cardTypeString.find(L"Spell") == std::string::npos && cardTypeString.find(L"Trap") == std::string::npos) {
	//			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
	//			cardType = AccessibilityFieldFocus::CardType::MONSTER;
	//		}
	//		else {
	//			lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
	//			cardType = AccessibilityFieldFocus::CardType::SPELL;
	//		}
	//	}
	//}

	//AccessibilityFieldFocus::DisplayedCards EventHandler::GetCardField() {
	//	for (int i = 0; i < hand[0].size(); i++) {
	//		if (hand[0].size() > i && hand[0][i] == clicked_card) {
	//			return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
	//		}
	//		else if (hand[1].size() > i && hand[1][i] == clicked_card) {
	//			return AccessibilityFieldFocus::DisplayedCards::DISPLAY_HAND;
	//		}
	//	}
	//	return AccessibilityFieldFocus::DisplayedCards::DISPLAY_FIELD;
	//}

	//int EventHandler::GetFieldSlot(const int& slot, const AccessibilityFieldFocus::DisplayedField& player, const AccessibilityFieldFocus::CardType& cardType) {
	//	if (player == AccessibilityFieldFocus::DisplayedField::PLAYER && cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE)
	//		return slot;
	//	else if (player == AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER && cardType == AccessibilityFieldFocus::CardType::NO_CARD_TYPE) {
	//		//if (slot > 5)
	//		//	return slot;
	//		return 6 - slot;
	//	}

	//	int fieldSlot = 1;
	//	for (int i = 0; i < 5; i++) {
	//		if (mzone[1][i] && mzone[1][i] == clicked_card) {
	//			fieldSlot = 5 - i;
	//			break;
	//		}
	//	}
	//	return fieldSlot;
	//}

	//bool EventHandler::CheckIfFieldSlotIsFree(const int& slot, const AccessibilityFieldFocus::DisplayedField& player, const int& cardType) {
	//	ClientCard* x;
	//	bool free = false;
	//	switch (cardType)
	//	{
	//	case AccessibilityFieldFocus::CardType::MONSTER:
	//		if (mzone[player][slot] == NULL)
	//			free = true;
	//		break;
	//	case AccessibilityFieldFocus::CardType::SPELL:
	//		x = szone[player][slot];
	//		break;
	//	default:
	//		break;
	//	}
	//	return free;
	//}

	//std::wstring EventHandler::GetLinkMarks(ClientCard* card)
	//{
	//	std::wstring linkMark = std::wstring();
	//	const int mark = card->link_marker;
	//	if (mark & LINK_MARKER_BOTTOM_LEFT) {
	//		linkMark += L"Bottom Left,";
	//	}
	//	if (mark & LINK_MARKER_BOTTOM) {
	//		linkMark += L"Bottom, ";
	//	}
	//	if (mark & LINK_MARKER_BOTTOM_RIGHT) {
	//		linkMark += L"Bottom Right, ";
	//	}
	//	if (mark & LINK_MARKER_TOP_LEFT) {
	//		linkMark += L"Top Left, ";
	//	}
	//	if (mark & LINK_MARKER_TOP) {
	//		linkMark += L"Top, ";
	//	}
	//	if (mark & LINK_MARKER_TOP_RIGHT) {
	//		linkMark += L"Top Right, ";
	//	}
	//	return linkMark;
	//}

	//std::wstring EventHandler::GetOverlayedCards(ClientCard* card)
	//{
	//	std::wstring overlayedCards = std::wstring();
	//	if (card->overlayed.size() > 0) {
	//		for (auto it = card->overlayed.begin(); it != card->overlayed.end(); ++it) {
	//			if (*it) {
	//				overlayedCards += fmt::format(L"{}, ", gDataManager->GetName((*it)->code));
	//			}
	//		}
	//	}
	//	return overlayedCards;
	//}

	//void EventHandler::SetLookUpField() {
	//	//if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_DECK) {
	//	//	lookupFieldLocId = AccessibilityFieldFocus::PLAYER_DECK;
	//	//	cardType = AccessibilityFieldFocus::CardType::DECK;
	//	//}
	//	//else
	//	if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_MONSTERS) {
	//		lookupFieldLocId = AccessibilityFieldFocus::PLAYER_MONSTERS;
	//		cardType = AccessibilityFieldFocus::CardType::MONSTER;
	//		//ChangeField(AccessibilityFieldFocus::CardType::MONSTER);
	//	}
	//	else if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_SPELLS) {
	//		lookupFieldLocId = AccessibilityFieldFocus::PLAYER_SPELLS;
	//		cardType = AccessibilityFieldFocus::CardType::SPELL;
	//		//ChangeField(AccessibilityFieldFocus::CardType::SPELL);
	//	}
	//	else if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_GRAVEYARD) {
	//		lookupFieldLocId = AccessibilityFieldFocus::PLAYER_GRAVEYARD;
	//		cardType = AccessibilityFieldFocus::CardType::GRAVEYARD;
	//	}
	//	//else if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_BANNED_CARDS) {
	//	//	lookupFieldLocId = AccessibilityFieldFocus::PLAYER_BANNED_CARDS;
	//	//	cardType = AccessibilityFieldFocus::CardType::BANNED;
	//	//}
	//	//else if (clicked_card && clicked_card->location == AccessibilityFieldFocus::PLAYER_EXTRA_DECK) {
	//	//	lookupFieldLocId = AccessibilityFieldFocus::PLAYER_EXTRA_DECK;
	//	//	cardType = AccessibilityFieldFocus::CardType::MONSTER;
	//	//}
	//}

	//void EventHandler::ReadCardName() {
	//	std::wstring nvdaString;
	//	SetLookUpField();
	//	if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS || lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS) {
	//		if (mainGame->dField.display_cards[indexLookedUpCard]->code != 0)
	//			nvdaString = fmt::format(L"{} {} attack {} defense zone {}", gDataManager->GetName(mainGame->dField.display_cards[indexLookedUpCard]->code), mainGame->dField.display_cards[indexLookedUpCard]->attack, mainGame->dField.display_cards[indexLookedUpCard]->defense, SearchFieldSlot(displayedField, mainGame->dField.display_cards[indexLookedUpCard]));
	//		else
	//			nvdaString = fmt::format(L"Face-down zone {}", SearchFieldSlot(displayedField, mainGame->dField.display_cards[indexLookedUpCard]));
	//	}
	//	else {
	//		if (mainGame->dField.display_cards[indexLookedUpCard]->code != 0)
	//			nvdaString = fmt::format(L"{} slot {}", gDataManager->GetName(mainGame->dField.display_cards[indexLookedUpCard]->code), indexLookedUpCard);
	//		else
	//			nvdaString = fmt::format(L"Face-down slot {}", indexLookedUpCard);
	//	}
	//	ScreenReader::getReader()->readScreen(nvdaString.c_str());
	//}

	//void EventHandler::TriggerOkButton()
	//{
	//}

	//void EventHandler::ChangeFieldAndLook()
	//{
	//	if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_HAND)
	//		DisplayCards(hand[displayedField], fmt::format(L"Hand"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS)
	//		DisplayCards(mzone[displayedField], fmt::format(L"Monster Zone"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS)
	//		DisplayCards(szone[displayedField], fmt::format(L"Spells"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_EXTRA_DECK)
	//		DisplayCards(extra[displayedField], fmt::format(L"Extra Deck"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_GRAVEYARD)
	//		DisplayCards(grave[displayedField], fmt::format(L"Graveyard"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_BANNED_CARDS)
	//		DisplayCards(remove[displayedField], fmt::format(L"Removed Cards"));
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_DECK)
	//		DisplayCards(deck[displayedField], fmt::format(L"Deck"));
	//}

	//int EventHandler::SearchFieldSlot(const int& displayedField, ClientCard* card) {
	//	SetLookUpField();
	//	auto selectedCard = card == NULL ? clicked_card : card;
	//	int fieldSlot = 0;
	//	for (int i = 0; i < 7; i++) {
	//		if ((mzone[displayedField][i] && mzone[displayedField][i] == selectedCard) || (szone[displayedField][i] && szone[displayedField][i] == selectedCard)) {
	//			if (displayedField == AccessibilityFieldFocus::DisplayedField::PLAYER && i < 5)
	//				fieldSlot = i + 1;
	//			else if (i < 5)
	//				fieldSlot = 5 - i;
	//			else if (szone[displayedField][i] == selectedCard)
	//				fieldSlot = i + 1;
	//			else {
	//				lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::LINK_ZONE;
	//				if (displayedField == AccessibilityFieldFocus::DisplayedField::PLAYER)
	//					fieldSlot = i - 4;
	//				else {
	//					if (i == 5)
	//						fieldSlot = 2;
	//					else
	//						fieldSlot = 1;
	//				}
	//			}

	//			break;
	//		}
	//	}
	//	return fieldSlot;
	//}

	//float EventHandler::GetXPosition(int slot, const AccessibilityFieldFocus::DisplayedField& player) {
	//	if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::LINK_ZONE) {
	//		cardType = AccessibilityFieldFocus::CardType::LINK;
	//	}
	//	else if (slot > 5 && lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS) {
	//		slot = -0.5;//041
	//	}
	//	float posX = 0.f;
	//	auto fieldSlotSize = 0.08;
	//	float startPosition = 0.40f;
	//	if (player == AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER && cardType != AccessibilityFieldFocus::CardType::LINK) {
	//		fieldSlotSize = 0.073f;
	//		startPosition = 0.43f;
	//	}
	//	if (cardType == AccessibilityFieldFocus::CardType::MONSTER || cardType == AccessibilityFieldFocus::CardType::SPELL)
	//		posX = startPosition + (slot * fieldSlotSize);
	//	else if (cardType == AccessibilityFieldFocus::CardType::LINK) {
	//		switch (slot)
	//		{
	//		case 1: {
	//			posX = 0.40 + (2 * fieldSlotSize);
	//			break;
	//		}
	//		case 2: {
	//			posX = 0.40 + (4 * fieldSlotSize);
	//			break;
	//		}
	//		case 4: {
	//			posX = 0.40 + (4 * fieldSlotSize);
	//			break;
	//		}
	//		case 5: {
	//			posX = 0.40 + (2 * fieldSlotSize);
	//			break;
	//		}
	//		default:
	//			posX = 0.60;
	//			break;
	//		}
	//	}
	//	else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_GRAVEYARD || lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_DECK) {
	//		int localSlot = 6;
	//		if (displayedField == AccessibilityFieldFocus::DisplayedField::PLAYER) {
	//			startPosition = 0.43f;
	//		}
	//		else {
	//			startPosition = 0.0f;
	//		}
	//		posX = startPosition + (localSlot * fieldSlotSize);
	//	}
	//	return posX;
	//}

	//float EventHandler::GetXPosition(const AccessibilityFieldFocus::Scroll& position) {
	//	float posX = 0.f;
	//	switch (position)
	//	{
	//	case ygo::AccessibilityFieldFocus::Scroll::RIGHT: {
	//		posX = 0.94f;
	//		break;
	//	}
	//	case ygo::AccessibilityFieldFocus::Scroll::LEFT: {
	//		posX = 0.36f;
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//	return posX;
	//}

	//float EventHandler::GetYPosition(int slot) {
	//	float posY = 0.f;
	//	float startPosY = 0.6f;
	//	float startSpellPosY = 0.15f;
	//	float LinkSummonZoneY = 0.515f;
	//	if (displayedField == AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER) {
	//		startPosY = 0.4f;
	//		startSpellPosY = -0.05f;
	//	}
	//	if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_GRAVEYARD) {
	//		/*if (displayedField == AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER)
	//			startSpellPosY = -0.04f;
	//		else*/
	//		startSpellPosY = 0.05f;
	//		posY = startPosY + startSpellPosY;
	//	}
	//	/*else if (lookupFieldLocId == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_DECK) {
	//		if (displayedField == AccessibilityFieldFocus::DisplayedField::ENEMY_PLAYER)
	//			startSpellPosY = -0.09f;
	//		else
	//			startSpellPosY = 0.18f;
	//		posY = startPosY + startSpellPosY;
	//	}*/
	//	else if (cardType == AccessibilityFieldFocus::CardType::MONSTER)
	//		posY = startPosY;
	//	else if (cardType == AccessibilityFieldFocus::CardType::SPELL) {
	//		if (slot > 5) {
	//			startSpellPosY = 0.05f;
	//		}
	//		posY = startPosY + startSpellPosY;
	//	}
	//	else if (cardType == AccessibilityFieldFocus::CardType::LINK)
	//		posY = LinkSummonZoneY;
	//	return posY;
	//}

	//void EventHandler::SimulateButton(irr::gui::IGUIElement* caller) {
	//	irr::SEvent simulated{};
	//	simulated.EventType = irr::EET_GUI_EVENT;
	//	simulated.GUIEvent.EventType = irr::gui::EGET_BUTTON_CLICKED;
	//	simulated.GUIEvent.Caller = caller;
	//	mainGame->device->postEventFromUser(simulated);
	//}

	//void EventHandler::MouseClick(const irr::SEvent& event, bool rightClick) {
	//	auto cursor = mainGame->device->getCursorControl();
	//	auto pos = cursor->getRelativePosition();

	//	auto& jevent = event.JoystickEvent;
	//	static irr::u32 buttonstates = 0;
	//	buttonstates |= irr::E_MOUSE_BUTTON_STATE_MASK::EMBSM_LEFT;
	//	irr::SEvent simulated{};
	//	simulated.EventType = irr::EET_MOUSE_INPUT_EVENT;
	//	simulated.MouseInput.ButtonStates = buttonstates;
	//	simulated.MouseInput.Control = false;
	//	simulated.MouseInput.Shift = false;
	//	simulated.MouseInput.X = irr::core::round32(pos.X * mainGame->window_size.Width);
	//	simulated.MouseInput.Y = irr::core::round32(pos.Y * mainGame->window_size.Height);

	//	buttonstates |= (simulated.MouseInput.Control) ? 1 << 30 : 0;
	//	buttonstates |= (simulated.MouseInput.Shift) ? 1 << 29 : 0;

	//	auto& changed = jevent.POV;

	//	auto CheckAndPost = [device = mainGame->device, &simulated, &changed, &states = jevent.ButtonStates](int button, irr::EMOUSE_INPUT_EVENT type) {
	//		simulated.MouseInput.Event = (states & button) ? type : (irr::EMOUSE_INPUT_EVENT)(type + 3);
	//		device->postEventFromUser(simulated);
	//	};

	//	CheckAndPost(JWrapper::Buttons::A, rightClick ? irr::EMIE_RMOUSE_PRESSED_DOWN : irr::EMIE_LMOUSE_PRESSED_DOWN);
	//}

	//void EventHandler::SetMouseOnCard()
	//{
	//	auto cursor = mainGame->device->getCursorControl();
	//	auto pos = cursor->getRelativePosition();
	//	pos.X = clicked_card->hand_collision.getCenter().X;
	//	pos.Y = clicked_card->hand_collision.getCenter().Y;
	//	auto clamp = [](auto& val) { val = (val < 0.f) ? 0.f : (1.f < val) ? 1.f : val;	};
	//	clamp(pos.X);
	//	clamp(pos.Y);
	//	cursor->setPosition(clicked_card->hand_collision.getCenter());
	//}
}
