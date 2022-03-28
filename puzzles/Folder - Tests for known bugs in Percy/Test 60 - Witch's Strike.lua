Debug.SetAIName("YuGiOh")
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_TEST_MODE,4)

Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
In the chain in which your card's/effect's activation was negated (fulfilling the condition for Witch's Strike), the Chain Link 1 effect Normal Summons a monster (in this test puzzle, it's the effect of Yosenju Kama 1).
The activation timing for Witch's Strike is in the summon negation window and not in the summon response window (EVENT_SUMMON, not EVENT_SUMMON_SUCCESS), and as a result the monster that was summoned is not considered to be on the field yet and so is not destroyed.
You can see that the Spell does not gain any counters and you cannot activate Torrential Tribute (because it's too early). 
]]
EvHERO=Debug.AddCard(27918963,0,0,LOCATION_SZONE,2,POS_FACEUP)
Debug.PreAddCounter(EvHERO, 0x33,2)

Debug.AddCard(54903668,0,0,LOCATION_SZONE,1,POS_FACEDOWN)
Debug.AddCard(53582587,0,0,LOCATION_SZONE,3,POS_FACEDOWN)

Debug.AddCard(92246806,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(65247798,0,0,LOCATION_HAND,0,POS_FACEDOWN)

Debug.AddCard(15693423,1,1,LOCATION_SZONE,0,POS_FACEDOWN)
Debug.AddCard(68688135,1,1,LOCATION_SZONE,1,POS_FACEDOWN)
Debug.AddCard(36458063,1,1,LOCATION_SZONE,2,POS_FACEDOWN)

Debug.AddCard(77044671,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK)
Debug.AddCard(70645913,1,1,LOCATION_MZONE,4,POS_FACEUP_ATTACK)

Debug.ReloadFieldEnd()
aux.BeginPuzzle()