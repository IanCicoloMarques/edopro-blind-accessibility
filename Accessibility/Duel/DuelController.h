#ifndef DUEL_CONTROLLER_H
#define DUEL_CONTROLLER_H

#include "IEventReceiver.h"
#include "Control/IEventHandler.h"
#include "FieldFocus/AccessibilityFieldFocus.h"
#include "../gframe/client_card.h"
#include "Models/UseCardModel.h"

namespace ygo {
	class DuelController : IEventHandler{
	public:
		static IEventHandler* GetDuelController();
		void KeyInputEvent(const irr::SEvent& event);
		void GuiEvent(const irr::SEvent& event);
	private:
		void Command(AccessibilityFieldFocus::UseType useType, const irr::SEvent& event, ClientCard* card);
		void DuelCommands(const irr::SEvent& event, ClientCard* card);

		static IEventHandler* _duelController;
		static int _battlePhase;

		//Duel commands
		void NormalSummon(UseCardModel* useCardModel);
		void SetCard(UseCardModel* useCardModel);
		void SpecialSummon(UseCardModel* useCardModel, const ClientCard* card);
		void ActivateCardEffect(UseCardModel* useCardModel);
	};
}

#endif //DUEL_CONTROLLER_H
