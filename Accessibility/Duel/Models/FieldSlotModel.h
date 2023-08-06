#ifndef FIELD_SLOT_MODEL_H
#define FIELD_SLOT_MODEL_H


namespace ygo {
	class FieldSlotModel{
	public:
		FieldSlotModel()
		{
			xPosition = 0;
			yPosition = 0;
			slotNumber = 1;
			field = 0;
		}
		static double slotSize;
		double xPosition;
		double yPosition;
		int slotNumber;
		int field;
	};
}

#endif //FIELD_SLOT_MODEL_H
