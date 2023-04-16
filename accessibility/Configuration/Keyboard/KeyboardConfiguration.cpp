#include "KeyboardConfiguration.h"
#include "../../../irrlicht/include/Keycodes.h"

void KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType type)
{
	if(type == KeyboardConfigurationType::Default)
	{
		LoadDefaultConfiguration();
	}
}

void KeyboardConfiguration::LoadDefaultConfiguration()
{
	NormalSummon = irr::KEY_KEY_A;
	SetSummon = irr::KEY_KEY_S;
}

void KeyboardConfiguration::LoadMudConfiguration()
{
}
