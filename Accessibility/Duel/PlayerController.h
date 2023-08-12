#ifndef PLAYER_CONTROLLER_HANDLER_H
#define PLAYER_CONTROLLER_HANDLER_H

#include "Control/IEventHandler.h"
#include "../gframe/client_card.h"
#include "FieldFocus/AccessibilityFieldFocus.h"

namespace ygo {
	class PlayerController : IEventHandler{
	public:
		static IEventHandler* GetInstance();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);
		bool HasEventKey(irr::EKEY_CODE key) override;
		void PlayerInformation();
		void SeeTurn();

	private:
		static IEventHandler* _playerController;
		void StartChat();
	};
}

#endif //PLAYER_CONTROLLER_HANDLER_H
