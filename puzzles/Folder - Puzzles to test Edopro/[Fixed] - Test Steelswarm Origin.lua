--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)
--[[message
	Steelswarm Origin does not allow any kind of Summon, not even set.
]]
--Main Deck
Debug.AddCard(77542832,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(77542832,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(41999284,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(41999284,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(2857636,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(2857636,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(61888819,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(85138716,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(8487449,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(35209994,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(83764718,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--GY
Debug.AddCard(8814959,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
--Debug.AddCard(61888819,0,0,LOCATION_MZONE,5,1,true)
Debug.AddCard(34472920,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(77542832,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(77542832,0,0,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()