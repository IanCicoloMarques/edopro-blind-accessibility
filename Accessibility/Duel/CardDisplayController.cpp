#include "CardDisplayController.h"

#include "../gframe/game.h"
#include <IGUIWindow.h>
#include "Helper/ButtonHelper.h"


namespace ygo {
	void CardDisplayController::CloseDisplay()
	{
		if (mainGame->wCardDisplay->isVisible())
			ButtonHelper::ClickButton(mainGame->btnDisplayOK);
	}
}
