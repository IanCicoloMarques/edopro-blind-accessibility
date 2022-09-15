#include "EventVariables.h"

namespace ygo {
	int EventVariables::cardSelectPosition = 0;
	int EventVariables::indexLookedUpCard = 0;
	int EventVariables::displayedCards = AccessibilityFieldFocus::DisplayedCards::NO_DISPLAY;
	int EventVariables::battlePhase = AccessibilityFieldFocus::BattleStep::MP1;
	int EventVariables::cardType = AccessibilityFieldFocus::CardType::MONSTER;
	AccessibilityFieldFocus::DisplayedField EventVariables::displayedField = AccessibilityFieldFocus::DisplayedField::PLAYER;
	AccessibilityFieldFocus::FieldLookerLocId EventVariables::lookupFieldLocId = AccessibilityFieldFocus::FieldLookerLocId::PLAYER_HAND;
}
