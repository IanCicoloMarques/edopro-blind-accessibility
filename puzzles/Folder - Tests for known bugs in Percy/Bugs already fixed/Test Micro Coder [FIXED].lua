--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(7403341,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(2347477,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(16188701,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Extra Deck
Debug.AddCard(53413628,0,0,LOCATION_EXTRA,0,8)
Debug.AddCard(53413628,0,0,LOCATION_GRAVE,0,1)
--Hand
Debug.AddCard(2347477,0,0,LOCATION_MZONE,2,1,true)
Debug.AddCard(30114823,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(30114823,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(2347477,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
--Debug.AddCard(2347477,0,0,LOCATION_MZONE,2,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()