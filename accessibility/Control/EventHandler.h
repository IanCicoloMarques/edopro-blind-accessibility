#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../accessibility/Configuration/AccessibilityConfiguration.h"
#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/FieldFocus/AccessibilityFieldFocus.h"
#include "../gframe/duelclient.h"
#include "../gframe/client_card.h"
#include "../gframe/game.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/custom_skin_enum.h"
#include "../gframe/joystick_wrapper.h"
#include "../gframe/sound_manager.h"
#include <vector>
#include <string>
#include <IGUIEditBox.h>
#include <IGUIWindow.h>
#include <IrrlichtDevice.h>
#include <IGUIStaticText.h>
#include <IGUIScrollBar.h>
#include <IGUIComboBox.h>
#include <IGUIListBox.h>

namespace ygo {
	class EventHandler : public IEventHandler
	{
	public:
		static IEventHandler* getEventHandler();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
		static IEventHandler* eventHandler;
		static int indexLookedUpCard;
		static int battlePhase;
		static bool effectResolver;
	private:
		bool selectZone = false;
		int cardSelectPosition = 0;
		AccessibilityFieldFocus::DisplayedField displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
		int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
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
		void SelectFieldSlotHandAllowed(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		float GetYPosition(const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		float GetYPositionPlayer();
		float GetYPositionEnemy();
		float GetYPositionLink();
		float GetXPosition(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		float GetXPositionPlayer(int slot);
		float GetXPositionEnemy(int slot);
		float GetXPositionLink(int slot);
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
		void TriggerOk();
		void EffectResolver(irr::SEvent event);
		void GetCardLocation(ClientCard* card);
		/*
		void SimulateButton(irr::gui::IGUIElement* caller = nullptr);
		void SetMouseOnCard();
		void TriggerOkButton();
		bool CheckIfFieldSlotIsFree(const int& slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		*/
	};
}

#endif
