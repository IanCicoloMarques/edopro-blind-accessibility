#ifndef ACCESSIBILITY_DECK_FOCUS_H
#define ACCESSIBILITY_DECK_FOCUS_H

namespace ygo {
	struct AccessibilityDeckFocus
	{
		/** A identifier to tell where the accessibility reader will look at in the field*/
		enum CardStack
		{
			MAIN_DECK = 156,
			EXTRA_DECK = 162,
			SIDE_DECK = 151,
			SEARCH = 158
		};

		enum DeckEditorMenu
		{
			SELECTED_SIDE_DECK = 151,
			SELECTED_MAIN_DECK = 156,
		};

		enum DeckEditorMessages
		{
			NO_DECK = 152,
			DECK_NAME = 153,
			ADD_CARD_SIDE_DECK = 154,
			ADD_CARD_MAIN_DECK = 155,
		};

		enum DeckOptionsMenu {
			DEOP_NEW_DECK,
			DEOP_DELETE_DECK,
			DEOP_RENAME_DECK,
			DEOP_SAVE_DECK,
			DEOP_DECK_NAME,
			DEOP_SELECT_DECK
		};

		enum SearchCardMenu {
			SCARD_CATEGORY,
			SCARD_SUB_CATEGORY,
			SCARD_ATTRIBUTE,
			SCARD_TYPE,
			SCARD_LEVEL,
			SCARD_SCALE,
			SCARD_LIMIT,
			SCARD_ATTACK,
			SCARD_DEFENSE,
			SCARD_LINK_MARKER,
			SCARD_EFFECT,
			SCARD_CLEAR_SEARCH,
			SCARD_SEARCH
		};
	};
}

#endif //ACCESSIBILITY_DECK_FOCUS_H
