#ifndef FIELD_SLOT_CONTROLLER_H
#define FIELD_SLOT_CONTROLLER_H

#include "Models/FieldSlotModel.h"
#include "FieldFocus/AccessibilityFieldFocus.h"


namespace ygo {
	class FieldSlotController{
	public:
		static FieldSlotController* GetInstance();
		FieldSlotModel* GetFieldSlotData(const int& slot, AccessibilityFieldFocus::Field field = AccessibilityFieldFocus::Field::MONSTER_ZONE, AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::MAIN_PLAYER);
	private:
		static FieldSlotController* _fieldSlotController;
		const double _linkYPosition = 0.515;
		const double _monsterFieldYPositionMainPlayer = 0.64;
		const double _spellFieldYPositionMainPlayer = 0.77;
		double GetLinkFieldXPosition(int slot);
		double GetPlayerFieldXPosition(int slot, const AccessibilityFieldFocus::Field field = AccessibilityFieldFocus::Field::MONSTER_ZONE);
		double GetXPosition(AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::MAIN_PLAYER);
		double GetYPosition(AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player = AccessibilityFieldFocus::Player::MAIN_PLAYER);
	};
}

#endif //FIELD_SLOT_CONTROLLER_H
