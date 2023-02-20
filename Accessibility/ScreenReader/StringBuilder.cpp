#include "StringBuilder.h"

std::wstring StringBuilder::builtMessage = std::wstring();

std::wstring StringBuilder::getBuiltMessage()
{
	return builtMessage;
}

void StringBuilder::AddLine(std::wstring string)
{
	builtMessage += string;
	builtMessage += L",\n";
}

void StringBuilder::cleanBuiltMessage()
{
	builtMessage = std::wstring();
}
