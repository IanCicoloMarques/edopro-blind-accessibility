--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	If Grinder Golem Golem is Special Summoned and Summons the tokens while the player controls, Gnomaterial should NOT be be able to be activated.
	Also if solemn jusgment is activated, the summoned tokens too should be destroyed, as the summon happens at the same time.
]]
--Hand
Debug.AddCard(58655504,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(41420027,0,0,LOCATION_SZONE,0,POS_FACEDOWN)
--Hand
Debug.AddCard(75732622,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.ReloadFieldEnd()
