Debug.ReloadFieldBegin(DUEL_TEST_MODE,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message
The player isn't prompted to activate Warrior's effect from the Graveyard if your "Subterror Behemoth" is
flipped face-up when attacked and then destroyed after (during Before Damage Calculation in this example) by an effect like Drillroid's.
The Behemoth's FLIP effect triggers normally as it should in this scenario.
]]

Debug.AddCard(92970404,0,0,LOCATION_MZONE,0,POS_FACEDOWN_DEFENSE) --Subterror Ultramafus

Debug.AddCard(16719140,0,0,LOCATION_GRAVE,0,POS_FACEUP) --Subterror Warrior

Debug.AddCard(71218746,1,1,LOCATION_MZONE,0,POS_FACEUP_ATTACK) --Drillroid


Debug.ReloadFieldEnd()