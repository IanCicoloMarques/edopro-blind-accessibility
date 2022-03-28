--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(94142993,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(99157310,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--Hand
Debug.AddCard(94365540,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(94142993,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(24158464,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(74937659,0,0,LOCATION_MZONE,5,1,true)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()