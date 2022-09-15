#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include "../../irrlicht/include/Keycodes.h"
#include "../../irrlicht/include/IEventReceiver.h"
class IEventHandler
{
	public:
		virtual void KeyInputEvent(const irr::SEvent& event) = 0;
		virtual void GuiEvent(const irr::SEvent& event) = 0;
};

#endif
