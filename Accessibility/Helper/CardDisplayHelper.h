#ifndef CARD_DISPLAY_HELPER_H
#define CARD_DISPLAY_HELPER_H

#include "../gframe/game.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include <IGUIScrollBar.h>

class CardDisplayHelper
{
public:
	static void ScrollCardDisplay()
	{
		if (ygo::mainGame->btnCardSelect[0]->isTrulyVisible()) {
			irr::SEvent newEvent{};
			newEvent.EventType = irr::EEVENT_TYPE::EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = ygo::mainGame->scrCardList;
			newEvent.GUIEvent.Element = nullptr;
			newEvent.GUIEvent.EventType = irr::gui::EGUI_EVENT_TYPE::EGET_SCROLL_BAR_CHANGED;
			ygo::mainGame->scrCardList->OnEvent(newEvent);
		}
	}
};

#endif //CARD_DISPLAY_HELPER_H
