#ifndef DUEL_CONTROLLER_H
#define DUEL_CONTROLLER_H

#include "../Control/IEventHandler.h"
#include "../gframe/client_card.h"
#include "FieldFocus/AccessibilityFieldFocus.h"
#include "Models/UseCardModel.h"

namespace ygo {
	class DuelController : IEventHandler{
	public:
		static IEventHandler* GetInstance();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		void Command(AccessibilityFieldFocus::UseType useType, const irr::SEvent& event, ClientCard* card);
		void DuelCommands(const irr::SEvent& event, ClientCard* card);

		static IEventHandler* _duelController;
		//Duel commands
		void NormalSummon(UseCardModel* useCardModel);
		void SetCard(UseCardModel* useCardModel);
		void SpecialSummon(UseCardModel* useCardModel, const ClientCard* card);
		void ActivateCardEffect(UseCardModel* useCardModel);
		void Attack(UseCardModel* useCardModel, const irr::SEvent& event);
		void ChangeBattlePosition(UseCardModel* useCardModel);
		void SelectCard(ClientCard* card, const irr::SEvent& event);
	};
}

#endif //DUEL_CONTROLLER_H
