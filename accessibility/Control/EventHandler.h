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
#include <IGUICheckBox.h>

namespace ygo {
	class EventHandler : public IEventHandler
	{
	public:
		static IEventHandler* getEventHandler();
		void TriggerEndPhase();
		void TriggerBattlePhase();
		void TriggerMainPhase2();
		void DisplaySpellField(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void ActivateCard(const irr::SEvent& event);
		void DisplayGraveyard(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void DisplayHand(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void StartChat();
		void DisplayChain(const irr::SEvent& event);
		void DisplayMonsterField(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void DisplayExtraDeck(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void DisplayDeck(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void DisplaySpecialSummonableMonsters(const irr::SEvent& event);
		void DisplayRemovedCards(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayed_field);
		void DisplaySelectableCards(const irr::SEvent& event);
		void DisplayActivableCards(const irr::SEvent& event);
		void ClickButton(irr::gui::IGUIButton* button, int message_code, bool saveHistory);
		void UseSelectedCard(const irr::SEvent& event);
		void ChangeLookedUpCardIndex(irr::EKEY_CODE ekey_code);
		void ScrollDisplayCards(unsigned int initialIndex, irr::EKEY_CODE ekeyCode);
		void ShowCardInfo();
		void ChangeLookedUpField(const irr::SEvent& event, AccessibilityFieldFocus::DisplayedField displayedField, int messageCode);
		void SetSlot(const irr::SEvent& event, int slot);
		void RockPaperScissors(irr::EKEY_CODE ekeyCode);
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
		int SearchFieldSlot(const int& displayedField, ClientCard* card = NULL, bool looped = false);
		void ShowOptions();
		static void SetKeyboardConfiguration();
		static IEventHandler* eventHandler;
		static unsigned int indexLookedUpCard;
		static int battlePhase;
		static bool effectResolver;
		static bool mudConfiguration;
		static bool selectZone;
		static bool rockPaperScissor;
	private:
		const int selectAttributeMax = 7;
		const int selectTypeMax = 25;
		int cardSelectPosition = 0;
		int selectAttribute = 0;
		int selectType = 0;
		AccessibilityFieldFocus::DisplayedField displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
		int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
		int cardType = AccessibilityFieldFocus::CardType::MONSTER;
		bool CheckIfCanViewCards(irr::SEvent event);
		void DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text);
		void DisplayCardsReverse(const std::vector<ClientCard*>& field, const std::wstring& text);
		void SelectCard(const std::vector<ClientCard*>& field, const std::wstring& text);
		void DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text);
		void CloseDialog();
		bool UseCard(const AccessibilityFieldFocus::UseType& useType, irr::SEvent event, ClientCard* card = mainGame->dField.clicked_card);
		void SetLookUpField();
		void ShowSelectCard();
		void ShowMenu(int flag, int x, int y);
		void MouseClick(const irr::SEvent& event, bool rightClick = false);
		void CancelOrFinish();
		void ChangeFieldAndLook(bool click = false);
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
		void SelectFieldSlot(int slot, const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER);
		void ChangeFieldByCard();
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
		std::wstring GetCardLocationName(ClientCard* card);
		bool CheckAttributeSelector();
		bool CheckTypeSelector();
		void AnnounceNumber();
		void AnnounceCard();
		void AttributeSelector(bool up);
		void RaceSelector(bool up);
		void SpecialSummon(const irr::SEvent& event);
		void CheckFreeSlots(const AccessibilityFieldFocus::DisplayedField& player = AccessibilityFieldFocus::DisplayedField::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE, bool link = false);
		void ReplayCommands(const irr::SEvent& event);
		void ReadCardInfo();
		void RotateField();
		void SetCard(const irr::SEvent& event);
		void PlayerInformation();
		void ConfirmCard(const irr::SEvent& event);
		void ConfirmOnFieldCard(const irr::SEvent& event);
		void SeeTurn();
		void SelectableCards(const irr::SEvent& event);
		void ChangeBattlePosition(const irr::SEvent& event);
		void DisplayTable(const irr::SEvent& event, AccessibilityFieldFocus::FieldLookerLocId fieldLooker,
		                  AccessibilityFieldFocus::DisplayedField displayedField);
		void ChangeBattlePhase(AccessibilityFieldFocus::BattleStep bp);
		void SelectOption(int i);
		void NumberKeyEvents(const irr::SEvent& event);
		void DuelCommands(const irr::SEvent& event);
		void MenuCommands(const irr::SEvent& event);
		void FocusOnMenus();
		void MovementCommands(const irr::SEvent& event);
		/*
		void SimulateButton(irr::gui::IGUIElement* caller = nullptr);
		void SetMouseOnCard();
		void TriggerOkButton();
		*/
	};
}

#endif
