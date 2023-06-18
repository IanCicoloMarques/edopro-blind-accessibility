#include "ButtonHelper.h"

#include "IGUIButton.h"
#include "IrrlichtDevice.h"

static inline void TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
	irr::SEvent event{};
	event.EventType = irr::EET_GUI_EVENT;
	event.GUIEvent.EventType = type;
	event.GUIEvent.Caller = target;
	event.GUIEvent.Caller->setVisible(true);
	ygo::mainGame->fadingList.clear();
	ygo::mainGame->device->postEventFromUser(event);
}

void ygo::ButtonHelper::ClickButton(irr::gui::IGUIButton* button)
{
	if (button->isTrulyVisible())
	{
		TriggerEvent(button, irr::gui::EGET_BUTTON_CLICKED);
	}
}
