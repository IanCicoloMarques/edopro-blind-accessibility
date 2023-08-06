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

	void EventHandler::ActivateCard(const irr::SEvent& event)
	{
		if (std::find(mainGame->dField.spsummonable_cards.begin(), mainGame->dField.spsummonable_cards.end(), mainGame->dField.clicked_card) == mainGame->dField.spsummonable_cards.end())
			EffectResolver(event);
		ChangeFieldByCard();
		UseCard(AccessibilityFieldFocus::UseType::ACTIVATE, event);
	}

	void EventHandler::StartChat()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(88).data()), false);
		mainGame->env->setFocus(mainGame->ebChatInput);
	}

	void EventHandler::UseCard(AccessibilityFieldFocus::UseType use, const irr::SEvent& event, ClientCard* clientCard)
	{
		return;
	}


	void EventHandler::UseSelectedCard(const irr::SEvent& event)
	{
		// DuelController::SelectCard
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

	void EventHandler::MouseClick(const irr::SEvent& event, bool cond)
	{
		return;
	}

	void EventHandler::CloseDialog()
	{
		return;
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

	void EventHandler::SelectFieldSlot(int slot, AccessibilityFieldFocus::Player player)
	{
		return;
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

	void EventHandler::MovementCommands(const irr::SEvent& event)
	{
		return;
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


	void EventHandler::PlayerInformation()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(85).data(),mainGame->dInfo.lp[AccessibilityFieldFocus::Player::PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(86).data(), mainGame->dInfo.lp[AccessibilityFieldFocus::Player::ENEMY_PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(87).data(), mainGame->dInfo.time_left[AccessibilityFieldFocus::Player::PLAYER]), false);
	}

	void EventHandler::TriggerOk()
	{
		return;
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
	}

	void EventHandler::DisplaySelectableCards(const irr::SEvent& event)
	{
		return;
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
		UseCard(AccessibilityFieldFocus::UseType::CHANGE_BATTLE_POSITION, event);
	};

	void EventHandler::SelectOption(const int i)
	{
		if (mainGame->btnOption[i]->isTrulyVisible()) {
			mainGame->dField.selected_option = i;
			SetResponseSelectedOption();
		}
	};

	void EventHandler::DuelCommandsOld(const irr::SEvent& event)
	{

		if(event.KeyInput.Key == KeyboardConfiguration::Chat)
			StartChat();
		else if(event.KeyInput.Key == KeyboardConfiguration::RotateField)
			RotateField();
		else if(event.KeyInput.Key == KeyboardConfiguration::Attack && battlePhase == AccessibilityFieldFocus::BattleStep::BP)
			UseCard(AccessibilityFieldFocus::UseType::ATTACK, event);

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

	bool EventHandler::CheckIfCanViewCards(const irr::SEvent& event)
	{
		return true;
	}

	void EventHandler::SelectCard(const std::vector<ClientCard*>& vector, const std::basic_string<wchar_t>& format)
	{
		return;
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

	void EventHandler::CancelOrFinish()
	{
		DuelClient::SetResponseI(0);
	}

	void EventHandler::DisplayCards(const std::vector<ClientCard*>& vector, const std::basic_string<wchar_t>& format)
	{
		return;
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
