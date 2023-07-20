#ifndef KEYBOARD_HELPER_H
#define KEYBOARD_HELPER_H

#include "Configuration/Keyboard/KeyboardConfiguration.h"


namespace ygo {
	bool _mudConfiguration;

	class KeyboardHelper{
	public:
		static int numberKeys[];
		static void SetKeyboardConfiguration()
		{
			if(_mudConfiguration)
				KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Mud);
			else
				KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType::Default);
		}
	};

	int KeyboardHelper::numberKeys[] = { irr::KEY_KEY_1, irr::KEY_KEY_2, irr::KEY_KEY_3, irr::KEY_KEY_4, irr::KEY_KEY_5, irr::KEY_KEY_6, irr::KEY_KEY_7, irr::KEY_KEY_8, irr::KEY_KEY_9, irr::KEY_KEY_0 };
}

#endif //KEYBOARD_HELPER_H
