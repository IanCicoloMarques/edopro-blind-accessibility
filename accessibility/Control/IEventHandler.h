#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include "../../irrlicht/include/Keycodes.h"
#include "../../irrlicht/include/IEventReceiver.h"
class IEventHandler
{
	public:
		virtual void PushKey(const irr::SEvent& event) = 0;
};

#endif
