#pragma once
#include "KeyboardConfigurationType.h"
#include "../../../irrlicht/include/Keycodes.h"

namespace ygo
{
	class KeyboardConfiguration
	{
	public:
		//Duel Keys
		static int NormalSummon;
		static int SetSummon;
		static int SpecialSummon;
		static int CardInformation;
		static int ExtraDeck;
		static int Chat;
		static int Graveyard;
		static int Hand;
		static int RemovedZone;
		static int MonsterZone;
		static int SpellZone;
		static int RotateField;
		static int Attack;
		static int BattlePhase;
		static int MainPhase2;
		static int EndTurn;
		static int ActivateCard;
		static int PlayerInformation;
		static int SelectCard;
		static int ConfirmCard;
		static int Help;
		static int SeeTurn;
		static int Chain;
		static int SelectableCards;
		static int SpecialSummonableCards;
		static int ActivatableCards;
		static int ChangeBattlePosition;
		static int Deck;

		//Menu Keys
		static int MenuButtonYes;
		static int MenuButtonNo;
		static int MenuButtonFirstTurn;
		static int MenuButtonSecondTurn;
		static int MenuButtonAttackUp;
		static int MenuButtonAttackDown;
		static int MenuButtonDefenseUp;
		static int MenuButtonDefenseDown;

		//Mouse
		static int MouseRightClick;

		static void LoadConfiguration(KeyboardConfigurationType::ConfigurationType type);
	private:
		static void LoadDefaultConfiguration();
		static void LoadMudConfiguration();
	};
}
