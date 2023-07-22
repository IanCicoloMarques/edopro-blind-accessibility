#ifndef KEYBOARD_HELPER_H
#define KEYBOARD_HELPER_H

#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include <algorithm>

namespace ygo {
	bool _mudConfiguration;

	class KeyboardHelper{
	public:
		static void SetKeyboardConfiguration()
		{
			if(_mudConfiguration)
				KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Mud);
			else
				KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Default);
		}

		static bool IsNumberKey(irr::EKEY_CODE key)
		{
			constexpr int numberKeys[] = { irr::KEY_KEY_1, irr::KEY_KEY_2, irr::KEY_KEY_3, irr::KEY_KEY_4, irr::KEY_KEY_5, irr::KEY_KEY_6, irr::KEY_KEY_7, irr::KEY_KEY_8, irr::KEY_KEY_9, irr::KEY_KEY_0 };

			if(std::find( std::begin(numberKeys), std::end(numberKeys), key) != std::end(numberKeys))
				return true;
			return false;
		}
	};

	}

#endif //KEYBOARD_HELPER_H
