#ifndef EVENTVARIABLES_H
#define EVENTVARIABLES_H

#include "../ScreenReader/StringBuilder.cpp"
#include "../ScreenReader/ScreenReader.cpp"
#include "../FieldFocus/AccessibilityFieldFocus.h"

namespace ygo {
	class EventVariables
	{
	public:
		static bool selectZone;
		static int cardSelectPosition;
		static int indexLookedUpCard;
		static int displayedCards;
		static int battlePhase;
		static int cardType;
		static AccessibilityFieldFocus::FieldLookerLocId lookupFieldLocId;
		static AccessibilityFieldFocus::DisplayedField displayedField;
	};
}

#endif
