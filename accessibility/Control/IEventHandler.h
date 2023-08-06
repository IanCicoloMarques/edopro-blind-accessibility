#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include "../../irrlicht/include/IEventReceiver.h"
/**
 * \brief Interface used to control the game events, like key presses, mouse clicks, etc.
 */
class IEventHandler
{
	public:
	/**
	 * \brief Control the events of the game when the user presses a key.
	 * \param event Data Type that contains the information of the key pressed.
	 */
	virtual void KeyInputEvent(const irr::SEvent& event) = 0;
	/**
	 * \brief Control the events of the game when a grafic element is clicked or changes.
	 * \param event Data Type that contains the information of the element.
	 */
	virtual void GuiEvent(const irr::SEvent& event) = 0;
};

#endif
