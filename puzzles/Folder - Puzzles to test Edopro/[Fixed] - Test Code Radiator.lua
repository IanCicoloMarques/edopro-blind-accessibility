--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(53413628,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(75130221,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(2347477,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(30114823,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(75130221,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(2347477,1,1,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(30114823,1,1,LOCATION_HAND,0,POS_FACEDOWN)



--Monster Zones
Debug.AddCard(2347477,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(30114823,0,0,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()