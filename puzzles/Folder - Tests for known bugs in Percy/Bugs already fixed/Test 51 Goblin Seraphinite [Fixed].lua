--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--[[message

]]
--Main Deck
Debug.AddCard(2273734,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(41999284,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(39064822,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(19230407,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(31178212,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(53143898,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(41999284,0,0,LOCATION_MZONE,5,1,true)
Debug.AddCard(3113836,0,0,LOCATION_MZONE,4,4,true)
Debug.AddCard(75878039,0,0,LOCATION_MZONE,0,1,true)
Debug.AddCard(52927340,0,0,LOCATION_MZONE,2,4,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()