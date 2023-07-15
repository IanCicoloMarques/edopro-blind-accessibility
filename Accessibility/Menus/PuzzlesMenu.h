#ifndef PUZZLES_AND_REPLAYS_MENU_HANDLER_H
#define PUZZLES_AND_REPLAYS_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class PuzzlesMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> puzzlesMenu;
		PuzzlesMenuHandler(int activeMenu = MenuType::MenuList::PUZZLES_MENU, const std::vector<int>& selectedMenu = puzzlesMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;

	private:
		static PuzzlesMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
		void ReadSinglePlayerList();
	};
}

#endif //PUZZLES_AND_REPLAYS_MENU_HANDLER_H
