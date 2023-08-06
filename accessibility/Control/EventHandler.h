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
		void ActivateCard(const irr::SEvent& event);
		void StartChat();
		void UseCard(AccessibilityFieldFocus::UseType use, const irr::SEvent& event, ClientCard* clientCard = nullptr);
		void UseSelectedCard(const irr::SEvent& event);
		void ChangeLookedUpCardIndex(irr::EKEY_CODE ekey_code);
		void MouseClick(const irr::SEvent& event, bool cond = false);
		void CloseDialog();
		void ChangeLookedUpField(const irr::SEvent& event, AccessibilityFieldFocus::Player displayedField, int messageCode);
		void SelectFieldSlot(int slot, AccessibilityFieldFocus::Player player);
		void SetSlot(const irr::SEvent& event, int slot);
		void MovementCommands(const irr::SEvent& event);
		void KeyInputEvent(const irr::SEvent& event) override;
		bool CheckIfCanViewCards(const irr::SEvent& event);
		void SelectCard(const std::vector<ClientCard*>& vector, const std::basic_string<wchar_t>& format);
		void GuiEvent(const irr::SEvent& event) override;
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
		AccessibilityFieldFocus::Player displayedField = AccessibilityFieldFocus::Player::PLAYER;
		int displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
		int cardType = AccessibilityFieldFocus::CardType::MONSTER;
		void SetLookUpField();
		void CancelOrFinish();
		void DisplayCards(const std::vector<ClientCard*>& vector, const std::basic_string<wchar_t>& format);
		void ChangeFieldAndLook(bool click = false);
		float GetYPosition(const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::PLAYER);
		float GetYPositionPlayer();
		float GetYPositionEnemy();
		float GetYPositionLink();
		float GetXPosition(int slot, const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::PLAYER);
		float GetXPositionPlayer(int slot);
		float GetXPositionEnemy(int slot);
		float GetXPositionLink(int slot);
		void ChangeFieldByCard();
		void ChangeField(const AccessibilityFieldFocus::CardType& cardField);
		int GetFieldSlot(const int& slot, const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::PLAYER, const AccessibilityFieldFocus::CardType& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE);
		void ScrollCardList();
		float GetXPosition(const AccessibilityFieldFocus::Scroll& position = AccessibilityFieldFocus::Scroll::RIGHT);
		void SetSelectableCards();
		void SetResponseSelectedOption() const;
		void EffectResolver(irr::SEvent event);
		void GetCardLocation(ClientCard* card);
		std::wstring GetCardLocationName(ClientCard* card);
		void CheckFreeSlots(const AccessibilityFieldFocus::Player& player = AccessibilityFieldFocus::Player::PLAYER, const int& cardType = AccessibilityFieldFocus::CardType::NO_CARD_TYPE, bool link = false);
		void ReplayCommands(const irr::SEvent& event);
		void RotateField();
		void PlayerInformation();
		void TriggerOk();
		void ConfirmCard(const irr::SEvent& event);
		void ConfirmOnFieldCard(const irr::SEvent& event);
		void SeeTurn();
		void DisplaySelectableCards(const irr::SEvent& event);
		void SelectableCards(const irr::SEvent& event);
		void ChangeBattlePosition(const irr::SEvent& event);
		void SelectOption(int i);
		void DuelCommandsOld(const irr::SEvent& event);
	};
}

#endif
