#ifndef ACCESSIBILITY_FIELD_FOCUS_H
#define ACCESSIBILITY_FIELD_FOCUS_H
#include <vector>

namespace ygo {
	class AccessibilityFieldFocus
	{
	private:
	public:
		static bool IsInMainTable(int location) {
			std::vector<int> mainTable = { MONSTER_ZONE, SPELL_ZONE, LINK_ZONE };
			return std::find(mainTable.begin(), mainTable.end(), location) != mainTable.end();
		}
		/** A identifier to tell where the accessibility reader will look at in the field*/
		enum Field
		{
			UNKNOWN_ZONE = -1,
			HAND_ZONE = 0,
			DECK_ZONE = 1,
			MONSTER_ZONE = 4,
			SPELL_ZONE = 8,
			GRAVEYARD_ZONE = 16,
			REMOVED_CARDS_ZONE = 32,
			EXTRA_DECK_ZONE = 64,
			PLAYER_FIELD = 6,
			PLAYER_PENDULUM_ZONE = 7,
			PLAYER_SUMMONABLE_MONSTERS = 8,
			PLAYER_SPECIAL_SUMMONABLE_MONSTERS = 9,
			PLAYER_ACTIVABLE_CARDS = 10,
			PLAYER_SETTABLE_CARDS = 11,
			PLAYER_SPELL_FIELD = 999,
			ATTACKABLE_CARDS = 12,
			SELECTABLE_CARDS = 13,
			SELECTED_CARDS = 14,
			MUST_SELECT_CARDS = 15,
			LINK_ZONE = 25,
			CHAINED_CARDS = 26
		};

		enum Player
		{
			MAIN_PLAYER = 0,
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
			ATTACK = 6,
			EFFECT = 7,
			SELECT_CARD = 8,
			MONSTER_ATTACK_SELECT = 9,
			ACTIVATE = 10,
			SET_CARD = 11,
			CHANGE_BATTLE_POSITION = 12
		};

		enum CardType
		{
			NO_CARD_TYPE = 0,
			MONSTER = 1,
			SPELL = 76,
			TRAP = 77,
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
