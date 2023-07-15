#ifndef AI_MENU_HANDLER_H
#define AI_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class AiMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> aiMenu;
		AiMenuHandler(int activeMenu = MenuType::MenuList::SELECT_AI_MENU, const std::vector<int>& selectedMenu = aiMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		static AiMenuHandler* _menuHandler;
		void ReadMenuAndValue() override;
	};
}

#endif //AI_MENU_HANDLER_H
