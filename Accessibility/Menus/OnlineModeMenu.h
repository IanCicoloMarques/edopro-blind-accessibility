#ifndef ONLINE_MODE_MENU_HANDLER_H
#define ONLINE_MODE_MENU_HANDLER_H

#include <vector>
#include "MenuType.h"

#include "BaseMenu.h"

namespace ygo {
	class OnlineModeMenuHandler final : public BaseMenu {
	public:
		static std::vector<int> onlineModeMenu;
		OnlineModeMenuHandler(int activeMenu = MenuType::MenuList::ONLINE_MODE_MENU, const std::vector<int>& selectedMenu = onlineModeMenu);
		static BaseMenu* GetMenu();
		static bool IsActive();
		void KeyInputEvent(const irr::SEvent& event) override;
		void GuiEvent(const irr::SEvent& event) override;
	private:
		void ReadMenuAndValue() override;

		/**
		 * \brief Reads, using text-to-speech, the current room name and player for an online match
		 */
		void ReadOnlineRoomFromList(irr::EKEY_CODE key);

		static OnlineModeMenuHandler* _menuHandler;
		int _onlineMatchIndex = 0;
	};
}

#endif //ONLINE_MODE_MENU_HANDLER_H
