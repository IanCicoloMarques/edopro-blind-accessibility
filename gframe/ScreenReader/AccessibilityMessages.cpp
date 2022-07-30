#include "AccessibilityMessages.h"

std::wstring AccessibilityMessages::getCommandNotAvaliableMessage(std::wstring command)
{
	return L"This card cannot use the command " + command + L" right now";
}
