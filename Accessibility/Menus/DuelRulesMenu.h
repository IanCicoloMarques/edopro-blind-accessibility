#ifndef DUEL_RULES_MENU_HANDLER_H
#define DUEL_RULES_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class DuelRulesMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> duelRulesMenu;
		DuelRulesMenuHandler(int activeMenu = MenuType::MenuList::DUEL_RULES_MENU, const std::vector<int>& selectedMenu = duelRulesMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static DuelRulesMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //DUEL_RULES_MENU_HANDLER_H
