#include "AccessibilityConfiguration.h"
#include "../../../irrlicht/include/Keycodes.h"
namespace ygo {
	bool AccessibilityConfiguration::accessibilityShortcuts = true;

	std::wstring AccessibilityConfiguration::GetKeyString(int Key)
	{
		std::wstring keyString = std::wstring();
		switch (Key) {
		case irr::KEY_KEY_A:
			keyString = L"A";
			break;
		case irr::KEY_KEY_B:
			keyString = L"B";
			break;
		case irr::KEY_KEY_C:
			keyString = L"C";
			break;
		case irr::KEY_KEY_D:
			keyString = L"D";
			break;
		case irr::KEY_KEY_E:
			keyString = L"E";
			break;
		case irr::KEY_KEY_F:
			keyString = L"F";
			break;
		case irr::KEY_KEY_G:
			keyString = L"G";
			break;
		case irr::KEY_KEY_H:
			keyString = L"H";
			break;
		case irr::KEY_KEY_I:
			keyString = L"I";
			break;
		case irr::KEY_KEY_J:
			keyString = L"J";
			break;
		case irr::KEY_KEY_K:
			keyString = L"K";
			break;
		case irr::KEY_KEY_L:
			keyString = L"L";
			break;
		case irr::KEY_KEY_M:
			keyString = L"M";
			break;
		case irr::KEY_KEY_N:
			keyString = L"N";
			break;
		case irr::KEY_KEY_O:
			keyString = L"O";
			break;
		case irr::KEY_KEY_P:
			keyString = L"P";
			break;
		case irr::KEY_KEY_Q:
			keyString = L"Q";
			break;
		case irr::KEY_KEY_R:
			keyString = L"R";
			break;
		case irr::KEY_KEY_S:
			keyString = L"S";
			break;
		case irr::KEY_KEY_T:
			keyString = L"T";
			break;
		case irr::KEY_KEY_U:
			keyString = L"U";
			break;
		case irr::KEY_KEY_V:
			keyString = L"V";
			break;
		case irr::KEY_KEY_W:
			keyString = L"W";
			break;
		case irr::KEY_KEY_X:
			keyString = L"X";
			break;
		case irr::KEY_KEY_Y:
			keyString = L"Y";
			break;
		case irr::KEY_KEY_Z:
			keyString = L"Z";
			break;
		case irr::KEY_KEY_0:
			keyString = L"0";
			break;
		case irr::KEY_KEY_1:
			keyString = L"1";
			break;
		case irr::KEY_KEY_2:
			keyString = L"2";
			break;
		case irr::KEY_KEY_3:
			keyString = L"3";
			break;
		case irr::KEY_KEY_4:
			keyString = L"4";
			break;
		case irr::KEY_KEY_5:
			keyString = L"5";
			break;
		case irr::KEY_KEY_6:
			keyString = L"6";
			break;
		case irr::KEY_KEY_7:
			keyString = L"7";
			break;
		case irr::KEY_KEY_8:
			keyString = L"8";
			break;
		case irr::KEY_KEY_9:
			keyString = L"9";
			break;
		default: ;
		}
		return keyString;
	}
}
