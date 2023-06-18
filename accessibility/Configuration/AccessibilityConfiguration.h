#ifndef ACCESSIBILITYCONFIGURATION_H
#define ACCESSIBILITYCONFIGURATION_H

#include <string>

namespace ygo {
	class AccessibilityConfiguration
	{
	public:
		static bool accessibilityShortcuts;
		static std::wstring GetKeyString(int Key);

	};
}

#endif
