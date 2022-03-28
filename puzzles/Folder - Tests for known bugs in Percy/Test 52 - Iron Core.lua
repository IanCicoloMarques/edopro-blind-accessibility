--Created using senpaizuri's Puzzle Maker (updated by Naim)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,1)
Debug.SetPlayerInfo(1,8000,0,0)

--Main Deck
Debug.AddCard(4035199,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(55784832,0,0,LOCATION_DECK,0,POS_FACEDOWN)
Debug.AddCard(73628505,0,0,LOCATION_DECK,0,POS_FACEDOWN)
--GY
Debug.AddCard(36623431,0,0,LOCATION_GRAVE,0,POS_FACEUP)
Debug.AddCard(36623431,0,0,LOCATION_GRAVE,0,POS_FACEUP)
--Monster Zones
--pandora
Debug.AddCard(15936370,0,0,LOCATION_MZONE,2,4,true)
--shapesnatch
--Debug.AddCard(4035199,0,0,LOCATION_MZONE,2,4,true)
--guarded treasure
--Debug.AddCard(17052477,0,0,LOCATION_SZONE,2,4,true)
Debug.ReloadFieldEnd()
--aux.BeginPuzzle()