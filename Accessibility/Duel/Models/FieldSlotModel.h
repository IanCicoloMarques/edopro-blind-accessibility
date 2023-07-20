#ifndef FIELD_SLOT_MODEL_H
#define FIELD_SLOT_MODEL_H


namespace ygo {
	class FieldSlotModel{
	public:
		static double slotSize;
		double xPosition;
		double yPosition;
		int slotNumber;
		int field;
	};
	double FieldSlotModel::slotSize = 0.08;
}

#endif //FIELD_SLOT_MODEL_H
