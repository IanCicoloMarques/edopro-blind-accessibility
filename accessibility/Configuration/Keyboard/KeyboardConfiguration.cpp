#include "KeyboardConfiguration.h"
namespace ygo
{
	int KeyboardConfiguration::NormalSummon = irr::KEY_KEY_A;
	int KeyboardConfiguration::SetSummon = irr::KEY_KEY_S;
	int KeyboardConfiguration::SpecialSummon = irr::KEY_KEY_D;
	int KeyboardConfiguration::CardInformation = irr::KEY_KEY_I;
	int KeyboardConfiguration::ExtraDeck = irr::KEY_KEY_R;
	int KeyboardConfiguration::Chat = irr::KEY_KEY_M;
	int KeyboardConfiguration::Graveyard = irr::KEY_KEY_T;
	int KeyboardConfiguration::Hand = irr::KEY_KEY_Q;
	int KeyboardConfiguration::RemovedZone = irr::KEY_KEY_Y;
	int KeyboardConfiguration::MonsterZone = irr::KEY_KEY_W;
	int KeyboardConfiguration::SpellZone = irr::KEY_KEY_E;
	int KeyboardConfiguration::RotateField = irr::KEY_KEY_V;
	int KeyboardConfiguration::Attack = irr::KEY_KEY_A;
	int KeyboardConfiguration::BattlePhase = irr::KEY_BACK;
	int KeyboardConfiguration::MainPhase2 = irr::KEY_BACK;
	int KeyboardConfiguration::EndTurn = irr::KEY_BACK;
	int KeyboardConfiguration::ActivateCard = irr::KEY_KEY_F;

	int KeyboardConfiguration::PlayerInformation = irr::KEY_KEY_L;
	int KeyboardConfiguration::SelectCard = irr::KEY_RETURN;
	int KeyboardConfiguration::ConfirmCard = irr::KEY_KEY_P;
	int KeyboardConfiguration::Help = irr::KEY_KEY_H;
	int KeyboardConfiguration::SeeTurn = irr::KEY_KEY_J;
	int KeyboardConfiguration::Chain = irr::KEY_KEY_N;
	int KeyboardConfiguration::SelectableCards = irr::KEY_KEY_Z;
	int KeyboardConfiguration::SpecialSummonableCards = irr::KEY_KEY_X;
	int KeyboardConfiguration::ActivatableCards = irr::KEY_KEY_C;
	int KeyboardConfiguration::ChangeBattlePosition = irr::KEY_KEY_G;
	int KeyboardConfiguration::Deck = irr::KEY_KEY_U;

	//Menu Keys
	int KeyboardConfiguration::MenuButtonYes = irr::KEY_COMMA;
	int KeyboardConfiguration::MenuButtonNo = irr::KEY_PERIOD;
	int KeyboardConfiguration::MenuButtonFirstTurn = irr::KEY_PERIOD;;
	int KeyboardConfiguration::MenuButtonSecondTurn = irr::KEY_PERIOD;;
	int KeyboardConfiguration::MenuButtonAttackUp = irr::KEY_PERIOD;;
	int KeyboardConfiguration::MenuButtonAttackDown = irr::KEY_PERIOD;;
	int KeyboardConfiguration::MenuButtonDefenseUp = irr::KEY_PERIOD;;
	int KeyboardConfiguration::MenuButtonDefenseDown = irr::KEY_PERIOD;;

	//Mouse
	int KeyboardConfiguration::MouseRightClick = irr::KEY_PERIOD;;

	void KeyboardConfiguration::LoadConfiguration(KeyboardConfigurationType::ConfigurationType type)
	{
		if(type == KeyboardConfigurationType::Default)
			LoadDefaultConfiguration();
		else if(type == KeyboardConfigurationType::Mud)
			LoadMudConfiguration();
	}

	void KeyboardConfiguration::LoadDefaultConfiguration()
	{
		NormalSummon = irr::KEY_KEY_A;
		SetSummon = irr::KEY_KEY_S;
		SpecialSummon = irr::KEY_KEY_D;
		CardInformation = irr::KEY_KEY_I;
		ExtraDeck = irr::KEY_KEY_R;
		Chat = irr::KEY_KEY_M;
		Graveyard = irr::KEY_KEY_T;
		Hand = irr::KEY_KEY_Q;
		RemovedZone = irr::KEY_KEY_Y;
		MonsterZone = irr::KEY_KEY_W;
		SpellZone = irr::KEY_KEY_E;
		RotateField = irr::KEY_KEY_V;
		Attack = irr::KEY_KEY_A;
		BattlePhase = irr::KEY_BACK;
		MainPhase2 = irr::KEY_BACK;
		EndTurn = irr::KEY_BACK;
		ActivateCard = irr::KEY_KEY_F;
		PlayerInformation = irr::KEY_KEY_L;
		SelectCard = irr::KEY_RETURN;
		ConfirmCard = irr::KEY_KEY_P;
		Help = irr::KEY_KEY_H;
		SeeTurn = irr::KEY_KEY_J;
		Chain = irr::KEY_KEY_N;
		SelectableCards = irr::KEY_KEY_Z;
		SpecialSummonableCards = irr::KEY_KEY_X;
		ActivatableCards = irr::KEY_KEY_C;
		ChangeBattlePosition = irr::KEY_KEY_G;
		Deck = irr::KEY_KEY_U;
	}

	void KeyboardConfiguration::LoadMudConfiguration()
	{
		NormalSummon = irr::KEY_KEY_S;
		SetSummon = irr::KEY_KEY_Z;
		SpecialSummon = irr::KEY_KEY_C;
		ChangeBattlePosition = irr::KEY_KEY_J;
		CardInformation = irr::KEY_KEY_I;
		ActivatableCards = irr::KEY_OEM_2;
		ExtraDeck = irr::KEY_KEY_X;
		Chat = irr::KEY_OEM_5;
		Graveyard = irr::KEY_KEY_G;
		Hand = irr::KEY_KEY_H;
		RemovedZone = irr::KEY_KEY_R;
		MonsterZone = irr::KEY_KEY_T;
		RotateField = irr::KEY_KEY_F;
		Attack = irr::KEY_KEY_A;
		BattlePhase = irr::KEY_KEY_B;
		MainPhase2 = irr::KEY_KEY_M;
		EndTurn = irr::KEY_KEY_E;
		ActivateCard = irr::KEY_KEY_V;

		SpellZone = irr::KEY_KEY_T;
		PlayerInformation = irr::KEY_UNKNOWN;
		SelectCard = irr::KEY_RETURN;
		ConfirmCard = irr::KEY_KEY_P;
		Help = irr::KEY_UNKNOWN;
		SeeTurn = irr::KEY_UNKNOWN;
		Chain = irr::KEY_UNKNOWN;
		SelectableCards = irr::KEY_UNKNOWN;
		SpecialSummonableCards = irr::KEY_UNKNOWN;
		Deck = irr::KEY_UNKNOWN;
	}


}
