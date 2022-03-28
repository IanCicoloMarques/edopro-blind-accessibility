--Created using senpaizuri's Puzzle Maker (updated by Naim & Larry126)
Debug.ReloadFieldBegin(DUEL_ATTACK_FIRST_TURN+DUEL_SIMPLE_AI,4)
Debug.SetPlayerInfo(0,8000,0,0)
Debug.SetPlayerInfo(1,8000,0,0)

--Extra Deck
Debug.AddCard(11502550,0,0,LOCATION_EXTRA,0,8)
--Hand
Debug.AddCard(14088859,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(54959865,0,0,LOCATION_HAND,0,POS_FACEDOWN)
Debug.AddCard(18511384,0,0,LOCATION_HAND,0,POS_FACEDOWN)
--Monster Zones
Debug.AddCard(89943723,0,0,LOCATION_MZONE,1,1,true)
Debug.AddCard(6205579,0,0,LOCATION_MZONE,3,1,true)
Debug.AddCard(24094653,0,0,LOCATION_GRAVE,1,1)
Debug.ReloadFieldEnd()
aux.BeginPuzzle()