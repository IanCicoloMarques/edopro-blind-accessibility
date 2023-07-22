#ifndef DUEL_MENU_CONTROLLER_H
#define DUEL_MENU_CONTROLLER_H

#include "Control/IEventHandler.h"
#include "FieldFocus/AccessibilityFieldFocus.h"

namespace ygo {
	class DuelMenuController : IEventHandler{
	public:
		static IEventHandler* GetInstance();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;

	private:
		static IEventHandler* _duelMenuController;
		bool IsRockPaperScissorsAvailable();
		void RockPaperScissors(irr::EKEY_CODE key);
		void SelectOption(int i);
		void SetResponseSelectedOption() const;
		void ChangeBattlePhase(AccessibilityFieldFocus::BattleStep bp);
		void AnnounceNumber();
		void AnnounceCard();
		bool CheckAttributeSelector();
		void RaceSelector(bool up);
		bool CheckTypeSelector();
		void AttributeSelector(bool up);
		void FocusOnMenus();
		AccessibilityFieldFocus::BattleStep _battleStep = AccessibilityFieldFocus::BattleStep::MP1;
		const int _selectAttributeMax = 7;
		const int _selectTypeMax = 25;
		int _selectAttribute = 0;
		int _selectType = 0;
	};
}

#endif //DUEL_MENU_CONTROLLER_H
