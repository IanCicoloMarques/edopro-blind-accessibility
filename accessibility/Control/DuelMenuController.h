#ifndef ACCESSIBILITYMENUCONTROLLER_H
#define ACCESSIBILITYMENUCONTROLLER_H

#include "../gframe/game.h"
#include "../gframe/data_manager.h"
#include "../gframe/client_card.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/custom_skin_enum.h"
#include "EventVariables.h"
#include <IGUIWindow.h>
#include <IGUIStaticText.h>
#include <IGUIButton.h>
#include <IGUIScrollBar.h>
#include <IrrlichtDevice.h>

namespace ygo {
	class DuelMenuController
	{
	public:
		static void ShowMenu(int flag, int x, int y);
		static void CloseDialog();
		//static void DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text);
		//static void DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text);
		//static void ShowLocationCard();
	};
}
#endif
