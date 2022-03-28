--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	An extra link cannot be performed
]]
--Extra Deck
Debug.AddCard(53413628,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(46947713,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(2347477,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(9523599,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
Debug.AddCard(40669071,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(33897356,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(15844566,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(36033786,0,0,LOCATION_MZONE,4,1,true)
Debug.AddCard(46947713,0,0,LOCATION_MZONE,5,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()