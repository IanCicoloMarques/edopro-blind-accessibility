#ifndef BASE_MENU_H
#define BASE_MENU_H

#include <vector>
#include <string>
#include "MenuType.h"
#include "../gframe/game.h"
#include "../gframe/game_config.h"
#include "../gframe/server_lobby.h"
#include "../gframe/data_manager.h"
#include "../gframe/sound_manager.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/CGUIFileSelectListBox/CGUIFileSelectListBox.h"
#include "../accessibility/Control/IEventHandler.h"
#include "../accessibility/ScreenReader/StringBuilder.h"
#include "../accessibility/ScreenReader/ScreenReader.h"
#include "../accessibility/ScreenReader/Messages/AccessibilityStringDictionary.h"
#include <IGUIWindow.h>
#include <IGUIEditBox.h>
#include <IGUIComboBox.h>
#include <IGUICheckBox.h>
#include <IGUITable.h>
#include <IGUIScrollBar.h>
#include <IrrlichtDevice.h>
#include <IGUITabControl.h>

namespace ygo {
	class BaseMenu : public IEventHandler {
		static BaseMenu* GetMenu()
		{
			return nullptr;
		}

	public:
		virtual void KeyInputEvent(const irr::SEvent& event);
		virtual void ReadMenu(irr::EKEY_CODE key = irr::EKEY_CODE::KEY_UNKNOWN);
		virtual void ReadReplayList();
		virtual void ReadMenuAndValue();
	};
}

#endif //BASE_MENU_H
