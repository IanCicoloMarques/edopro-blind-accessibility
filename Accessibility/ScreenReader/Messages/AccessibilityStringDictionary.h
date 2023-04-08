#pragma once

namespace Accessibility {
	/** A identifier to tell what message the accessibility reader will read*/
	struct Dict
	{
		enum Menu
		{
			WELCOME = 0,
			YES = 102,
			NO = 106,
			LEAVE_GAME = 119,
		};
		enum Duel
		{
			FIRST_TURN = 103,
			ATTACK_UP = 104,
			ATTACK_DOWN = 105,
			SECOND_TURN = 107,
			DEFENSE_UP = 108,
			DEFENSE_DOWN = 109,
			FREE_SLOTS = 376
		};
		enum CardUses
		{
			SUMMON = 370,
			SET = 371,
			SPECIAL_SUMMON = 372,
			ACTIVATE = 373,
			ATTACK = 374,
			CHANGE_MODE = 375,
		};
	};
}
