#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../accessibility/Configuration/AccessibilityConfiguration.h"
#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/Menus/MenuType.h"
#include "../accessibility/FieldFocus/AccessibilityDeckFocus.h"
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

namespace ygo {
	class DeckHandler : public IEventHandler
	{
	public:
		static IEventHandler* getDeckHandler();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
		static IEventHandler* deckHandler;
		static int indexLookedUpCard;
	private:
		bool scrollSelected = false;
		bool typing = false;
		int menuSelectCounter = 0;
		std::vector<std::wstring> menu = { L"Deck", L"Search", L"Category", L"Sub Category", L"Attribute", L"Type", L"Level", L"Scale", L"Limit", L"Attack", L"Defense", L"Link Marker", L"Effect", L"Clear Search" };
		AccessibilityDeckFocus::DeckLookerLocId deckLooker = AccessibilityDeckFocus::DeckLookerLocId::MAIN_DECK;

		void ReadCardName();

		void DeckOptionsMenu();
	};
}

#endif
