#ifndef ACCESSIBILITY_DECK_FOCUS_H
#define ACCESSIBILITY_DECK_FOCUS_H

namespace ygo {
	struct AccessibilityDeckFocus
	{
		/** A identifier to tell where the accessibility reader will look at in the field*/
		enum DeckLookerLocId
		{
			MAIN_DECK = 0,
			EXTRA_DECK = 1,
			SIDE_DECK = 2,
			SEARCH = 3,
			MENU = 4,
		};
	};
}

#endif //ACCESSIBILITY_DECK_FOCUS_H
