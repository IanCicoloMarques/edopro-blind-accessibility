#ifndef USE_CARD_MODEL_H
#define USE_CARD_MODEL_H
#include <string>

#include "ScreenReader/ScreenReader.h"


namespace ygo {
	class UseCardModel{
	public:
		UseCardModel()
		{
			canUse = false;
			command = L"";
		}

		bool canUse;
		std::wstring command;

		void ReadCommand()
		{
			if (!canUse)
				ScreenReader::getReader()->readScreen(AccessibilityMessages::getCommandNotAvaliableMessage(command));
		}
	};
}

#endif //USE_CARD_MODEL_H
