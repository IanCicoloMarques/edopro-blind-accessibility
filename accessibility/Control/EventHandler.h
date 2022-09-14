#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/FieldFocus/AccessibilityFieldFocus.h"
#include "../gframe/duelclient.h"
#include "../gframe/client_card.h"
#include "../gframe/game.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/custom_skin_enum.h"
#include "../gframe/joystick_wrapper.h"
#include <vector>
#include <string>
//#include "../accessibility/Control/CardsDTO.h"

namespace ygo {
	class EventHandler : public IEventHandler
	{
	public:
		static IEventHandler* getEventHandler();
		virtual void PushKey(const irr::SEvent& event) override;
	private:
		static IEventHandler* eventHandler;
		bool accessibilityFocus = true; //TODO- FAZER UMA CONFIGURAÇÃO NO MENU PRA ISSO
		bool selectZone = false;
		int cardSelectPosition = 0;
		int indexLookedUpCard = 0;
		AccessibilityFieldFocus::DisplayedField displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
		int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
		int battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
		int cardType = AccessibilityFieldFocus::CardType::MONSTER;
		bool CheckIfCanViewCards(irr::SEvent event);
		void DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text);
		void DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text);
		void CloseDialog();
		void ShowLocationCard();
		bool UseCard(const AccessibilityFieldFocus::UseType& useType, irr::SEvent event);
		void SetLookUpField();
		void ShowMenu(int flag, int x, int y);
		void MouseClick(const irr::SEvent& event, bool rightClick = false);
		void ChangeFieldAndLook();
		void SelectFieldSlotNoPlayer(int slot);
		float GetYPosition(int slot = 1);
		float GetXPosition(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		AccessibilityFieldFocus::DisplayedCards GetCardField();
		void SelectFieldSlot(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		int SearchFieldSlot(const int& displayedField, ClientCard* card = NULL);
		void ChangeFieldByCard();
		std::wstring GetLinkMarks(ClientCard* card);
		std::wstring GetOverlayedCards(ClientCard* card);
		void ChangeField(const AccessibilityFieldFocus::CardType& cardField);
		int GetFieldSlot(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		void ScrollCardList();
		float GetXPosition(const AccessibilityFieldFocus::Scroll& position = AccessibilityFieldFocus::Scroll::RIGHT);
		void ReadCardName();
		void SetSelectableCards();
		void SetResponseSelectedOption() const;
		/*
		void SimulateButton(irr::gui::IGUIElement* caller = nullptr);
		void SetMouseOnCard();
		void TriggerOkButton();
		bool CheckIfFieldSlotIsFree(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		*/
	};
}

#endif
