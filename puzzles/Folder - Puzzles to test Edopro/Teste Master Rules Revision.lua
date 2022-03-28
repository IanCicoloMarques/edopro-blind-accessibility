--[[message
To test the master rules changes:

1-Before: “Sangan” is Tributed to activate “Crush Card Virus”, and “D.D. Crow” is activated in a Chain to banish the “Sangan” from the GY. “Sangan” activates its effect after this chain is done resolving. (In this case, “Sangan” is treated as activating its effect in the GY.)
Now:“Sangan” does not activate its effect after the Chain is done resolving.

2-Before: You cannot activate “Rage with Eyes of Blue” during the turn the Normal Summon of your “Maiden with Eyes of Blue” was negated by “Solemn Judgment”.
Now: You can activate “Rage with Eyes of Blue” in the same scenario.

3-Before: If your “Hi-Speedroid Chanbara” Synchro Summon was negated by “Solemn Judgment” during this turn, you cannot try to Synchro Summon “Hi-Speedroid Chanbara” or try to use any other type of card effects to Special Summon it for the rest of the turn.
Now: If your “Hi-Speedroid Chanbara” Synchro Summon was negated by “Solemn Judgment” during this turn, you can Synchro Summon “Hi-Speedroid Chanbara”.

4-Before: If “Amazoness Empress” is returned to the Extra Deck by “Storming Mirror Force", its effect to Special Summon can activate.
Now: It cannot activate.

5-Before: You have 5 cards Set in your Spell & Trap Zone, you activate 1 of them, which is “Embodiment of Apophis” and Special Summons it to the Monster Zone. The Spell & Trap Zone that “Embodiment of Apophis” was in before cannot be used, so you cannot Set a new card in your Spell & Trap Zones.
Now: the Spell & Trap Zone it was in before is now empty and available for use, therefore you can Set a new Spell/Trap Card into the Spell & Trap Zone it was in before.
]]
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)


--Debug.ShowHint("Remember to change the duel rule in ReloadFieldBegin to test in MR4 and MR5")
--Main Deck
Debug.AddCard(15951532,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(15951532,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(89631139,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(89631139,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(89631139,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(88241506,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(89882100,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(5318639,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(88241506,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(29432790,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(42110604,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(42110604,0,0,LOCATION_EXTRA,0,8)
--Monster Zones
Debug.AddCard(8487449,0,0,LOCATION_MZONE,1,4,true)
Debug.AddCard(87979586,0,0,LOCATION_MZONE,2,1,true)
--Spell & Trap Zones
Debug.AddCard(89882100,0,0,LOCATION_SZONE,1,10)
Debug.AddCard(89882100,0,0,LOCATION_SZONE,2,10)
Debug.AddCard(54447022,0,0,LOCATION_SZONE,0,10)

--Monster Zones
local a = Debug.AddCard(4591250,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(26202165,0,0,LOCATION_MZONE,3,1,true)
--Spell & Trap Zones
Debug.AddCard(79852326,0,0,LOCATION_SZONE,4,10)
Debug.AddCard(57728570,0,0,LOCATION_SZONE,3,10)
--Hand
Debug.AddCard(24508238,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(2273734,1,1,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(73574678,1,1,LOCATION_MZONE,0,4,true)
--Spell & Trap Zones
Debug.AddCard(44095762,1,1,LOCATION_SZONE,4,10)
Debug.AddCard(5650082,1,1,LOCATION_SZONE,3,10)
Debug.AddCard(84749824,1,1,LOCATION_SZONE,1,10)
Debug.PreSummon(a,SUMMON_TYPE_FUSION,LOCATION_EXTRA)
Debug.ReloadFieldEnd()


