#include "FieldSlotController.h"

#include "FieldFocus/AccessibilityFieldFocus.h"


namespace ygo {
	FieldSlotModel* FieldSlotController::GetFieldSlotData(const int& slot, const int& field)
	{
		auto* fieldSlot = new FieldSlotModel();
		if (field == AccessibilityFieldFocus::FieldLookerLocId::LINK_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::FieldLookerLocId::LINK_ZONE;
			fieldSlot->xPosition = GetLinkFieldXPosition(slot);
			fieldSlot->yPosition = _linkYPosition;
			fieldSlot->slotNumber = slot;
		}
		else if (field == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS)
		{
			fieldSlot->field = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_MONSTERS;
			fieldSlot->xPosition = GetPlayerFieldXPosition(slot);
			fieldSlot->yPosition = _monsterFieldYPosition;
			fieldSlot->slotNumber = slot;
		}
		else if (field == AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS)
		{
			fieldSlot->field = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_SPELLS;
			fieldSlot->xPosition = GetPlayerFieldXPosition(slot);
			fieldSlot->yPosition = _spellFieldYPosition;
			fieldSlot->slotNumber = slot;
		}
		return nullptr;
	}

	double FieldSlotController::GetLinkFieldXPosition(int slot)
	{
		double posX;
		switch (slot)
		{
		case 6:
		case 1: {
				posX = 0.40 + (2 * FieldSlotModel::slotSize);
				break;
		}
		case 2:
		case 7:
		{
				posX = 0.40 + (4 * FieldSlotModel::slotSize);
				break;
		}
		default:
			posX = 0.60;
			break;
		}
		return posX;
	}

	double FieldSlotController::GetPlayerFieldXPosition(const int slot)
	{
		constexpr double startPosition = 0.40;
		double posX = posX = startPosition + (slot * FieldSlotModel::slotSize);
		return posX;
	}
}
