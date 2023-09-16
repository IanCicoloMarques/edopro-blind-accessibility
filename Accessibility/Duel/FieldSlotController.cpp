#include "FieldSlotController.h"

#include "FieldController.h"
#include "FieldFocus/AccessibilityFieldFocus.h"


namespace ygo {
	FieldSlotController* FieldSlotController::_fieldSlotController = nullptr;
	FieldSlotController* FieldSlotController::GetInstance()
	{
		if (_fieldSlotController == nullptr)
			_fieldSlotController = new FieldSlotController();
		return _fieldSlotController;
	}

	FieldSlotModel* FieldSlotController::GetFieldSlotData(const int& slot, AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player)
	{
		auto* fieldSlot = new FieldSlotModel();
		if (field == AccessibilityFieldFocus::Field::LINK_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::LINK_ZONE;
			fieldSlot->xPosition = GetLinkFieldXPosition(slot);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::LINK_ZONE);
			fieldSlot->slotNumber = slot;
		}
		else if (field == AccessibilityFieldFocus::Field::MONSTER_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::MONSTER_ZONE;
			fieldSlot->xPosition = GetPlayerFieldXPosition(slot);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::MONSTER_ZONE, player);
			fieldSlot->slotNumber = slot;
		}
		else if (field == AccessibilityFieldFocus::Field::SPELL_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::SPELL_ZONE;
			fieldSlot->xPosition = GetPlayerFieldXPosition(slot);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::SPELL_ZONE, player);
			fieldSlot->slotNumber = slot;
		}
		else if (field == AccessibilityFieldFocus::Field::DECK_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::DECK_ZONE;
			fieldSlot->xPosition = GetXPosition(AccessibilityFieldFocus::Field::DECK_ZONE, player);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::DECK_ZONE, player);
		}
		else if (field == AccessibilityFieldFocus::Field::GRAVEYARD_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::GRAVEYARD_ZONE;
			fieldSlot->xPosition = GetXPosition(AccessibilityFieldFocus::Field::GRAVEYARD_ZONE, player);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::GRAVEYARD_ZONE, player);
		}
		else if (field == AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE;
			fieldSlot->xPosition = GetXPosition(AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE, player);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::REMOVED_CARDS_ZONE, player);
		}
		else if (field == AccessibilityFieldFocus::Field::FIELD_SPELL)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::FIELD_SPELL;
			fieldSlot->xPosition = GetXPosition(AccessibilityFieldFocus::Field::FIELD_SPELL, player);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::FIELD_SPELL, player);
		}
		else if (field == AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE)
		{
			fieldSlot->field = AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE;
			fieldSlot->xPosition = GetXPosition(AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE, player);
			fieldSlot->yPosition = GetYPosition(AccessibilityFieldFocus::Field::EXTRA_DECK_ZONE, player);
		}
		return fieldSlot;
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

	double FieldSlotController::GetXPosition(const AccessibilityFieldFocus::Field field, const AccessibilityFieldFocus::Player player)
	{
		constexpr double leftSlotX = 0.43;
		constexpr double rightSlotX = 0.88;
		double xPosition = 0;
		switch (field) {
			case AccessibilityFieldFocus::DECK_ZONE:
			case AccessibilityFieldFocus::GRAVEYARD_ZONE:
			case AccessibilityFieldFocus::REMOVED_CARDS_ZONE:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					xPosition =  rightSlotX;
				else
					xPosition = leftSlotX;
			break;
			case AccessibilityFieldFocus::EXTRA_DECK_ZONE:
			case AccessibilityFieldFocus::FIELD_SPELL:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					xPosition = leftSlotX;
				else
					xPosition = rightSlotX;
			break;
		}
		return xPosition;
	}

	double FieldSlotController::GetYPosition(AccessibilityFieldFocus::Field field, AccessibilityFieldFocus::Player player)
	{
		double yPosition = 0;
		switch (field) {
			case AccessibilityFieldFocus::MONSTER_ZONE:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					yPosition = _monsterFieldYPositionMainPlayer;
				else
					yPosition = 0.30;
			break;
			case AccessibilityFieldFocus::DECK_ZONE:
			case AccessibilityFieldFocus::EXTRA_DECK_ZONE:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					yPosition = 0.83;
				else
					yPosition = 0.30;
				break;
			case AccessibilityFieldFocus::SPELL_ZONE:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					yPosition = _spellFieldYPositionMainPlayer;
				else
					yPosition = 0.39;
			break;
			case AccessibilityFieldFocus::GRAVEYARD_ZONE:
			case AccessibilityFieldFocus::FIELD_SPELL:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					yPosition = 0.70;
				else
					yPosition = 0.39;
				break;
			case AccessibilityFieldFocus::REMOVED_CARDS_ZONE:
				if(player == AccessibilityFieldFocus::Player::MAIN_PLAYER)
					yPosition = 0.56;
				else
					yPosition = 0.43;
			break;
			case AccessibilityFieldFocus::LINK_ZONE:
				yPosition = _linkYPosition;
			break;
		}
		return yPosition;
	}
}
