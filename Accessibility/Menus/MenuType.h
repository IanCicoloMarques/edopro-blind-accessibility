#ifndef MENU_TYPE_H
#define MENU_TYPE_H

#include <vector>
#include <string>

namespace ygo {
	class MenuType {
	public:

		enum MenuList {
			MAIN_MENU,
			SINGLE_PLAYER_MENU,
			HOST_DUEL_MENU,
			DUEL_MENU,
			SELECT_AI_MENU,
			ONLINE_MENU,
			ROOM_PASSWORD_MENU,
			DECK_EDITOR,
			AI_CONFIGURATION, 
		};

		enum MainMenu {
			MM_ONLINE_DUEL,
			MM_SP_DUEL,
			MM_PUZZLES,
			MM_REPLAY,
			MM_DECK_EDITOR,
			MM_GAME_OPTIONS,
			MM_ACCESSILITY_KEYS
		};

		enum HostDuel {
			RULES_OK,
			NUM_PLAYERS_T1,
			NUM_PLAYERS_T2,
			BEST_OF,
			TIME_LIMIT,
			STARTING_LP,
			STARTING_HAND,
			CARDS_DRAW,
			CHECK_DECK,
			SHUFFLE_DECK,
			ROOM_NAME,
			ROOM_PASSWORD,
		};

		enum SinglePlayerMenu {
			SP_HOST,
			SP_PLAYER_NAME
		};

		enum PlayerDuel {
			PD_START_DUEL,
			PD_SELECT_DECK,
			PD_PLAYER_READY
		};

		enum SinglePlayerDuel {
			SP_AI_MENU = 3
		};

		enum AIConfigMenu {
			AIC_OK,
			AIC_SELECT_DECK,
			AIC_ATR
		};

		enum OnlineDuel {
			OD_DUEL_MODE = 3,
			OD_SPECTATE_MODE = 4,
		};

		enum OnlineMenu{
			HOST,
			REFRESH,
			HOST_ONLINE_DUEL,
			SERVER,
			PLAYER_NAME,
			ALLOWED_CARDS,
			FORBIDDEN_LIST,
			LOCKED_ROOMS,
			STARTED_ROOMS,
		};

		enum DeckEditorMenu {
			DE_NEW_DECK
		};

		enum PasswordMenu {
			PASS_SET_PASSWORD,
			PASS_OK,
			PASS_CANCEL
		};

		enum GameOptionsMenu {
			GAMEOP_ENABLE_SOUND_EFFECTS,
			GAMEOP_SOUND_EFFECTS_VOLUME,
			GAMEOP_ENABLE_MUSIC,
			GAMEOP_MUSIC_VOLUME
		};

		enum DeckOptionsMenu {
			DECKOP_SELECT_DECK,
			DECKOP_SEARCH,
			DECKOP_CATEGORY,
			DECKOP_SUB_CATEGORY,
			DECKOP_ATTRIBUTE,
			DECKOP_TYPE,
			DECKOP_LEVEL,
			DECKOP_SCALE,
			DECKOP_LIMIT,
			DECKOP_ATTACK,
			DECKOP_DEFENSE,
			DECKOP_LINK_MARKER,
			DECKOP_EFFECT,
			DECKOP_CLEAR_SEARCH
		};

		enum PuzzlesMenu {
			PUZZLES_START
		};
	};
}

#endif //MENU_TYPE_H
