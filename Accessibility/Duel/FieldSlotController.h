#ifndef FIELD_SLOT_CONTROLLER_H
#define FIELD_SLOT_CONTROLLER_H

#include "Models/FieldSlotModel.h"


namespace ygo {
	class FieldSlotController{
	public:
		static FieldSlotController* GetInstance();
		FieldSlotModel* GetFieldSlotData(const int& slot, const int& field);
	private:
		static FieldSlotController* _fieldSlotController;
		const double _linkYPosition = 0.515;
		const double _monsterFieldYPosition = 0.64;
		const double _spellFieldYPosition = 0.72;
		double GetLinkFieldXPosition(int slot);
		double GetPlayerFieldXPosition(int slot);
	};
}

#endif //FIELD_SLOT_CONTROLLER_H
