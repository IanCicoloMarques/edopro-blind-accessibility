#ifndef MENU_TYPE_H
#define MENU_TYPE_H

#include <vector>
#include <string>

namespace ygo {
	class MenuType {
	public:
		//static std::vector<std::wstring> menu;
		//static std::vector<std::wstring> menuMain;// = { L"Online Duel", L"Duel", L"Deck Editor" };
		//static std::vector<std::wstring> menuSinglePlayer;// = { L"Host Duel", L"Player Name" };
		//	static std::vector<std::wstring> menuHostDuel;// = { L"Rules ok", L"Best of", L"Time Limit", L"Starting LP", L"Starting Hand", L"Cards per Draw", L"Don't check deck", L"Don't shuffle deck", L"Room Name", L"Room Password" };
		//	static std::vector<std::wstring> menuRulesOk;// = { L"Start Duel", L"Select Deck", L"Player Ready", L"Select AI" };
		//	static std::vector<std::wstring> menuRulesOkOnline;// = { L"Start Duel", L"Select Deck", L"Player Ready", L"Enter Duel mode", L"Enter Spectate mode" };
		//static std::vector<std::wstring> menuSelectAI;// = { L"AI Ok", L"Select Deck", L"Always throw Rock" };
		//static std::vector<std::wstring> menuOnline;// = { L"Host", L"Refresh", L"Rooms", L"Server", L"Player Name", L"Allowed Cards", L"Forbidden List", L"Show Locked Rooms", L"Show Started Rooms" };
		//static std::vector<std::wstring> menuPassword;// = { L"OK", L"Cancel" };
		//static std::wstring currentMenu;// = L"Online Duel";
		//static std::wstring oldMenu;// = L"Online Duel";
		//static int menuSelectCounter;// = 0;
		//static int subMenuSelectCounter;// = 0;
		//static int onlineMatchCounter;// = 0;

		enum MenuList {
			MAIN_MENU,
			SINGLE_PLAYER_MENU,
			HOST_DUEL_MENU,
			DUEL_MENU,
			SELECT_AI_MENU,
			ONLINE_MENU,
			ROOM_PASSWORD_MENU,
			DECK_EDITOR,
			AI_CONFIGURATION
		};

		enum MainMenu {
			MM_ONLINE_DUEL,
			MM_SP_DUEL,
			MM_DECK_EDITOR
		};

		enum HostDuel {
			RULES_OK = 0,
			BEST_OF = 1,
			TIME_LIMIT = 2,
			STARTING_LP = 3,
			STARTING_HAND = 4,
			CARDS_DRAW = 5,
			CHECK_DECK = 6,
			SHUFFLE_DECK = 7,
			ROOM_NAME = 8,
			ROOM_PASSWORD = 9,
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
	};
}
//static std::vector<std::wstring> menuMain = { L"Online Duel", L"Duel", L"Deck Editor" };
//static std::vector<std::wstring> menuSinglePlayer = { L"Host Duel", L"Player Name" };
//static std::vector<std::wstring> menuHostDuel = { L"Rules ok", L"Best of", L"Time Limit", L"Starting LP", L"Starting Hand", L"Cards per Draw", L"Don't check deck", L"Don't shuffle deck", L"Room Name", L"Room Password" };
//static std::vector<std::wstring> menuRulesOk = { L"Start Duel", L"Select Deck", L"Player Ready", L"Select AI" };
//static std::vector<std::wstring> menuRulesOkOnline = { L"Start Duel", L"Select Deck", L"Player Ready", L"Enter Duel mode", L"Enter Spectate mode" };
//static std::vector<std::wstring> menuSelectAI = { L"AI Ok", L"Select Deck", L"Always throw Rock" };
//static std::vector<std::wstring> menuOnline = { L"Host", L"Refresh", L"Rooms", L"Server", L"Player Name", L"Allowed Cards", L"Forbidden List", L"Show Locked Rooms", L"Show Started Rooms" };
//static std::vector<std::wstring> menuPassword = { L"OK", L"Cancel" };
//static std::wstring currentMenu = L"Online Duel";
//static std::wstring oldMenu = L"Online Duel";
//static int menuSelectCounter = 0;
//static int subMenuSelectCounter = 0;
//static int onlineMatchCounter = 0;

#endif //MENU_TYPE_H
