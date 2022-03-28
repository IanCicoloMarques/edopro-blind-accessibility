--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	To demonstrate that Linkuriboh's Link Summon procedure is incorrect
]]
--Extra Deck
Debug.AddCard(94259633,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(41999284,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(33909817,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(81907872,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(35306215,0,0,LOCATION_MZONE,3,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()