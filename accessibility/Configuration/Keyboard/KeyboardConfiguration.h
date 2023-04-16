#pragma once
#include "KeyboardConfigurationType.h"

class KeyboardConfiguration
{
public:
	static int NormalSummon;
	static int SpecialSummon;
	static int SetSummon;
	static int CardInformation;
	static int ExtraDeck;
	static int Chat;
	static int Graveyard;
	static int Hand;
	static int RemovedZone;
	static int PlayerField;
	static int OpponentField;
	static int RotateField;
	static int Attack;
	static int BattlePhase;
	static int MainPhase2;
	static int EndTurn;
	static int ActivateCard;
	static void LoadConfiguration(KeyboardConfigurationType::ConfigurationType type);
private:
	static void LoadDefaultConfiguration();
	void LoadMudConfiguration();
};
