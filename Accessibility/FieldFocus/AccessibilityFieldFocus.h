#ifndef ACCESSIBILITY_FIELD_FOCUS_H
#define ACCESSIBILITY_FIELD_FOCUS_H
#include <vector>

namespace ygo {
	class AccessibilityFieldFocus
	{
	private:
	public:
		static bool IsInMainTable(int location) {
			std::vector<int> mainTable = { PLAYER_MONSTERS, PLAYER_SPELLS, LINK_ZONE };
			return std::find(mainTable.begin(), mainTable.end(), location) != mainTable.end();
		}
		/** A identifier to tell where the accessibility reader will look at in the field*/
		enum FieldLookerLocId
		{
			PLAYER_HAND = 0,
			PLAYER_DECK = 1,
			PLAYER_MONSTERS = 4,
			PLAYER_SPELLS = 8,
			PLAYER_GRAVEYARD = 16,
			PLAYER_BANNED_CARDS = 32,
			PLAYER_EXTRA_DECK = 64,
			PLAYER_FIELD = 6,
			PLAYER_PENDULUM_ZONE = 7,
			PLAYER_SUMMONABLE_MONSTERS = 8,
			PLAYER_SPECIAL_SUMMONABLE_MONSTERS = 9,
			PLAYER_ACTIVABLE_CARDS = 10,
			PLAYER_SETTABLE_CARDS = 11,
			ATTACKABLE_CARDS = 12,
			SELECTABLE_CARDS = 13,
			SELECTED_CARDS = 14,
			MUST_SELECT_CARDS = 15,
			LINK_ZONE = 25,
			CHAINED_CARDS = 26
		};

		enum DisplayedField
		{
			PLAYER = 0,
			ENEMY_PLAYER = 1
		};

		enum DisplayedCards
		{
			NO_DISPLAY = 0,
			DISPLAY_HAND = 1,
			DISPLAY_FIELD = 2

		};

		enum UseType
		{
			NO_USE = 0,
			NORMAL_SUMMON = 1,
			SPECIAL_SUMMON = 2,
			SPECIAL_SUMMON_DEFENSE = 3,
			SET_MONSTER = 4,
			SET_SPELL = 5,
			MONSTER_ATTACK = 6,
			EFFECT = 7,
			SELECT_CARD = 8,
			MONSTER_ATTACK_SELECT = 9,
			ACTIVATE = 10,
			SET_CARD = 11,
			CHANGE_MODE = 12
		};

		enum CardType
		{
			NO_CARD_TYPE = 0,
			MONSTER = 1,
			SPELL = 2,
			ACTIVABLE_EFFECT = 3,
			SELECTABLE = 4,
			LINK = 5,
			GRAVEYARD = 6,
			BANNED = 7,
			DECK = 8,
			CHAIN = 9,
			EXTRA_DECK = 10
		};

		enum BattleStep
		{
			MP1 = 0,
			BP = 1,
			MP2 = 2,
			ED = 3
		};

		enum Scroll
		{
			NO_SCROLL = 0,
			UP = 1,
			DOWN = 2,
			LEFT = 3,
			RIGHT = 4
		};
	};
}

#endif //ACCESSIBILITY_FIELD_FOCUS_H
